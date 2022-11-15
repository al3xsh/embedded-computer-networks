//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**
 * 3_restful_arduino.ino
 *
 * arduino restful api example using the aREST library - in this example we are
 * setting the brightness of an led on pin 5 and reading light values
 *
 * author:  alex shenfield
 * date:    01/11/2022
 */

// LIBRARY IMPORTS

// include the necessary libraries for wifi functionality
#include <SPI.h> 
#include <WiFiNINA.h>

// my wifi credentials are included as a seperate header file
#include "MyCredentials.h"

// include the aREST library (making sure that it knows we are using a WiFi 
// client)
#define WiFi_h 1
#include <aREST.h>

// WIFI INITIALISATION

// set the initial wifi status (to idle)
int status = WL_IDLE_STATUS;

// set up a server on port 80 (note: web browsers usually assume that 
// the server is running on port 80 unless told otherwise)
WiFiServer server(80);

// AREST DECLARATIONS

// create an aREST instance
aREST rest = aREST();

// variables to monitor with our webservice
int light_level = 0;

// CODE

// this method runs once (when the sketch starts)
void setup()
{
  // set up serial ...
  
  // set up serial comms for debugging and display of DHCP allocated 
  // IP address
  Serial.begin(115200);
  while (!Serial);
  Serial.println("simple rest client running ..."); 

  // set up wifi ...

  // attempt to connect to the wifi network
  while (status != WL_CONNECTED) 
  {
    Serial.print("attempting to connect to network: ");
    Serial.println(my_ssid);
    
    // connect to wifi network
    status = WiFi.begin(my_ssid, my_pass);

    // wait for 5 seconds for wifi to come up
    delay(5000);
  }
  Serial.println("connected to WiFi network");  

  // print the IP address to the serial monitor
  IPAddress my_ip = WiFi.localIP();
  Serial.print("my ip address: "); 
  Serial.println(my_ip);
  
  // start the server
  server.begin();

  // set up rest functionality ...

  // set output pin mode
  pinMode(5, OUTPUT);

  // expose the light level variable to the REST api
  rest.variable("light_level", &light_level);

  // expose the led trigger function to the REST api
  rest.function("led", led_control);

  // set the name and id for this webservice node
  rest.set_id("001");
  rest.set_name("alexs_arduino");
}

// main loop
void loop()
{
  // update our light level each time round the loop
  light_level = analogRead(A0);

  // listen for incoming clients
  WiFiClient client = server.available();
  rest.handle(client);
}

// FUNCTIONS EXPOSED TO THE REST API

// led control function accessible by the API
int led_control(String command)
{
  // debugging information about the actual command string
  Serial.print("command is ");
  Serial.println(command);

  // get pwm signal from command
  int pwm = command.toInt();
  pwm = constrain(pwm, 0, 255);

  // send pwm signal to the led
  analogWrite(5, pwm);

  // return 1 (indicating success)
  return 1;
}
