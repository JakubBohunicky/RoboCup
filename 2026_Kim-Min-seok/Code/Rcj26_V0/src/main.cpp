#include "world.h"
#include "Low/inputs.h"
#include "Low/outputs.h"

void setup()
{
    Pheripherials::inputs_init_();
}

void loop()
{
    Pheripherials::inputs_update();
    
}