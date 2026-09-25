void setup() {
  pinMode(25,OUTPUT);
  pinMode(27,OUTPUT);  //motor A
  pinMode(3,OUTPUT);  //En

  pinMode(29,OUTPUT);
  pinMode(33,OUTPUT);  //motor B
  pinMode(5,OUTPUT);  //En

  pinMode(37,OUTPUT);
  pinMode(39,OUTPUT);  //motor C
  pinMode(7,OUTPUT);  //En

  pinMode(43,OUTPUT);
  pinMode(45,OUTPUT);  //motor D
  pinMode(9,OUTPUT);  //En

}

void loop() {
  digitalWrite(25,1);
  digitalWrite(27,0);
  analogWrite(3,200);

  digitalWrite(29,1);
  digitalWrite(33,0);
  analogWrite(5,200);

  digitalWrite(37,1);
  digitalWrite(39,0);
  analogWrite(7,200);

  digitalWrite(43,1);
  digitalWrite(45,0);
  analogWrite(9,200);

  delay(5000);

  digitalWrite(25,0);
  digitalWrite(27,1);
  analogWrite(3,50);

  digitalWrite(29,0);
  digitalWrite(33,1);
  analogWrite(5,50);

  digitalWrite(37,0);
  digitalWrite(39,1);
  analogWrite(7,50);

  digitalWrite(43,0);
  digitalWrite(45,1);
  analogWrite(9,50);
  

  delay(5000);


  

}
