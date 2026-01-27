#define irMultiplexerPin1 22  //ir multiplexer pins
#define irMultiplexerPin2 24
#define irMultiplexerPin3 26
#define irMultiplexerPin4 28
#define irMultiplexerIn A12



const int outputArray[12][4] = {
  { 0, 0, 0, 0 },
  { 0, 0, 0, 1 },
  { 0, 0, 1, 0 },
  { 0, 0, 1, 1 },
  { 0, 1, 0, 0 },
  { 0, 1, 0, 1 },
  { 0, 1, 1, 0 },
  { 0, 1, 1, 1 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 1 },
  { 1, 0, 1, 0 },
  { 1, 0, 1, 1 }
};

const float sensorAngles[12] = { 90, 120, 150, 180, 210, 240, 270, 300, 330, 0, 30, 60 };


void define_irMultiplexer() {
  pinMode(irMultiplexerPin1, OUTPUT);
  pinMode(irMultiplexerPin2, OUTPUT);
  pinMode(irMultiplexerPin3, OUTPUT);
  pinMode(irMultiplexerPin4, OUTPUT);
  pinMode(irMultiplexerIn, INPUT);
}

uint16_t getBallAngle() {
  float ballAngle = 999;
  float xCor = 0;
  float yCor = 0;
  bool itCheck;
  itCheck = 0;
  for (int irNumber = 0; irNumber < 12; irNumber++)
  {
    digitalWrite(irMultiplexerPin1, outputArray[irNumber][0]);
    digitalWrite(irMultiplexerPin2, outputArray[irNumber][1]);
    digitalWrite(irMultiplexerPin3, outputArray[irNumber][2]);
    digitalWrite(irMultiplexerPin4, outputArray[irNumber][3]);
    Serial.print(analogRead(irMultiplexerIn));
    Serial.print(" ");
    if (analogRead(irMultiplexerIn) < 900) {
      itCheck = 1;
      xCor += sin(radians(sensorAngles[irNumber]));
      yCor += cos(radians(sensorAngles[irNumber]));
    }
  }

  if (itCheck == 1) {
      ballAngle = round((atan2(yCor, xCor) * (180 / M_PI))-90);

      if (ballAngle == -0) {
        ballAngle = 0;
      } else if (ballAngle < 0) {
        ballAngle += 360;
      }
      ballAngle += 180;
      if (ballAngle > 359) {
        ballAngle -= 360;
      }
    }
  else {
    ballAngle = 999;
  }
  Serial.print(" ==");
  Serial.print(ballAngle);
  Serial.print("==");
  Serial.println("");
  return ballAngle;
}
void setup() {
  define_irMultiplexer();
  Serial.begin(9600);
}
void loop() {
  //Serial.println(getBallAngle());
  getBallAngle();
  delay(100);
}
