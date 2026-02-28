#include <Arduino.h>
#include "world.h"
#include "Low/inputs.h"
#include "High/Services/logic.h"
#include "Low/outputs.h"

void setup()
{
    Serial.begin(921600);
    Serial.print("rcj26 V0 TIME:  "); Serial.print(__TIME__); Serial.print("  DATA:  "); Serial.println(__DATE__);
    Pheripherials::inputs_init_();
    Pheripherials::outputs_init_();
    ST::resetToDefaults();
}

void loop()
{
    Pheripherials::inputs_update();
    Logic::determineMode();
    Logic::applyMode();

    
    Pheripherials::outputs_update();
}