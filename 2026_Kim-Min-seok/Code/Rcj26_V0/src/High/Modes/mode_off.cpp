#include "High/Modes/mode_off.h"
#include "Low/Outputs/output_display.h"

static constexpr unsigned char PROGMEM image_arrow_curved_down_right_bits[] = {0x20,0x40,0x40,0xc0,0xe8,0x78,0x38,0x78};
static constexpr unsigned char PROGMEM image_External_ant_1_bits[] = {0x7f,0xff,0xc0,0x80,0x00,0x20,0x88,0x02,0x20,0x92,0x49,0x20,0x94,0xe5,0x20,0x94,0xe5,0x20,0x92,0x49,0x20,0x88,0x42,0x20,0x80,0x40,0x20,0x80,0x00,0x20,0x7f,0xff,0xc0};
static constexpr unsigned char PROGMEM image_arrow_curved_left_down_bits[] = {0x00,0x0e,0x00,0x0e,0x00,0x0e,0x00,0x70,0x00,0x70,0x00,0x70,0x03,0xf0,0x03,0xf0,0x03,0xf0,0x03,0x80,0x03,0x80,0x03,0x80,0xff,0xfe,0xff,0xfe,0xff,0xfe,0x1f,0xf0,0x1f,0xf0,0x1f,0xf0,0x03,0x80,0x03,0x80,0x03,0x80};
static constexpr unsigned char PROGMEM image_arrow_curved_right_up_bits[] = {0x03,0x80,0x03,0x80,0x03,0x80,0x1f,0xf0,0x1f,0xf0,0x1f,0xf0,0xff,0xfe,0xff,0xfe,0xff,0xfe,0x03,0x80,0x03,0x80,0x03,0x80,0x1f,0x80,0x1f,0x80,0x1f,0x80,0x1c,0x00,0x1c,0x00,0x1c,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00};


static void _drawScreen_MAIN() {
        display.setTextColor(SSD1306_WHITE);
        display.setTextWrap(false);
        display.setTextSize(1);

        // External_ant_1
        if(1) display.drawBitmap(108, 1, image_External_ant_1_bits, 19, 11, 1);

        // Gyro S
        display.setTextColor(1);
        display.setTextWrap(false);
        display.setCursor(90, 2);
        display.print("S:");
        display.setCursor(100, 2);
        display.print(IN::gyro.calSys);

        // Mode
        display.setCursor(3, 2);
        if(ST::soccer.role == ST::Types::role_t::Attacker) display.print("Atk");
        else if (ST::soccer.role == ST::Types::role_t::Defender) display.print("Def");
        else display.print("Test");

        // Goal
        display.setCursor(33, 2);
        if(ST::soccer.enemyGoal == ST::Types::goal_t::Yellow) display.print("Yellow");
        else if(ST::soccer.enemyGoal == ST::Types::goal_t::Blue) display.print("Blue");

        // Speed
        display.setCursor(3, 15);
        display.print("Spd:");
        display.setCursor(26, 15);
        display.print(ST::soccer.baseSpeed);

        // Gyro G
        display.setCursor(66, 15);
        display.print("G:");
        display.setCursor(76, 15);
        display.print(IN::gyro.calGyr);

        // Gyro A
        display.setCursor(89, 15);
        display.print("A:");
        display.setCursor(99, 15);
        display.print(IN::gyro.calAcl);

        // Gyro M
        display.setCursor(110, 15);
        display.print("M:");
        display.setCursor(120, 15);
        display.print(IN::gyro.calMag);


        display.setCursor(16, 32);
        display.print(IN::gyro.offset);


        display.setCursor(76, 32);
        display.print("Set Goal");


        display.setCursor(11, 49);
        display.print("Set MODE");


        display.setCursor(77, 49);
        display.print("Set Speed");

        // Start Line
        // if(state == 0)display.drawLine(15, 39, 49, 39, 1);

        // Set Goal line
        if(ST::offMenu.cursor == ST::Types::menu_t::SetGoal) { 
            display.drawLine(75, 39, 122, 39, 1);
            display.drawBitmap(67, 32, image_arrow_curved_down_right_bits, 5, 8, 1);
        }

        // Set Mode line
        if(ST::offMenu.cursor == ST::Types::menu_t::SetRole) {
            display.drawLine(10, 56, 59, 56, 1);
            display.drawBitmap(3, 48, image_arrow_curved_down_right_bits, 5, 8, 1);
        }

        // Set SPD line
        if(ST::offMenu.cursor == ST::Types::menu_t::SetSpeed) {
            display.drawLine(74, 56, 126, 56, 1);
            display.drawBitmap(67, 48, image_arrow_curved_down_right_bits, 5, 8, 1);
        }

        display.drawLine(1, 25, 126, 25, 1);
        // main lines
        display.drawLine(64, 26, 64, 63, 1);
        // main lines
        display.drawLine(1, 44, 127, 44, 1);


}

static void _drawScreen_SetSPEED() {

    // Layer 1
    display.setTextColor(1);
    display.setTextSize(3);
    display.setTextWrap(false);
    display.setCursor(13, 4);
    display.print("Speed:");


    // arrow_curved_right_up
    display.drawBitmap(99, 30, image_arrow_curved_right_up_bits, 15, 21, 1);

    // arrow_curved_left_down
    display.drawBitmap(11, 31, image_arrow_curved_left_down_bits, 15, 21, 1);


    // Layer 1 copy 1
    display.setTextSize(2);
    display.setCursor(40, 36);
    display.print(ST::soccer.baseSpeed);

}



namespace Mode {

    void off() {
        OUT::motorAcc.motEn = false;
        OUT::display.needsUpdate = true;

        if(ST::offMenu.state == ST::Types::menu_t::SetSpeed) {
            _drawScreen_SetSPEED();
        } else { _drawScreen_MAIN(); }
    } 
}