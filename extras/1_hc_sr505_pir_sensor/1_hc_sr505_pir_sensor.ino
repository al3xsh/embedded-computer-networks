/**
 * 1_hc_sr505_pir_sensor.ino
 *
 * simple sketch to show the operation of the HC-SR505 pir sensor
 * 
 * note the component info can be found at:
 * https://www.elecrow.com/wiki/index.php?title=HC-SR505_Mini_PIR_Motion_Sensor
 * 
 * key points are:
 * 1/ the delay time (before motion is no longer detected) is ~11s
 * 2/ the sensor needs to be powered from 5v or motion detection will
 *    be really unreliable
 *
 * author:  alex shenfield
 * date:    30/01/2023
 */

// SENSORS AND OUTPUTS

// set the led and pir sensor pins
const int led_pin = 6;
const int pir_pin = 7;

// TIMING VARIABLES

// check every 500 ms (unless motion is detected!)
long previous_time = 0;
long check_interval = 500;

// CODE

// this method runs once (when the sketch starts)
void setup()
{
  // set up serial comms for debugging
  Serial.begin(115200);
  while (!Serial);
  Serial.println("starting security detection system ...");

  // set the pir sensor pin as an input and initialise it low
  pinMode(pir_pin, INPUT);
  digitalWrite(pir_pin, LOW);

  // set the led pin as an output and initialise it low
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);

}

// this methods loops continuously
void loop()
{
  // check the pir sensor every 11s
  unsigned long current_time = millis();
  if (current_time - previous_time > check_interval)
  {
    previous_time = current_time;

    // if the pir sensor reads high (i.e. motion is detected) ...
    if (digitalRead(pir_pin) == HIGH)
    {
      // print an alert message and turn the led on
      Serial.println("motion detected");
      digitalWrite(led_pin, HIGH);
      
      // the pir datasheet states that it's delay time is 8s +/- 30%,
      // so, if we detect motion, there's no point in checking again
      // until ~11s has elapsed
      check_interval = 11000;
    }
    else
    {
      // otherwise, no motion is detected so turn led off ...
      Serial.println("no motion detected");
      digitalWrite(led_pin, LOW);

      // ... and check again in 500 ms!
      check_interval = 500;
    }
  }
}
