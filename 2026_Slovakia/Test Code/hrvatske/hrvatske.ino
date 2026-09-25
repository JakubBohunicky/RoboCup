#include <Wire.h>
#include <math.h>

#define IR_I2C_ADDRESS   0x10
#define IR_REGISTER_RAW  0x01
#define IR_RAW_COUNT     13

// near mode: 12 receiverov
static const float NEAR_SENSOR_ANGLE_DEG[12] = {
  0.0f, 30.0f, 60.0f, 90.0f, 120.0f, 150.0f,
  180.0f, 210.0f, 240.0f, 270.0f, 300.0f, 330.0f
};

// far mode: 6 receiverov
// ak ma tvoja doska ine realne rozlozenie, zmen len toto pole
static const float FAR_SENSOR_ANGLE_DEG[6] = {
  0.0f, 60.0f, 120.0f, 180.0f, 240.0f, 300.0f
};

// chces, aby predok robota bol 180°
static const float FRONT_OFFSET_DEG = 215.0f;

// vystupy
float ballAngle = 0.0f;         // 0..359
float ballStrength = 0.0f;      // 0..1
bool ballNearMode = false;
bool ballValid = false;

// filter state
static float filteredAngle = 0.0f;
static bool hasLock = false;
static uint8_t suspectCount = 0;

// filter tuning
const float ALPHA_NEAR = 0.40f;
const float ALPHA_FAR  = 0.18f;
const float MAX_JUMP_NEAR = 55.0f;
const float MAX_JUMP_FAR  = 25.0f;

const int MIN_SUM_NEAR = 20;
const int MIN_SUM_FAR  = 8;
const float MIN_DIR_NEAR = 0.08f;
const float MIN_DIR_FAR  = 0.05f;

static uint32_t lastPrintMs = 0;

static inline float deg2rad(float d) {
  return d * 0.01745329251994329577f;
}

static inline float rad2deg(float r) {
  return r * 57.29577951308232088f;
}

static inline float wrap360(float a) {
  while (a < 0.0f) a += 360.0f;
  while (a >= 360.0f) a -= 360.0f;
  return a;
}

static inline float angleDiffDeg(float a, float b) {
  float d = fmodf(a - b + 540.0f, 360.0f) - 180.0f;
  return fabsf(d);
}

static inline float circularLerpDeg(float from, float to, float alpha) {
  float d = fmodf(to - from + 540.0f, 360.0f) - 180.0f;
  return wrap360(from + alpha * d);
}

static uint8_t median3(uint8_t a, uint8_t b, uint8_t c) {
  if (a > b) { uint8_t t = a; a = b; b = t; }
  if (b > c) { uint8_t t = b; b = c; c = t; }
  if (a > b) { uint8_t t = a; a = b; b = t; }
  return b;
}

bool readBallRaw(uint8_t raw[12], bool &nearMode) {
  Wire.beginTransmission(IR_I2C_ADDRESS);
  Wire.write((uint8_t)IR_REGISTER_RAW);
  if (Wire.endTransmission() != 0) {
    return false;
  }

  int got = Wire.requestFrom((int)IR_I2C_ADDRESS, IR_RAW_COUNT);
  if (got != IR_RAW_COUNT) {
    while (Wire.available()) Wire.read();
    return false;
  }

  for (int i = 0; i < 12; i++) {
    raw[i] = Wire.read();
  }

  nearMode = Wire.read() ? true : false;
  return true;
}

void getBallFromRaw() {
  uint8_t raw[12];
  bool nearMode = false;

  if (!readBallRaw(raw, nearMode)) {
    ballValid = false;
    return;
  }

  // median-of-3 proti jednorazovym ustrelom
  static uint8_t hist[12][3] = {};
  static uint8_t histPos = 0;

  for (int i = 0; i < 12; i++) {
    hist[i][histPos] = raw[i];
  }
  histPos = (histPos + 1) % 3;

  uint8_t filt[12];
  for (int i = 0; i < 12; i++) {
    filt[i] = median3(hist[i][0], hist[i][1], hist[i][2]);
  }

  float x = 0.0f;
  float y = 0.0f;
  int sum = 0;
  int maxVal = 0;
  int secondVal = 0;

  if (nearMode) {
    for (int i = 0; i < 12; i++) {
      int v = filt[i];
      sum += v;

      if (v > maxVal) {
        secondVal = maxVal;
        maxVal = v;
      } else if (v > secondVal) {
        secondVal = v;
      }

      float a = deg2rad(NEAR_SENSOR_ANGLE_DEG[i]);
      x += cosf(a) * v;
      y += sinf(a) * v;
    }
  } else {
    for (int i = 0; i < 6; i++) {
      int v = filt[i];
      sum += v;

      if (v > maxVal) {
        secondVal = maxVal;
        maxVal = v;
      } else if (v > secondVal) {
        secondVal = v;
      }

      float a = deg2rad(FAR_SENSOR_ANGLE_DEG[i]);
      x += cosf(a) * v;
      y += sinf(a) * v;
    }
  }

  if (sum <= 0 || maxVal <= 0) {
    ballValid = false;
    return;
  }

  float rawAngle = wrap360(rad2deg(atan2f(y, x)) + FRONT_OFFSET_DEG);
  float dirStrength = sqrtf(x * x + y * y) / (float)sum;
  float peakRatio = (maxVal > 0) ? ((float)(maxVal - secondVal) / (float)maxVal) : 0.0f;

  bool enoughEnergy = nearMode ? (sum >= MIN_SUM_NEAR) : (sum >= MIN_SUM_FAR);
  bool enoughDirection = nearMode ? (dirStrength >= MIN_DIR_NEAR) : (dirStrength >= MIN_DIR_FAR);
  bool validNow = enoughEnergy && enoughDirection;

  if (!validNow) {
    ballValid = false;
    return;
  }

  if (!hasLock) {
    filteredAngle = rawAngle;
    hasLock = true;
    suspectCount = 0;
  } else {
    float jump = angleDiffDeg(rawAngle, filteredAngle);
    float maxJump = nearMode ? MAX_JUMP_NEAR : MAX_JUMP_FAR;

    if (dirStrength < 0.12f) maxJump *= 0.6f;
    if (peakRatio < 0.15f)   maxJump *= 0.7f;

    if (jump <= maxJump) {
      filteredAngle = circularLerpDeg(filteredAngle, rawAngle, nearMode ? ALPHA_NEAR : ALPHA_FAR);
      suspectCount = 0;
    } else {
      suspectCount++;
      if (suspectCount >= 3) {
        filteredAngle = circularLerpDeg(filteredAngle, rawAngle, 0.15f);
        suspectCount = 0;
      }
    }
  }

  ballAngle = filteredAngle;
  ballStrength = dirStrength;
  ballNearMode = nearMode;
  ballValid = true;

  if (millis() - lastPrintMs > 100) {
    lastPrintMs = millis();

    Serial.print("mode=");
    Serial.print(ballNearMode ? "near" : "far");
    Serial.print(" raw=[");
    for (int i = 0; i < 12; i++) {
      Serial.print((int)raw[i]);
      if (i != 11) Serial.print(' ');
    }
    Serial.print("] angle=");
    Serial.print(ballAngle, 1);
    Serial.print(" strength=");
    Serial.print(ballStrength, 3);
    Serial.print(" valid=");
    Serial.println(ballValid ? "1" : "0");
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(300);
  Serial.println("IR raw ball tracking start");
}

void loop() {
  getBallFromRaw();
  delay(10);
}