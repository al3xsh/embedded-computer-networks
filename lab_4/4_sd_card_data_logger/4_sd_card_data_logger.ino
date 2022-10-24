/**
 * 4_sd_card_data_logger.ino
 *
 * simple sketch to log the value from a potentiometer every 
 * 1000 ms
 *
 * author: alex shenfield
 * date:   24-10-2022 
 */

// LIBRARY IMPORTS

// include the spi and sd card libraries
#include <SPI.h>
#include <SD.h>

// INITIAL VARIABLES

// define the update interval
#define UPDATE_INTERVAL 1000

// PINS

// the potentiometer is connected to pin A0
const int pot_pin = A0;

// the sd card chip select (ccs) is connected to pin 4
const int chip_select = 4;

// TIMING

// timing variables ...
long previous_time = 0;

// CODE

// this method runs once (when the sketch starts)
void setup() 
{
  // start serial comms and wait until its up and running
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }
  Serial.println("SD card logger running ..."); 
      
  // see if the sd card is present and can be initialized
  if (!SD.begin(chip_select)) {    
    return;
  }
  Serial.println("card initialised ...");
  
}

// this method loops continuously
void loop()
{
  // get the current time this time round the loop
  unsigned long current_time = millis();

  // if the set time interval has elapsed ...
  if (current_time - previous_time > UPDATE_INTERVAL)
  {   
    // read the potentiometer
    int pot_val = analogRead(pot_pin);    
    
     // print the value of the potentiometer to serial
    Serial.print("potentiometer value is: ");
    Serial.println(pot_val);
    
    // open the logfile
    File logfile = SD.open("log.txt", FILE_WRITE);
    
    // if the logfile is open the write the current time and 
    // potentiometer value to it in csv format
    if (logfile)
    {
      logfile.print(current_time);
      logfile.print(",");
      logfile.println(pot_val);
      logfile.close();
    }
    else
    {
      Serial.println("error opening file!");
    }
    
    // set the previous time to the current time
    previous_time = current_time;
  }
}
