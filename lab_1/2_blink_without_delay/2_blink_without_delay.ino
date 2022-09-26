/*
 * 2_blink_without_delay.ino
 *
 * this is a simple Arduino program to blink an led (the electronics equivalent 
 * of hello world). This program turns an led on for 1 second and then off for 
 * 1 second, and so on ...
 * 
 * unlike the previous example, this version uses timing variables to blink the
 * led without using a delay statement. this frees up your code to do other 
 * things (such as reading from sensors, handling network communication, etc.)
 *
 * this program uses pin 6 for the led (this is the built in led on the MKR
 * series of boards).
 *
 * author: alex shenfield
 * date:   01-09-2022
 */

// the led is connected to pin 6
const int led_pin = 6;

// timing variables ...
long previous_time = 0;  // the last time the led was updated
long interval = 1000;    // the blink interval
int  led_state = LOW;    // initial state of led (off)

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
  // get the current time this time round the loop
  unsigned long current_time = millis();

  // if the set time interval has elapsed ...
  if (current_time - previous_time > interval)
  {
    // save the time
    previous_time = current_time;

    // blink the led (by flipping the led state)
    if (led_state == LOW)
    {
      led_state = HIGH;
    }
    else
    {
      led_state = LOW;
    }

    // set the led to the new led state
    digitalWrite(led_pin, led_state);
  }
}
