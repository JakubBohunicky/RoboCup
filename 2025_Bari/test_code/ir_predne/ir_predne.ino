void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.print(analogRead(A8));
  Serial.print(" ");
  Serial.print(analogRead(A10));
  Serial.println("");
  delay(100);
}
