//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**
 * 3c_iot_light_switch.ino
 * 
 * an internet of things light switch that integrates with adafruit io
 * to allow remote control of lighting.
 * 
 * because we are (i am!) lazy, we will use a library for button debouncing.
 * this is the "EasyButton" library which can be installed via the library
 * manager.
 * 
 * WARNING: if you toggle the light switch too fast, you are likely to
 * hit the rate limits of adafruit.io - pay attention to the throttle
 * topic in the serial window.
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

// include our lazy button library
#include <EasyButton.h>

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

// BUTTON AND LED DECLARATIONS

// light bulb settings
const int light_bulb = 6;
int light_state = LOW;

// light switch (on pin 7)
EasyButton light_switch(7);

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

  // set up the light bulb and light switch (including the button pressed
  // callback function)
  pinMode(light_bulb, OUTPUT);
  light_switch.begin();
  light_switch.onPressed(light_toggle);
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
    // handle the light switch (but only bother if the state has changed)
    if (digitalRead(light_bulb) != light_state)
    {
      digitalWrite(light_bulb, light_state);
    }
  
    // handle mqtt functions (e.g. subscriptions to topics)
    client.loop();
  } 

  // read the button status
  light_switch.read();
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

      // once connected, subscribe to relevant feeds
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

// mqtt message received callback
void callback(char* topic, byte* payload, unsigned int length) 
{  
  // get the topic
  String t = String(topic);
  
  // get the value of the message
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

  // parse the light switch topic to work out what the light bulb
  // should be doing
  if (t.indexOf("light-switch") > 0)
  {
    if (strcmp(data, "ON") == 0)
    {
      light_state = HIGH;
    }
    else if (strcmp(data, "OFF") == 0)
    {
      light_state = LOW;
    }
  }
}

// APPLICATION FUNCTIONS

// callback function attached to the light switch button
void light_toggle()
{
  // toggle the state of the light
  light_state = !light_state;
  
  // if the client is connected then send a data update
  if (client.connected())
  {    
    // send "ON" if the led is on, and "OFF" if the led is off
    if (light_state == HIGH)
    {
      client.publish("alexshenfield/f/light-switch", "ON");
    }
    else
    {
      client.publish("alexshenfield/f/light-switch", "OFF");      
    }
  }
}
