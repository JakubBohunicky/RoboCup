#include "Wire.h"
#include <MPU6050_light.h>

#define P 2
#define I 0
#define D 0

MPU6050 mpu(Wire);

float outPid;
float error;
float oldError;
float sumI;

float spdA;
float spdB;
float spdC;
float spdD;

int speed = 150;

#define motorDPWM 3  //PWM pin motor A
#define motorDINB 25  //INA pin motor A
#define motorDINA 27  //INB pin motor A

#define motorAPWM 5  //PWM pin motor B
#define motorAINB 29  //INA pin motor B
#define motorAINA 33  //INB pin motor B

#define motorCPWM 7  //PWM pin motor C
#define motorCINB 37   //INA pin motor C
#define motorCINA 39   //INB pin motor C

#define motorBPWM 9  //PWM pin motor D
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

  mpu.update();
  error = mpu.getAngleZ();

  if (error>180){
    error-=360;
  }else if (error<-180){
    error+=360;
  }
  
  sumI += error * I;
  sumD = (oldError - error) * D;
  if (error == 0) sumI = 0;
  outPid = -((error * P) + sumI + sumD);
  oldError = error;
  return outPid;
}

void setup() {
  define_motors();
  Serial.begin(9600);
  Wire.begin();
  byte status = mpu.begin();
  while(status!=0){ } // stop everything if could not connect to MPU6050
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("doneeee");

}

void loop() {
  float a = errorCalculation();
  Serial.println(a);
  motion(a, a, a, a);
  //delay(100);
}
