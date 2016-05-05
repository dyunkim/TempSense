void setup() {
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()) {
    Serial.println("hello");
  }
  else 
    Serial.println("nope");
  delay(500);

}
