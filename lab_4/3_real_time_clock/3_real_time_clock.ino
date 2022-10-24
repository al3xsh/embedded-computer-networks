/**
 * 3_real_time_clock.ino
 * 
 * this is a simple Arduino program to keep track of the time using 
 * a real-time clock (built into the MKR WiFi 1010) and display it 
 * on the serial monitor
 * 
 * as the standard RTCZero library isn't very easy to initialise to 
 * the correct starting time / date I have written my own library to 
 * do this
 *
 * author: alex shenfield
 * date:   24-10-2022 
 */

// LIBRARY IMPORTS

// include my rtc library
#include "my_rtc.h"

// INITIAL VARIABLES

// create my rtc object
MyRTC rtc;

// CODE

// this method runs once (when the sketch starts)
void setup() 
{
  // start serial comms and wait until its up and running
  Serial.begin(9600);
  while (!Serial)
  {
    delay(100);
  }
  Serial.println("RTC program running ..."); 

  // initialise the rtc with the compilation time and date
  rtc.set_rtc();
}

void loop() 
{  
  // print the time and date to the serial monitor          
  Serial.print("current timestamp = ");
  Serial.print(rtc.get_rtc_time());
  Serial.print(" ");      
  Serial.print(rtc.get_rtc_date());
  Serial.println();
  
  // delay for 10 seconds
  delay(10000);  
}
