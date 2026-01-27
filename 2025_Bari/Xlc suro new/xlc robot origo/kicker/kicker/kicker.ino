void setup() {
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);

}

void loop() {
    analogWrite(8,255);
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
    delay(58);
    digitalWrite(12,HIGH);
    digitalWrite(11,LOW);
    delay(180);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    delay(2000);


}
