/*
 * 1_blink.ino
 *
 * this is a simple Arduino program to blink an led (the electronics equivalent 
 * of hello world). This program turns an led on for 1 second and then off for 
 * 1 second, and so on ...
 *
 * this program uses pin 6 for the led (this is the built in led on the MKR
 * series of boards).
 *
 * author: alex shenfield
 * date:   01-09-2022
 */

// the led is connected to pin 6
const int led_pin = 6;

// CODE

// this method runs once (when the sketch starts)
void setup()
{
  // sets the digital pin as output
  pinMode(led_pin, OUTPUT);
}

// this methods loops continuously
void loop()
{
  // turn led on, wait for 1 second, turn led off, wait for 1 second,
  // repeat ...
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  delay(1000);
}
