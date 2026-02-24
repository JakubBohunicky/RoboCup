#include "High/Modes/mode_off.h"
#include "Low/Outputs/output_display.h"

namespace Mode {
    void off() {
        output_display_update();
    } 
}