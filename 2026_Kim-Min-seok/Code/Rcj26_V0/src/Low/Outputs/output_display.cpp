#include "Low/Outputs/output_display.h"
#include "Low/config_hw.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


static Adafruit_SSD1306 display(HW::DisplayCfg::width, HW::DisplayCfg::height, &Wire);

void output_display_init_() {
    display.setRotation(2);
    display.display();
}

void output_display_update() {

}