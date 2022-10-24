//3456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|
/**
 * 2_tft_touchscreen_example.ino
 * 
 * a simple touch screen demo using the adafruit gfx libraries and
 * drivers for the adafruit 2.8" TFT + capactive touchscreen display 
 * breakout:
 * 
 * https://www.adafruit.com/product/2090
 * 
 * this demo has a touchable button that controls a virtual led. touch
 * the button and the led turns on, touch it again and it turns off.
 * 
 * full documentation for all features can be found at:
 * 
 * https://adafruit.github.io/Adafruit-GFX-Library/html/index.html
 *  
 * author: alex shenfield
 * date:   12/10/2022
 */
 
// include the necessary libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

// INITIAL DEFINES

// LCD AND TOUCHSCREEN

// define the custom pins
#define TFT_DC 6
#define TFT_CS 7

// create display and touchscreen objects
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_FT6206   ts = Adafruit_FT6206();

// lcd size
const int lcd_width  = 320;
const int lcd_height = 240;

// GRAPHICS OBJECTS

// define the button
Adafruit_GFX_Button on_button;

// set the x and y positions to put the button on the centre left of
// the screen (note: the button coordinates are the centre of the 
// button)
const int button_x = 100;
const int button_y = 120;

// set the height and width of the button
const int button_h = 40;
const int button_w = 100;

// set the x and y positions so that the "led" is centre right of the
// screen (note: the coordinates are the centre of the circle)
const int led_x = 250;
const int led_y = 120;

// led radius
const int led_r = 20;

// STATE VARIABLES

// keep track of the led state
int led_state = LOW;
  
// CODE

// this method runs once (when the sketch starts)
void setup() 
{  
  // start the touchscreen and the tft screen and make the screen black
  ts.begin();
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  
  // draw the button 
  on_button.initButton(&tft, button_x, button_y, button_w, button_h, 
                       ILI9341_BLUE, ILI9341_WHITE, ILI9341_BLUE, 
                       "Press me!", 1, 1);
  on_button.drawButton(true);

  // draw the "led"
  tft.fillCircle(led_x, led_y, led_r, ILI9341_RED);
}

// this method loops continuously
void loop() 
{
  // if the touch screen has been pressed ...
  if (ts.touched())
  {
    // get the touch coordinate and flip it to match the orientation  
    // of the screen
    TS_Point p = ts.getPoint(); 
    p.x = map(p.x, 0, lcd_height, lcd_height, 0);
    p.y = map(p.y, 0, lcd_width, lcd_width, 0);
    int y = tft.height() - p.x;
    int x = p.y;
    
    // check the button
    if (on_button.contains(x,y))
    {
      on_button.press(true);
    }
  }
  // as soon as it's released, reset the button press
  else
  {
    on_button.press(false);
  }

  // if the button was pressed since we last checked the touch screen
  // state then toggle the led colour
  if (on_button.justPressed())
  { 
    if (led_state == LOW)
    {
      tft.fillCircle(led_x, led_y, led_r, ILI9341_GREEN);
      led_state = HIGH;
    }
    else
    {
      tft.fillCircle(led_x, led_y, led_r, ILI9341_RED);
      led_state = LOW;      
    }
  }
}
