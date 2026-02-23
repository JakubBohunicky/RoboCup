#include "world.h"
#include "Low/inputs.h"
#include "High/Services/logic.h"
#include "Low/outputs.h"


void setup()
{
    Pheripherials::inputs_init_();
    Pheripherials::outputs_init_();
    ST::resetToDefaults();
}

void loop()
{
    Pheripherials::inputs_update();
    Logic::determineMode();

    
    Pheripherials::outputs_update();
}