#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <math.h>

#define P 2
#define I 0
#define D 0

#define BNO08X_RESET -1

float outPid;
float error;
float oldError;
float sumI;

float spdA;
float spdB;
float spdC;
float spdD;

int speed = 150;

#define motorAPWM 3  //PWM pin motor A
#define motorAINA 25  //INA pin motor A
#define motorAINB 27  //INB pin motor A

#define motorBPWM 5  //PWM pin motor B
#define motorBINA 29  //INA pin motor B
#define motorBINB 33  //INB pin motor B

#define motorCPWM 7  //PWM pin motor C
#define motorCINA 37   //INA pin motor C
#define motorCINB 39   //INB pin motor C

#define motorDPWM 9  //PWM pin motor D
#define motorDINA 43  //INA pin motor D
#define motorDINB 45  //INB pin motor D

float start_error;
int check = 0;
float e;

struct euler_t {
  float yaw;
} ypr;

Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

#ifdef FAST_MODE
sh2_SensorId_t reportType = SH2_GYRO_INTEGRATED_RV;
long reportIntervalUs = 2000;
#else
sh2_SensorId_t reportType = SH2_ARVR_STABILIZED_RV;
long reportIntervalUs = 5000;
#endif
void setReports(sh2_SensorId_t reportType, long report_interval) {
  Serial.println("Setting desired reports");
  if (!bno08x.enableReport(reportType, report_interval)) {
    Serial.println("Could not enable stabilized remote vector");
  }
}

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
  sensors_event_t event;
  
  error = readBNO() ;
  if (error>180){
    error-=360;
  }else if (error<-180){
    error+=360;
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
  Serial.begin(115200);

  while (!Serial) delay(10);
  //Serial.println("Adafruit BNO08x test!");

  if (!bno08x.begin_I2C()) {
    //Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  //Serial.println("BNO08x Found!");


  setReports(reportType, reportIntervalUs);

  //Serial.println("Reading events");
  delay(100);
}

void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees = false) {
  float sqr = sq(qr);
  float sqi = sq(qi);
  float sqj = sq(qj);
  float sqk = sq(qk);

  ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr));

  if (degrees) {
    ypr->yaw *= RAD_TO_DEG;
  }
}

void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector, euler_t* ypr, bool degrees = false) {
  quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

void quaternionToEulerGI(sh2_GyroIntegratedRV_t* rotational_vector, euler_t* ypr, bool degrees = false) {
  quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

void resetBNO() {
  if (bno08x.getSensorEvent(&sensorValue)) {
    switch (sensorValue.sensorId) {
      case SH2_ARVR_STABILIZED_RV:
        quaternionToEulerRV(&sensorValue.un.arvrStabilizedRV, &ypr, true);
      case SH2_GYRO_INTEGRATED_RV:
        // faster (more noise?)
        quaternionToEulerGI(&sensorValue.un.gyroIntegratedRV, &ypr, true);
        break;
    }
    start_error = ypr.yaw;
    check = 1;
  }
}

float readBNO(){
  if (check == 1) {
    if (bno08x.getSensorEvent(&sensorValue)) {
      switch (sensorValue.sensorId) {
        case SH2_ARVR_STABILIZED_RV:
          quaternionToEulerRV(&sensorValue.un.arvrStabilizedRV, &ypr, true);
        case SH2_GYRO_INTEGRATED_RV:
          // faster (more noise?)
          quaternionToEulerGI(&sensorValue.un.gyroIntegratedRV, &ypr, true);
          break;
      }
      e = ypr.yaw - start_error;
    }
  }else{
    resetBNO();
    if (bno08x.getSensorEvent(&sensorValue)) {
      switch (sensorValue.sensorId) {
        case SH2_ARVR_STABILIZED_RV:
          quaternionToEulerRV(&sensorValue.un.arvrStabilizedRV, &ypr, true);
        case SH2_GYRO_INTEGRATED_RV:
          // faster (more noise?)
          quaternionToEulerGI(&sensorValue.un.gyroIntegratedRV, &ypr, true);
          break;
      }
      e = ypr.yaw - start_error;
    }
  }
  return e;
}

void loop() {
  float a = errorCalculation();
  Serial.println(a);
  motion(a, a, a, a);
  //delay(100);
}
