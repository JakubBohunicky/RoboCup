#include <Wire.h>                                     // I2C library.

#define DATA_COUNT_ANGLE 4                            // Number of bytes to receive for angle-and-distance version.
#define DATA_COUNT_RAW 13                             // Number of bytes to receive for raw version.
#define I2C_ADDRESS 0x10                              // Sensor's I2C address.
#define REGISTER_ANGLE_AND_DISTANCE 0x00              // I2C virtual register with distance and angle.
#define REGISTER_RAW 0x01                             // I2C virtual register with raw data
#define RAW false                                      // true - raw data, false - angle and distance

uint32_t ms;                                          // Variable used for displaying results periodically.

void setup() {
  Serial.begin(115200);                               // Adjust monitor speed to 115200 bps in order not to get garbage in the window.
  Wire.begin();                                       // Start I2C.
  delay(500);                                         // Wait to be sure that the text will be displayed.
  Serial.println("Start");
}

void loop() {
  if (millis() - ms > 100){                           // Every 0.1 sec...

#if RAW
    Wire.beginTransmission(I2C_ADDRESS);              // Start a "write" I2C command (write to sensor).
    Wire.write((uint8_t)REGISTER_RAW);                // Send the desired virtual register address.
    Wire.endTransmission();                           // End "write" part.

    Wire.requestFrom((int)I2C_ADDRESS, DATA_COUNT_RAW);// Start "read" part (read from sensor). Request 4 bytes of data.
    for (uint8_t i = 0; i < DATA_COUNT_RAW - 1; i++){
      uint8_t data = Wire.read();                     // Read a byte (single sensor's receiver)
      Serial.print((int)data);                        // Print it
      Serial.print(" ");
    }
    Serial.println(Wire.read() ? "near" : "far");     // Last byte signals if any of the near-sensing 12 receivers has any positive value ("near") or not ("far"), in which case 6 values of the far-sensing receivers are displayed.
#else
    Wire.beginTransmission(I2C_ADDRESS);              // Start a "write" I2C command (write to sensor).
    Wire.write((uint8_t)REGISTER_ANGLE_AND_DISTANCE); // Send the desired virtual register address.
    Wire.endTransmission();                           // End "write" part.

    Wire.requestFrom((int)I2C_ADDRESS, DATA_COUNT_ANGLE);   // Start "read" part (read from sensor). Request 4 bytes of data.
    uint16_t angle = Wire.read() << 8;                // Here and in the next 3 lines, read 4 bytes and reconstruct 2 16-bit values: angle and distance.
    angle |= Wire.read();
    uint16_t distance = Wire.read() << 8;
    distance |= Wire.read();
    
    Serial.println("Distance: " + (String)distance + ", angle: " + (String)angle + "°"); // Display.
#endif

    ms = millis();
  }
}