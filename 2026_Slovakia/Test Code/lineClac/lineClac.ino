#define lightMultiplexerPin1 22  //ir multiplexer pins
#define lightMultiplexerPin2 24
#define lightMultiplexerPin3 26
#define lightMultiplexerPin4 28
#define lightMultiplexerIn1 A13
#define lightMultiplexerIn2 A15



const int outputArray[16][4] = {
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
  { 1, 0, 1, 1 },
  { 1, 1, 0, 0 },
  { 1, 1, 0, 1 },
  { 1, 1, 1, 0 },
  { 1, 1, 1, 1 }
};

const int tresoldArray[12][4] = {
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
const float lightSensorAngles[32] = { 343.125, 354.375, 5.625, 16.875, 28.125, 39.375, 50.625, 61.875, 106.875, 95.625, 84.375, 73.125, 118.125, 129.375, 140.625, 151.875, 163.125, 174.375, 185.625, 196.875, 208.125, 219.375, 230.625, 241.875, 253.125, 264.375, 275.625, 286.875, 298.125, 309.375, 320.625 };


void define_lightMultiplexer() {
  pinMode(lightMultiplexerPin1, OUTPUT);
  pinMode(lightMultiplexerPin2, OUTPUT);
  pinMode(lightMultiplexerPin3, OUTPUT);
  pinMode(lightMultiplexerPin4, OUTPUT);
  pinMode(lightMultiplexerIn1, INPUT);
  pinMode(lightMultiplexerIn2, INPUT);
}

uint16_t getLineAngle() {
  float lineAngle = 999;
  float xCor = 0;
  float yCor = 0;
  bool itCheck;
  itCheck = 0;
  for (int lighNumber = 0; lighNumber <= 12; lighNumber++) {
    digitalWrite(lightMultiplexerPin1, outputArray[lighNumber][0]);
    digitalWrite(lightMultiplexerPin2, outputArray[lighNumber][1]);
    digitalWrite(lightMultiplexerPin3, outputArray[lighNumber][2]);
    digitalWrite(lightMultiplexerPin4, outputArray[lighNumber][3]);
    if (analogRead(lightMultiplexerIn1) < 100) {
      itCheck = 1;
      xCor += sin(radians(lightSensorAngles[lighNumber]));
      yCor += cos(radians(lightSensorAngles[lighNumber]));
    }
    if (analogRead(lightMultiplexerIn2) < 100) {
      if (lighNumber != 2) {
        itCheck = 1;
        xCor += sin(radians(lightSensorAngles[lighNumber + 16]));
        yCor += cos(radians(lightSensorAngles[lighNumber + 16]));
      }
    }
  }

  if (itCheck == 1) {
    lineAngle = round((atan2(yCor, xCor) * (180 / M_PI))+90);

    if (lineAngle == -0) {
      lineAngle = 0;
    } else if (lineAngle < 0) {
      lineAngle += 360;
    }
    lineAngle += 180;
    if (lineAngle > 359) {
      lineAngle -= 360;
    }
  } else {
    lineAngle = 999;
  }
  /*
  Serial.print(" ==");
  Serial.print(lineAngle);
  Serial.print("==");
  Serial.println("");
  */
  return lineAngle;
}
void setup() {
  define_lightMultiplexer();
  Serial.begin(115200);
}
void loop() {
  Serial.println(getLineAngle());
  //getLineAngle();
  delay(100);
}
