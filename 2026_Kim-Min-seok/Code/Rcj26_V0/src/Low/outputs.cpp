#include "Low/outputs.h"
#include "Low/Outputs/output_LED.h"

void outputs_init_() {
    output_LED_init_();
}

void outputs_update() {
    output_LED_update();
}

//int out_pwm = 102 + input * (921 - 102);