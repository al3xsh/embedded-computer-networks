//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**
 * 1_simple_web_server.ino
 *
 * a simple web server for demonstrating arduino mkr wifi 1010 
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
}

// this methods loops continuously
void loop()
{
  // check for a client connection
  WiFiClient client = server.available();

  // if a remote client is connected
  if (client)
  {
    // get the ip address of the remote client
    IPAddress ip = client.remoteIP();
    Serial.print("new client at ");
    Serial.println(ip);

    // while the client is still connected
    while (client.connected())
    {
      // and has more data to send
      if (client.available() > 0)
      {
        // read bytes from the incoming client and write them to
        // the serial monitor
        Serial.print((char)client.read());
      }
      // when the client is done sending data
      else
      {
        // send standard http response header (to acknowledge the
        // data)
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
  
        // disconnect from client
        client.stop();
      }
    }
  }
}
