#include "world.h"
#include "Low/inputs.h"
#include "High/Services/logic.h"
#include "Low/outputs.h"


void setup()
{
    Pheripherials::inputs_init_();
    Pheripherials::outputs_init_();
}

void loop()
{
    Pheripherials::inputs_update();



    
    Pheripherials::outputs_update();
}