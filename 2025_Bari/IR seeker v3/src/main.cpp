#include <Arduino.h>
#include <Wire.h>

#define TCAADDR 0x70
#define TCA_COMPASS 0
#define TCA_IR_FRONT 1
#define TCA_IR_BACK 2
#define TCA_IR_V3 3


int IR_V3();
int IR_V3_strength();

void setup()
{
  Serial.begin(115200);
  Wire.begin();
}

void loop()
{
  Serial.print("IR V3: ");
  Serial.print(IR_V3());
  Serial.print(" Strength: ");
  Serial.println(IR_V3_strength());
  delay(1000); 
}


void tcaselect(uint8_t i) {
	if (i > 7) {
		return;
	}
	Wire.beginTransmission(TCAADDR);
	Wire.write(1 << i);
	Wire.endTransmission();
}


int IR_V3() {
  tcaselect(TCA_IR_V3);
  int value;

  Wire.beginTransmission(0x38 >> 1);
  Wire.write(0x04);
  Wire.endTransmission();
  Wire.requestFrom(0x38 >> 1, 1);
  value = Wire.read();

  while (Wire.available()) {
    Wire.read();
  }

  if (value > 127) {
    value = value - 255;
  }
  return value;
} 



int IR_V3_strength() {
  tcaselect(TCA_IR_V3);
  int value;

  Wire.beginTransmission(0x38 >> 1);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.requestFrom(0x38 >> 1, 1);

  value = Wire.read();
  while (Wire.available()) {
    Wire.read();
  }

  return 158 - value; // 158=maximum
}