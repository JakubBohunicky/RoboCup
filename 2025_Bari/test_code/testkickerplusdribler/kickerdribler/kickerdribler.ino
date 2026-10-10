void setup() {
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);

}

void loop() {
    analogWrite(10,255);
    digitalWrite(13,HIGH);
    digitalWrite(14,LOW);
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



   



