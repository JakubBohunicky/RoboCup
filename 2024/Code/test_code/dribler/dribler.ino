void setup() {
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);

}

void loop() {
    analogWrite(255,0);
    digitalWrite(13,HIGH);
    digitalWrite(14,LOW);


}
