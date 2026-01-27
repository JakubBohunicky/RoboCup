const int output[12][4]{
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1},
  {1,0,1,0},
  {1,0,1,1}  
};

const int treshold[12][4]{
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1},
  {1,0,1,0},
  {1,0,1,1}  
};
void setup() {
  Serial.begin(115200);
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(A13,INPUT);
  pinMode(A15,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<16;i++){
    digitalWrite(22,output[i][0]);
    digitalWrite(24,output[i][1]);
    digitalWrite(26,output[i][2]);
    digitalWrite(28,output[i][3]);
    Serial.print(analogRead(A13));
    Serial.print(" ");
    Serial.print(analogRead(A15));
    Serial.print(" ");

  }
  Serial.println("");
}
