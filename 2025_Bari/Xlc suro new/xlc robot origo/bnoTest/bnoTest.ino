#include <Arduino.h>
#include <Adafruit_BNO08x.h>

#define BNO08X_RESET -1

float start_error;
int check = 0;

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

void setup(void) {

  Serial.begin(115200);
  while (!Serial) delay(10);
  //Serial.println("Adafruit BNO08x test!");

  if (!bno08x.begin_I2C()) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  Serial.println("BNO08x Found!");


  setReports(reportType, reportIntervalUs);

  Serial.println("Reading events");
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

void readBNO(){
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
      Serial.println(ypr.yaw - start_error);
    }
  }else{
    resetBNO();
  }
}


void loop() {
  readBNO();
  
}
