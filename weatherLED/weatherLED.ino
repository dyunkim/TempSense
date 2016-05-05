/* SparkFun WS2812 Breakout Board Example
  SparkFun Electronics
  date: July 25, 2013
  license: GNU GENERAL PUBLIC LICENSE

  Requires the Adafruit NeoPixel library. It's awesome, go get it.
  https://github.com/adafruit/Adafruit_NeoPixel

  This simple example code runs three sets of animations on a group of WS2812
  breakout boards. The more boards you link up, the better these animations
  will look.

  For help linking WS2812 breakouts, checkout our hookup guide:
  https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide

  Before uploading the code, make sure you adjust the two defines at the
  top of this sketch: PIN and LED_COUNT. Pin should be the Arduino pin
  you've got connected to the first pixel's DIN pin. By default it's
  set to Arduino pin 4. LED_COUNT should be the number of breakout boards
  you have linked up.
*/
#include <Adafruit_NeoPixel.h>
#include "ColorDefinitions.h"

#define PIN 4
#define LED_COUNT 9

// Create an instance of the Adafruit_NeoPixel class called "leds".
// That'll be what we refer to from here on...
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
int windDelaySpeed = 1000;
bool PRECIPITATION = false;
int BRIGHTNESS = 45;
float temp;
float precip;
float windSpeed;
void setup()
{
  Serial.begin(9600);
  leds.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  leds.setBrightness(BRIGHTNESS);
  leds.show();   // ...but the LEDs don't actually update until you call this.
}

void loop()
{
  String tempString;
  String windString;
  String precipString;
  delay(1000);
  int count = 0;

  while (Serial.available() > 0) {
    if (Serial.peek() != 'x' && count == 0) {
      char c = Serial.read();
      tempString += c;
    }
    else if (Serial.peek() != 'x' && count == 1) {
      char c = Serial.read();
      precipString += c;
    }
    else if (Serial.peek() != 'x' && count == 2) {
      char c = Serial.read();
      windString += c;
    }
    else {
      char trash = Serial.read();
      if(count == 2) {
        temp = tempString.toFloat();
        precip = precipString.toFloat();
        windSpeed = windString.toFloat();
      }
      count++;
    }
  }

  //  if(temp != 0) staticColor();
  PRECIPITATION = false;
  if (PRECIPITATION) {    //floral white for snow
    for (int i = 0; i < 10; i++) {
      // cylon function: first param is color, second is time (in ms) between cycles
      cylon(BLUE, windDelaySpeed);  // Indigo cylon eye!
    }
  }
  else {
    //    staticColor();
  }
}

// Implements a little larson "cylon" sanner.
// This'll run one full cycle, down one way and back the other

void staticColor() {
  clearLEDs();

  unsigned long color = WHITESMOKE;
  byte red = (color & 0xFF0000) >> 16;
  byte green = (color & 0x00FF00) >> 8;
  byte blue = (color & 0x0000FF);
  for (int i = 0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, red, green, blue);
  }
  leds.show();
}
void cylon(unsigned long color, byte wait)
{
  // weight determines how much lighter the outer "eye" colors are
  const byte weight = 1;
  // It'll be easier to decrement each of these colors individually
  // so we'll split them out of the 24-bit color value
  byte red = (color & 0xFF0000) >> 16;
  byte green = (color & 0x00FF00) >> 8;
  byte blue = (color & 0x0000FF);

  // Start at closest LED, and move to the outside
  for (int i = 0; i <= LED_COUNT - 1; i++)
  {
    clearLEDs();
    leds.setPixelColor(i, red, green, blue);  // Set the bright middle eye
    // Now set two eyes to each side to get progressively dimmer
    for (int j = 1; j < 3; j++)
    {
      if (i - j >= 0)
        leds.setPixelColor(i - j, red / (weight * j), green / (weight * j), blue / (weight * j));
      if (i - j <= LED_COUNT)
        leds.setPixelColor(i + j, red / (weight * j), green / (weight * j), blue / (weight * j));
    }
    leds.show();  // Turn the LEDs on
    delay(wait);  // Delay for visibility
  }
}
// Sets all LEDs to off, but DOES NOT update the display;
// call leds.show() to actually turn them off after this.
void clearLEDs() {
  for (int i = 0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, 0);
  }
}

