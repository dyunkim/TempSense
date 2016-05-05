#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include "ColorDefinitions.h"

#define PIN 4
#define LED_COUNT 9

Servo servo;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
int windDelaySpeed = 1000;
bool PRECIPITATION = false;
int BRIGHTNESS = 45;
float temp = -1;
float precip = -1;
float windSpeed = -1;
const static int MED_VALUE = 95;
const static int MIN_VALUE = 60;
const static int MAX_VALUE = 130;
const static int temperaturePin = 0;
const static int motorPin = 9;
const static float MAX_ERROR_MARGIN = 1.0;
int pwmVal;
int requestTemp;

void setup() {
  //  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  servo.attach(motorPin);
  servo.write(MED_VALUE);
  pwmVal = 95;
  requestTemp = 72;
  leds.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  leds.setBrightness(BRIGHTNESS);
  leds.show();   // ...but the LEDs don't actually update until you call this.
  while (temp == -1 && precip == -1 && windSpeed == -1) {
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
        if (count == 2) {
          temp = tempString.toFloat();
          precip = precipString.toFloat();
          windSpeed = windString.toFloat();
        }
        count++;
      }
    }
  }
  if (precip > 0) PRECIPITATION = true;
  if (windSpeed >= 1) {
    windDelaySpeed /= windSpeed;
  }
}

void loop() {
  if (PRECIPITATION && windSpeed >= 1) {    //floral white for snow
      // cylon function: first param is color, second is time (in ms) between cycles
      cylon(BLUE, windDelaySpeed);  // Indigo cylon eye!
  }
  else if (windSpeed >= 1) {
    cylon(WHITESMOKE, windDelaySpeed);
  }
  else {
    staticColor();
  }


  if (Serial.available()) {
    requestTemp = Serial.parseInt();
    Serial.print("Requesting Temperature: ");
    Serial.println(requestTemp);
  }
  changeTemperature(requestTemp);
  delay(1000);

  //  if (Serial.available())
  //  {
  //    int speed = Serial.parseInt();
  //    if (speed >= 60 && speed <= 130)
  //    {
  //      //      analogWrite(motorPin, speed);
  //      Serial.println(speed);
  //      servo.write(speed);
  //    }
  //  }
  //  readTemperature();
  //  delay(1000);
}

float math(int temp) {
  float zero = 551.51;
  float one = 20.734 * temp;
  float two = .22 * temp * temp;
  float three = .0008 * temp * temp * temp;
  return (three - two + one - zero);
}


void changeTemperature(int temperature) {
  float error = temperature - readTemperature();

  if (abs(error) >= (MAX_ERROR_MARGIN + 6)) {
    //    Serial.println("larger change");
    if (error > 0) {
      changePwm(102);
    } else {
      changePwm(75);
    }
  } else if (abs(error) >= (MAX_ERROR_MARGIN + 3)) {
    //    Serial.println("medium change");
    if (error > 0) {
      changePwm(100);
    } else {
      changePwm(87);
    }
  } else if (abs(error) >= MAX_ERROR_MARGIN) {
    //    Serial.println("small change");
    if (error > 0) {
      changePwm(97);
    } else {
      changePwm(92);
    }
  } else {
    Serial.println("Temperature reached");
  }
}


bool changePwm(int value) {
  if (value >= MIN_VALUE && value <= MAX_VALUE) {
    servo.write(value);
    //    Serial.println(pwmVal);
    return true;
  }
  else {
    Serial.print("value out of range\n");
    pwmVal = 95;
    return false;
  }
}


int readTemperature() {
  float voltage, degreesC, degreesF;

  float voltSum = 0;
  for (int i = 0; i < 10; ++i) {
    voltSum += getVoltage(temperaturePin);
    delay(50);
  }
  voltage = voltSum / 10.0;

  //voltage = getVoltage(temperaturePin);
  degreesC = (voltage - .5) * 100.0;
  degreesF = degreesC * (9.0 / 5.00) + 32.0;

  Serial.print("Degrees F: ");
  Serial.println(degreesF);
  return degreesF;
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}

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


