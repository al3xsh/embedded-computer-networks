//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**
 * 1_lcd_hello_world.ino
 * 
 * this is a simple Arduino program to keep track of the up-time using 
 * and display it on the Adafruit 2.8" TFT LCD screen:
 * 
 * https://www.adafruit.com/product/2090
 *
 * author: alex shenfield
 * date:   08-10-2022 
 */

// LIBRARY IMPORTS

// include the necessary libraries for the LCD
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// INITIAL VARIABLES

// DISPLAY

// set the additional SPI pins for the TFT break out
#define TFT_DC 6
#define TFT_CS 7

// create the tft object using the hardware SPI pins
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// UPTIME COUNTER

// timing variables ...
long previous_time = 0;
long interval = 1000; 

// create a variable to increment every second
int current_uptime = 0;

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
  Serial.println("LCD hello world program running ..."); 
  
  // start the tft screen and display some diagnostic data on the 
  // serial display
  tft.begin();
  print_diagnostics();

  // make the screen black
  tft.fillScreen(ILI9341_BLACK);
    
  // set the text colour, background colour, and text size
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);  
  tft.setTextSize(2);
  
  // rotate the display, reset the cursor to the top left, and write 
  // a header to it
  tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.println();
  tft.println("**************************");
  tft.println(" embedded lcd hello world ");
  tft.println("**************************");
  tft.println();
}

// this method loops continuously
void loop() 
{
  // get the current time this time round the loop
  unsigned long current_time = millis();

  // if the set time interval has elapsed ...
  if (current_time - previous_time > interval)
  {
    // save the time
    previous_time = current_time;
    
    // update the current uptime
    current_uptime = current_uptime + 1;
    
    // set the cursor to the start of the fifth line - each character
    // is 16 pixels high and so the cursor should be set to y = 5 * 16
    tft.setCursor(0, 80);
    tft.println("current up-time = ");
    tft.print(current_uptime);
    tft.println(" s");
  }
}

// UTILITY METHODS

// print some simple diagnostic information about the TFT LCD
// (this is optional but can help debug problems – e.g. the lcd not  
// properly connected)
void print_diagnostics()
{
  uint8_t x = 0;
  x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("display power mode: 0x"); 
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL mode: 0x"); 
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("pixel format: 0x"); 
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("image format: 0x"); 
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("self diagnostic: 0x"); 
  Serial.println(x, HEX); 
}
