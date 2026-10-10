#include <SPI.h>
#include <Pixy.h>

// This is the main Pixy object
Pixy pixy;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting...\n");
  pixy.init();
}

void loop() {
  static int i = 0;
  uint16_t blocks;
  uint16_t goalPosition = 999;
  char buf[32];

  // grab blocks!
  blocks = pixy.getBlocks();

  // If there are detect blocks, print them!
  if (blocks) {
    i++;
    if (i % 50 == 0) {
      goalPosition = ((pixy.blocks[0].width / 2) + pixy.blocks[0].x);
      Serial.println(goalPosition);
      if (goalPosition<120){
        goalPosition = -1;
      }else if (goalPosition>200){
        goalPosition = 1;
      }else{
        goalPosition = 0;
      }
    }
  }else{
    goalPosition = 999;
  }
  //Serial.println(goalPosition);
}
