#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <math.h>
#include <utility/imumaths.h>


#define P 2
#define I 0
#define D 0

float outPid;
float error;
float oldError;
float sumI;

float spdA;
float spdB;
float spdC;
float spdD;

int speed = 50;

#define BNO055_SAMPLERATE_DELAY_MS (1);
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

#define motorDPWM 3   //PWM pin motor A
#define motorDINB 25  //INA pin motor A
#define motorDINA 27  //INB pin motor A

#define motorAPWM 5   //PWM pin motor B
#define motorAINB 29  //INA pin motor B
#define motorAINA 33  //INB pin motor B

#define motorCPWM 7   //PWM pin motor C
#define motorCINB 37  //INA pin motor C
#define motorCINA 39  //INB pin motor C

#define motorBPWM 9   //PWM pin motor D
#define motorBINB 43  //INA pin motor D
#define motorBINA 45  //INB pin motor D


void define_motors() {
  pinMode(motorAPWM, OUTPUT);  //motor A PWM
  pinMode(motorAINA, OUTPUT);  //motor A INA
  pinMode(motorAINB, OUTPUT);  //motor A INB

  pinMode(motorBPWM, OUTPUT);  //motor B PWM
  pinMode(motorBINA, OUTPUT);  //motor B INA
  pinMode(motorBINB, OUTPUT);  //motor B INB

  pinMode(motorCPWM, OUTPUT);  //motor C PWM
  pinMode(motorCINA, OUTPUT);  //motor C INA
  pinMode(motorCINB, OUTPUT);  //motor C INB

  pinMode(motorDPWM, OUTPUT);  //motor D PWM
  pinMode(motorDINA, OUTPUT);  //motor D INA
  pinMode(motorDINB, OUTPUT);  //motor D INB
}

void gyroCalibration() {
  !bno.begin();
  bno.setExtCrystalUse(true);
  sensors_event_t event;
  bno.getEvent(&event);
  oldError = (float)event.orientation.x;
  if (oldError > 180) {
    oldError -= 360;
  }
}

void motor(byte id, float spd) {

  switch (id) {
    case 1:
      analogWrite(motorAPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorAINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorAINB, spd > 0 ? LOW : HIGH);
      break;
    case 2:
      analogWrite(motorBPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorBINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorBINB, spd > 0 ? LOW : HIGH);
      break;
    case 3:
      analogWrite(motorCPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorCINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorCINB, spd > 0 ? LOW : HIGH);
      break;
    case 4:
      analogWrite(motorDPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorDINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorDINB, spd > 0 ? LOW : HIGH);
      break;
  }
}

void motion(float speedA, float speedB, float speedC, float speedD) {
  motor(1, speedA);
  motor(2, speedB);
  motor(3, speedC);
  motor(4, speedD);
}

float errorCalculation() {
  float sumD;

  sensors_event_t event;
  bno.getEvent(&event);
  error = (float)event.orientation.x;
  while (error != (float)event.orientation.x) {
    error = (float)event.orientation.x;
  }
  if (error > 180) {
    error -= 360;
  }

  sumI += error * I;
  sumD = (oldError - error) * D;
  if (error == 0) sumI = 0;
  outPid = (error * P) + sumI + sumD;
  oldError = error;
  return outPid;
}

void setup() {
  define_motors();
  gyroCalibration();
  Serial.begin(115200);
}

void loop() {
  float a = errorCalculation();
  Serial.println(a);
  motion(a, a, a, a);
}