#include <Servo.h>
//#include <cmath>
Servo servo;
const static int MED_VALUE = 95;
const static int MIN_VALUE = 60;
const static int MAX_VALUE = 130;
const static int temperaturePin = 0;
const static int motorPin = 9;
const static float MAX_ERROR_MARGIN = 2.00;
int pwmVal;

void setup() {
  //  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  servo.attach(motorPin);
  servo.write(MED_VALUE);
  pwmVal = 95;
}

void loop() {
//  if (Serial.available())
//  {
//    int speed = Serial.parseInt();
//    Serial.println(speed);
//    changeTemperature(speed);
//  }
//
//  
//  readTemperature();
//  //changeTemperature();
//  delay(1000);

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
  readTemperature();
  delay(1000);
}


void changeTemperature(int temperature) {
  float error = temperature - readTemperature();
  while(abs(error) >= MAX_ERROR_MARGIN) {
    if (error > 0) {
      pwmVal += 1;
      changePwm(pwmVal);
    } else {
      pwmVal -= 1;
      changePwm(pwmVal);
    }
    delay(1000);
    error = temperature - readTemperature();
  }
}

float mapTempDiff(float error) {
  
}

bool changePwm(int value) {
  if(value >= MIN_VALUE && value <= MAX_VALUE) {
    Serial.print("Given value: ");
    Serial.print(value);
    Serial.print("\n");  //debugging
    servo.write(value);
    Serial.println(pwmVal);
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

  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - .5) * 100.0;
  degreesF = degreesC * (9.0/5.00) + 32.0;

  Serial.print("Degrees F: ");
  Serial.println(degreesF);
  return degreesF;
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}

