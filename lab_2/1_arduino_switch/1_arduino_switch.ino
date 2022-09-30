/*
 * 1_arduino_switch.ino
 * 
 * this is a simple Arduino program to use a push button (i.e. a momentary
 * switch) to turn on an led
 *
 * this program uses pin 7 for the push button and pin 6 for the led (this 
 * is the built in led on the MKR series of boards).
 *
 * author: alex shenfield
 * date:   01-09-2022
 */

// INITIAL VARIABLES

// the button is connected to pin 7 and the led is connected to pin 6
const int button_pin = 7;
const int led_pin = 6;

// CODE

// this method runs once (when the sketch starts)
void setup()
{
  // sets the pin directions
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

// this methods loops continuously
void loop()
{
  // if the button is pressed, turn the led on
  int button_state = digitalRead(button_pin);
  if(button_state == HIGH)
  {
    digitalWrite(led_pin, HIGH);
  }
  else
  {
    digitalWrite(led_pin, LOW);
  }
}
