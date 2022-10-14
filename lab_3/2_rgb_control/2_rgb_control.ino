/*
 * 2_rgb_control.ino
 * 
 * this is a simple Arduino program to use pwn to cycle through some 
 * different colours on the built-in rgb led of the mkr wifi 1010 board
 * 
 * note: this requires the wifinina library to be installed
 *
 * author: alex shenfield
 * date:   30-09-2022
 */

// LIBRARY IMPORTS

// include the wifinina library and the wifi_drv.h file to allow control
// of the built-in led
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

// INITIAL VARIABLES

// define the leds
const int led_pin_r = 25;
const int led_pin_g = 26;
const int led_pin_b = 27;

// CODE

// this method runs once (when the sketch starts)
void setup()
{
  // sets the digital pins as outputs
  WiFiDrv::pinMode(led_pin_r, OUTPUT);
  WiFiDrv::pinMode(led_pin_g, OUTPUT);
  WiFiDrv::pinMode(led_pin_b, OUTPUT);
}

// this methods loops continuously
void loop()
{
  // full red  
  WiFiDrv::analogWrite(led_pin_r, 255);
  WiFiDrv::analogWrite(led_pin_g, 0);
  WiFiDrv::analogWrite(led_pin_b, 0);

  // slight delay
  delay(250);
  
  // purple  
  WiFiDrv::analogWrite(led_pin_r, 128);
  WiFiDrv::analogWrite(led_pin_g, 0);
  WiFiDrv::analogWrite(led_pin_b, 128);

  // slight delay
  delay(250);
  
  // full blue  
  WiFiDrv::analogWrite(led_pin_r, 0);
  WiFiDrv::analogWrite(led_pin_g, 0);
  WiFiDrv::analogWrite(led_pin_b, 255);

  // slight delay
  delay(250);
  
  // yellow 
  WiFiDrv::analogWrite(led_pin_r, 128);
  WiFiDrv::analogWrite(led_pin_g, 128);
  WiFiDrv::analogWrite(led_pin_b, 0);

  // slight delay
  delay(250);
  
  // full green  
  WiFiDrv::analogWrite(led_pin_r, 0);
  WiFiDrv::analogWrite(led_pin_g, 255);
  WiFiDrv::analogWrite(led_pin_b, 0);

  // slight delay
  delay(250);  
}
