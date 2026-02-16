#include <Pixy2I2C.h>
#include <Wire.h>

Pixy2I2C pixy;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);              // zmeň ak máš iné piny
  Serial.println("Starting I2C...");
  int8_t r = pixy.init();          // default adresa je 0x54
  Serial.println(r == 0 ? "Pixy init OK" : "Pixy init FAIL");
}

void loop() {
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    Serial.print("Blocks: ");
    Serial.println(pixy.ccc.numBlocks);
  }


  auto &b = pixy.ccc.blocks[0];  // najväčší blok (index 0 je najväčší)
Serial.print("sig=");   Serial.print(b.m_signature);
Serial.print(" x=");    Serial.print(b.m_x);
Serial.print(" y=");    Serial.print(b.m_y);
Serial.print(" w=");    Serial.print(b.m_width);
Serial.print(" h=");    Serial.print(b.m_height);
Serial.print(" age=");  Serial.println(b.m_age);

  delay(100);
}



