#include <Servo.h>

Servo servo;
int speed;

void setup() {
  //  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  //  while (! Serial);
  //  Serial.println("Speed 0 to 255");
  servo.attach(9);
  speed = 95;
  servo.write(speed);
}

void loop() {
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed >= 60 && speed <= 130)
    {
      //      analogWrite(motorPin, speed);
      Serial.println(speed);
      servo.write(speed);
    }
  }
  
//  delay(2000);
//  speed += 5;
//  if (speed > 145) {
//    speed = 50;
//  }
//  servo.write(speed);

  // put your main code here, to run repeatedly:
//  Serial.println("70");
//  servo.write(70);
//  //  analogWrite(motorPin, 70);
//  delay(20000);
//  Serial.println("15");
//  servo.write(30);
//  //  analogWrite(motorPin, 30);
//  delay(20000);

}
