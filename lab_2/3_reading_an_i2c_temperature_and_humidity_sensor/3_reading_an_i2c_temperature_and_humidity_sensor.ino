/*
 * 3_reading_an_i2c_temperature_and_humidity_sensor.ino
 * 
 * this is a simple Arduino program to read from an i2c sensor (in this
 * case an SHT40 temperature and humidity sensor) and write the sensor 
 * reading to the serial monitor
 *
 * this program uses pins 11 and 12 for SDA and SCL respectively (these
 * are the default i2c pins on the Arduino MKR WiFi 1010)
 *
 * author: alex shenfield
 * date:   01-09-2022
 */

// LIBRARY IMPORTS

// we will use the adafruit SHT4X library to simplify use of this 
// sensor
#include "Adafruit_SHT4x.h"

// INITIAL VARIABLES

// create the sensor object
Adafruit_SHT4x sht40 = Adafruit_SHT4x();

// CODE

// this method runs once (when the sketch starts)
void setup() 
{
  // initialise serial communication at 115200 bits per second, wait for 
  // the serial port to become available, and print a start up message
  Serial.begin(115200);
  while (!Serial) 
  { 
    delay(1);  
  }
  Serial.println("i2c sensor example");

  // start the SHT40 sensor
  if (!sht40.begin()) 
  {
    // if it doesn't connect, print an error message and wait forever
    Serial.println("couldn't find SHT40 sensor - check connections!");
    while (true)
    {
      delay(1);
    }
  }

  // print the serial number of the sensor (for information)
  Serial.println("found SHT40 sensor");
  Serial.print("serial number 0x");
  Serial.println(sht40.readSerial(), HEX);

  // configure the sensor to have high precision (i.e. high repeatability
  // and heater off - see lab sheet for description of when using the 
  // heater is useful
  sht40.setPrecision(SHT4X_HIGH_PRECISION);
  sht40.setHeater(SHT4X_NO_HEATER);

}

// this methods loops continuously
void loop() 
{
  // initialise structures to contain the sensor readings
  sensors_event_t humidity;
  sensors_event_t temp;

  // read the sensor (and keep track of how long it takes)
  long timestamp = millis();
  sht40.getEvent(&humidity, &temp);
  timestamp = millis() - timestamp;
  
  // print temperature
  Serial.print("temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" degrees C");
  
  // print humidity
  Serial.print("humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("%");

  // print the sensor read time
  Serial.print("reading took ");
  Serial.print(timestamp);
  Serial.println(" ms");

  // we'll use a simple 1s delay here because our loop is simple - if 
  // we wanted to do anything more complicated in our loop, we'd be 
  // better off not using delays (because they mean our program can't 
  // do anything else)
  delay(1000);
}
