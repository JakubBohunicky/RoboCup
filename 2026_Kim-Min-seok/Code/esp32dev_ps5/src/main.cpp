#include <Arduino.h>
#include <ps5Controller.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>


struct ControllerRx_MSG {
    uint8_t version = 1;
    uint8_t connected = 0;
    uint16_t reserved0 = 0;

    uint32_t seq = 0;
    uint32_t uptimeMs = 0;

    uint8_t right = 0;
    uint8_t down = 0;
    uint8_t up = 0;
    uint8_t left = 0;

    uint8_t square = 0;
    uint8_t cross = 0;
    uint8_t circle = 0;
    uint8_t triangle = 0;

    uint8_t l1 = 0;
    uint8_t r1 = 0;
    uint8_t l3 = 0;
    uint8_t r3 = 0;

    uint8_t share = 0;
    uint8_t options = 0;
    uint8_t psButton = 0;
    uint8_t touchpad = 0;

    uint8_t l2Pressed = 0;
    uint8_t r2Pressed = 0;
    uint16_t reserved1 = 0;

    int16_t l2 = 0;
    int16_t r2 = 0;
    int16_t lStickX = 0;
    int16_t lStickY = 0;
    int16_t rStickX = 0;
    int16_t rStickY = 0;
};


int main() {
    
}