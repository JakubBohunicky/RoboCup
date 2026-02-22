#include "Low/Outputs/output_LED.h"
#include "Low/config_hw.h"
#include "FastLED.h"

static CRGB LEDs_O[HW::LEDsCfg::LED_O_num];
static CRGB LEDs_X[HW::LEDsCfg::LED_X_num];


void output_LED_init_() {
    FastLED.addLeds<WS2812B, HW::LEDsCfg::LEDSetO_Pin, GRB>(LEDs_O, HW::LEDsCfg::LED_O_num);
    FastLED.addLeds<WS2812B, HW::LEDsCfg::LEDSet_Xdebug_Pin, GRB>(LEDs_X, HW::LEDsCfg::LED_X_num);
    FastLED.setBrightness(OUT::led_O.brightness);
    FastLED.clear(true);
}


static void _output_LED_set_O() {
    for (uint8_t i = 0; i < HW::LEDsCfg::LED_O_num; ++i) { //zapis do vsetkych O
        LEDs_O[i] = OUT::led_O.color;
    }
}


static void _output_LED_set_X() {
    for (uint8_t i = HW::LEDsCfg::LED_DEBUG_num; i < HW::LEDsCfg::LED_X_num; ++i) { //zapis do vsetkych X
        LEDs_X[i] = OUT::led_X.color;
    }
}



static void _output_LED_set_DEBUG() {
    for (uint8_t i = 0; i < HW::LEDsCfg::LED_DEBUG_num; ++i) { //zapis do vsetkych DEBUG
        LEDs_X[i] = OUT::led_Debug.color;
    }
}


void output_LED_update() {
    if(OUT::led_O.needsUpdate) { _output_LED_set_O(); OUT::led_O.needsUpdate = false;}
    if(OUT::led_X.needsUpdate) { _output_LED_set_X(); OUT::led_X.needsUpdate = false; }
    if(OUT::led_Debug.needsUpdate) { _output_LED_set_DEBUG(); OUT::led_Debug.needsUpdate = false; }

    FastLED.show();
}



