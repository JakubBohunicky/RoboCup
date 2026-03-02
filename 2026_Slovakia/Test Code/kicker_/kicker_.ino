void setup() {
  pinMode(4,OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);

}

bool dribblerShwitch = false;

void loop() {

  if (digitalRead(19) == 0){
    while(digitalRead(19) == 0)
    {
      delay(1);
    }
    //analogWrite(10, 0);
    //delay(50);

    
    digitalWrite(4,HIGH);
    delay(100);
    digitalWrite(4,LOW);
    //analogWrite(10, 255);
    delay(2000);
    

    // analogWrite(10, 255);
    // digitalWrite(13, LOW);
    // digitalWrite(14, HIGH);
    // delay(1000);

    
    // analogWrite(10, 255);
    // digitalWrite(13, dribblerShwitch);
    // digitalWrite(14, LOW);

  }

  if (digitalRead(2) == 0)
  {
      while(digitalRead(2) == 0)
      {
        delay(1);
      }
      dribblerShwitch = !dribblerShwitch;
  }

    analogWrite(10, 255);
    digitalWrite(13, dribblerShwitch);
    digitalWrite(14, LOW);
} 
