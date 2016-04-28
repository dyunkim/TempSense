const int temperaturePin = 0;


void setup() {
  Serial.begin(9600);

}

void loop() {
  float voltage, degreesC, degreesF;

  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - .5) * 100.0;
  degreesF = degreesC * (9.0/5.00) + 32.0;

  Serial.print("Degrees F: ");
  Serial.println(degreesF);

  delay(1000);

}

float getVoltage(int pin) {
  
  return (analogRead(pin) * 0.004882814);

}

