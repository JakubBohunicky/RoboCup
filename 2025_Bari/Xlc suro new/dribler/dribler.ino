void setup() {
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);

}

void loop() {
    analogWrite(10,255);
    digitalWrite(13,HIGH);
    digitalWrite(14,LOW);


}

 
