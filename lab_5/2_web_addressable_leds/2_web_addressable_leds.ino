//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**
 * 2_web_addressable_leds.ino
 *
 * a simple web service to control LEDs using the arduino mkr wifi 1010 
 * connectivity
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

// WIFI INITIALISATION

// set the initial wifi status (to idle)
int status = WL_IDLE_STATUS;

// set up a server on port 80 (note: web browsers usually assume that 
// the server is running on port 80 unless told otherwise)
WiFiServer server(80);

// variable indicating when to start paying attention to data
boolean pay_attention = true;

// CODE

// this method runs once (when the sketch starts)
void setup()
{
  // set up serial comms for debugging and display of DHCP allocated 
  // IP address
  Serial.begin(115200);
  while (!Serial);
  Serial.println("simple wifi web server running ..."); 

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

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("my signal strength (rssi):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
  // start the server
  server.begin();

  // set up the pins as outputs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

// this methods loops continuously
void loop()
{
  // constantly check for connections
  check_for_connections();
}

// HTTP REQUEST HANDLER

// method to check for incoming connections and process them
void check_for_connections()
{
  // get any client that is connected to the server and
  // trying to send data
  WiFiClient client = server.available();

  // record whether we have already sent the standard http
  // response header
  boolean header_sent = false;

  // if a remote client is connected
  if (client)
  {
    // get the ip address of the remote client
    IPAddress ip = client.remoteIP();
    Serial.print("new client at ");
    Serial.println(ip);

    // while the client is connected ...
    while (client.connected())
    {  
      // if we haven't already sent the http header, then send it
      if (!header_sent)
      {
        // send standard http response header (to acknowledge the
        // data)
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        header_sent = true;
      }
      
      // if the client has more data available ...
      if (client.available() > 0)
      {
        // read the next byte
        char c = client.read();
  
        // debugging ...
        Serial.print(c);
  
        // pay attention to all the data between the '?' character
        // and a space
        if (c == '?')
        {
          pay_attention = true;
        }
        else if (c == ' ')
        {
          pay_attention = false;
        }
  
        // if we are paying attention ...
        if (pay_attention)
        {
          // use a switch statement to decide what to do
          switch (c)
          {
            case '2':
              trigger_pin(2, client);
              break;  
            case '3':
              trigger_pin(3, client);
              break;  
            case '4':
              trigger_pin(4, client);
              break;  
            case '5':
              trigger_pin(5, client);
              break;  
            case 'x':
              clear_pins(client);
              break;
          }
        }
      }
      // when the client is done sending data
      else
      {        
        // disconnect from client
        client.stop();
      }
    }
  }
}

// UTILITY FUNCTIONS

// separate function for triggering pins - note we only need
// the wifi client so we can send data to it
void trigger_pin(int pin_number, WiFiClient client)
{
  // print a status message
  client.print("Turning on pin <b>");
  client.println(pin_number);
  client.println("</b><br>");

  // turn on appropriate pin
  digitalWrite(pin_number, HIGH);
}

// another function to clear all pins - again the wifi client
// is only needed to return data to the web page
void clear_pins(WiFiClient client)
{
  // print a status message
  client.println("Clearing all pins!<br>");

  // turn off pins
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}
