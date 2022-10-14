/*
 * 1_led_dimmer.ino
 * 
 * this is a simple Arduino program to read from a potentiometer and use
 * that reading to dim an led using pwm
 *
 * this program uses pin A0 for the analog sensor and pin 5 for the led
 *
 * author: alex shenfield
 * date:   01-09-2022
 */

// INITIAL VARIABLES

// the pot is connected to A0 and the led is connected to pin 5
const int pot_pin = A0;
const int led_pin = 5;

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
  // read the potentiometer (varies between 0-1023)
  int pot_value = analogRead(pot_pin);

  // remap the potentiometer value to between 0 and 255 (as that is
  // what the pwm signal needs) and send the pwm signal to the led
  int pwm_value = map(pot_value, 0, 1023, 0, 255);
  analogWrite(led_pin, pwm_value);
}
