#include <Servo.h>
#include <cmath>
Servo servo;
const static int MED_VALUE = 95;
const static int MIN_VALUE = 60;
const static int MAX_VALUE = 130;
const static int temperaturePin = 0;
const static int motorPin = 9;
const static float MAX_ERROR_MARGIN = 2.00;

void setup() {
  //  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  servo.attach(motorPin);
  servo.write(MED_VALUE);
}

void loop() {
  
}


void changeTemperature(int temperature) {
  float error = temperature - readTemperature();
  while(abs(error) <= MAX_ERROR_MARGIN) {
    if (error > 0) {
      changePwm(
    } else {
      
    }
    
    delay(1000);
    error = temperature - readTemperature();
  }
}

float mapTempDiff(float error) {
  
}

bool changePwm(int value) {
  if(value >= MIN_VALUE && value <= MAX_VALUE) {
    Serial.println("Given value: " + value + "\n");  //debugging
    servo.write(value);
    return true;
  }
  else {
    Serial.print("value out of range\n");
    return false;
  }
}


void readTemperature() {
  float voltage, degreesC, degreesF;

  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - .5) * 100.0;
  degreesF = degreesC * (9.0/5.00) + 32.0;

  Serial.print("Degrees F: " + "\n");
  Serial.println(degreesF);
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}

