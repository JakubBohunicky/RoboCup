#pragma once
#include "world.h"

//namespace World { struct In; }   // iba dopredu


int16_t input_wrap180(int16_t a);  //normalize from -180 to 180


namespace Pheripherials {
  void inputs_init_();
  void inputs_update();
}