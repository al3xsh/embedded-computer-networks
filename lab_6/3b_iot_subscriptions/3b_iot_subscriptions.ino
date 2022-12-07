//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**
 * 3b_iot_subscriptions.ino
 * 
 * a simple mqtt application to parse mqtt messages on subscribed 
 * topics. in this sketch we have enhanced the message received
 * callback to extract the data from the payload into a complete
 * string so we can process it (rather than just pinting each 
 * character
 *
 * author:  alex shenfield
 * date:    03/11/2022
 */

// LIBRARY IMPORTS

// include the necessary libraries for wifi functionality
#include <SPI.h> 
#include <WiFiNINA.h>

/// include the pubsub client
#include <PubSubClient.h>

// my wifi credentials are included as a seperate header file
#include "MyCredentials.h"

// WIFI INITIALISATION

// set the initial wifi status (to idle)
int status = WL_IDLE_STATUS;

// MQTT DECLARATIONS

// mqtt server details
const char server[] = "io.adafruit.com";
const long port     = 1883;

// get a wifi client object and pass it to the mqtt client
WiFiClient wifi_client;
PubSubClient client(wifi_client);

// timing variables - note: adafruit.io allows a maximum of 30 messages
// per minute - any more than this and your account will be throttled
// and then blocked!
long previous_time = 0;
long connection_interval = 10000;

// CODE

// this method runs once (when the sketch starts)
void setup()
{
  // set up serial comms for debugging and display of DHCP allocated 
  // IP address
  Serial.begin(115200);
  while (!Serial);
  Serial.println("starting mqtt client on arduino ..."); 

  // mqtt server and subscription callback
  client.setServer(server, port);
  client.setCallback(callback);

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
}

// this methods loops continuously
void loop()
{  
  // if the client isn't connected then try to reconnect
  if (!client.connected())
  {
    reconnect();
  }
  else
  {
    // handle subscriptions to topics (i.e. incoming messages)
    client.loop();

    // do nothing else here (as we are just testing how message
    // subscriptions work)
    // ...
  }
}

// MQTT FUNCTIONS

// reconnect to adafruit io mqtt server
void reconnect()
{
  // loop until we're reconnected
  while (!client.connected())
  {
    Serial.println("attempting mqtt connection...");

    // try to connect to adafruit.io
    if (client.connect(CLIENT_ID, USER_ID, API_KEY))
    {
      Serial.println("... connected");

      // once connected, subscribe to relevant feeds feeds (also subscribe 
      // to the "throttle" and "errors" topics which will let us know if  
      // we are bumping up against the adafruit.io rate limit)
      client.subscribe((USER_ID "/feeds/status-messages"));
      client.subscribe((USER_ID "/feeds/light-switch"));
      client.subscribe((USER_ID "/throttle"));
      client.subscribe((USER_ID "/errors"));

      // ... and publish an announcement
      client.publish((USER_ID "/feeds/status-messages"), "we are alive!");
    }
    else
    {
      // print some error status
      Serial.print("connection failed, rc = ");
      Serial.print(client.state());
      Serial.println();
      Serial.println("we will try again in 5 seconds");

      // wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// enhanced mqtt message received callback (triggered every time 
// we get a message)
void callback(char* topic, byte* payload, unsigned int length) 
{  
  // get the topic
  String t = String(topic);
  
  // get the value of the message payload
  char data[length + 1];
  for (int i = 0; i < length; i++)
  {
    data[i] = payload[i];
  }
  data[length] = '\0';
  
  // print the message to the serial window
  Serial.print("message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(data);
}
