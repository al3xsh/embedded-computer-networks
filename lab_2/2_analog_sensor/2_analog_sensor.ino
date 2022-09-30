/*
 * 2_analog_sensor.ino
 * 
 * this is a simple Arduino program to read from an analog sensor (in this
 * case an ldr) and write the sensor reading to the serial monitor
 *
 * this program uses pin A0 for the analog sensor
 *
 * author: alex shenfield
 * date:   01-09-2022
 */

// INITIAL VARIABLES

// the ldr is connected to A0
const int ldr_pin = A0;

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
  Serial.println("analog sensor example");
}

// this methods loops continuously
void loop()
{
  // read the analog sensor and print to the serial monitor
  int ldr_value = analogRead(ldr_pin);
  Serial.println(ldr_value);  

  // delay for 100 ms between readings
  delay(100);
}
