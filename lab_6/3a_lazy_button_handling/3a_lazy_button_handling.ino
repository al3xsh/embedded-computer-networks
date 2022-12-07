//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**
 * 3a_lazy_button_handling.ino
 * 
 * a simple example of using the EasyButton library to handle button presses
 * without a tonne of extra code
 *
 * author:  alex shenfield
 * date:    03/11/2022
 */

// LIBRARY IMPORTS

// include our lazy button library
#include <EasyButton.h>

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
  // set up serial comms for debugging 
  Serial.begin(115200);
  while (!Serial);
  Serial.println("starting lazy button handler ..."); 
  
  // set up the light bulb and light switch (including the button pressed
  // callback function)
  pinMode(light_bulb, OUTPUT);
  light_switch.begin();
  light_switch.onPressed(light_toggle);
}

// this methods loops continuously
void loop() 
{
  // read the button status
  light_switch.read();
}

// APPLICATION FUNCTIONS

// callback function attached to the light switch button
void light_toggle()
{
  // print a status message
  Serial.println("button pressed!");
  
  // toggle the state of the light
  light_state = !light_state;
  digitalWrite(light_bulb, light_state);
}
