#include <Arduino.h>
#include <FastADC_Mux.h>

// tvoje ADC piny
static constexpr int PIN_A = 4;
static constexpr int PIN_B = 5;
static constexpr int PIN_X = 6;

// indexy pre analogReadFast() v poradi, v akom ich das do fadcInit()
static constexpr uint8_t CH_A = 0;
static constexpr uint8_t CH_B = 1;
static constexpr uint8_t CH_X = 2;

static void benchmarkAnalogRead(uint32_t samples) {
  uint32_t t0 = micros();

  uint32_t sumA = 0, sumB = 0, sumX = 0;
  uint16_t lastA = 0, lastB = 0, lastX = 0;

  for (uint32_t i = 0; i < samples; i++) {
    lastA = analogRead(PIN_A);
    lastB = analogRead(PIN_B);
    lastX = analogRead(PIN_X);

    sumA += lastA;
    sumB += lastB;
    sumX += lastX;
  }

  uint32_t dt = micros() - t0;

  Serial.println("=== analogRead() ===");
  Serial.printf("samples per channel: %lu\n", samples);
  Serial.printf("total conversions:   %lu\n", samples * 3UL);
  Serial.printf("total time:          %lu us\n", dt);
  Serial.printf("time / conversion:   %.2f us\n", (float)dt / (samples * 3.0f));
  Serial.printf("A avg=%lu last=%u\n", sumA / samples, lastA);
  Serial.printf("B avg=%lu last=%u\n", sumB / samples, lastB);
  Serial.printf("X avg=%lu last=%u\n", sumX / samples, lastX);
  Serial.println();
}

static void benchmarkAnalogReadFast(uint32_t samples) {
  uint32_t t0 = micros();

  uint32_t sumA = 0, sumB = 0, sumX = 0;
  uint16_t lastA = 0, lastB = 0, lastX = 0;

  for (uint32_t i = 0; i < samples; i++) {
    lastA = analogReadFast(CH_A);
    lastB = analogReadFast(CH_B);
    lastX = analogReadFast(CH_X);

    sumA += lastA;
    sumB += lastB;
    sumX += lastX;
  }

  uint32_t dt = micros() - t0;

  Serial.println("=== analogReadFast() ===");
  Serial.printf("samples per channel: %lu\n", samples);
  Serial.printf("total conversions:   %lu\n", samples * 3UL);
  Serial.printf("total time:          %lu us\n", dt);
  Serial.printf("time / conversion:   %.2f us\n", (float)dt / (samples * 3.0f));
  Serial.printf("A avg=%lu last=%u\n", sumA / samples, lastA);
  Serial.printf("B avg=%lu last=%u\n", sumB / samples, lastB);
  Serial.printf("X avg=%lu last=%u\n", sumX / samples, lastX);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_A, ADC_11db);
  analogSetPinAttenuation(PIN_B, ADC_11db);
  analogSetPinAttenuation(PIN_X, ADC_11db);

  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_X, INPUT);

  // init FastAnalogRead v tom istom poradi ako CH_A/CH_B/CH_X
  fadcInit(3, PIN_A, PIN_B, PIN_X);

  // zahriatie / ustalenie
  for (int i = 0; i < 100; i++) {
    (void)analogRead(PIN_A);
    (void)analogRead(PIN_B);
    (void)analogRead(PIN_X);

    (void)analogReadFast(CH_A);
    (void)analogReadFast(CH_B);
    (void)analogReadFast(CH_X);
  }

  Serial.println();
  Serial.println("Start benchmark");
}

void loop() {
  const uint32_t samples = 1000;

  benchmarkAnalogRead(samples);
  delay(500);

  benchmarkAnalogReadFast(samples);
  delay(2000);
}