#include <Servo.h>
//#include <cmath>
Servo servo;
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
}

void loop() {

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

