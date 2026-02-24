#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


static Adafruit_SSD1306 display(128, 64, &Wire);

void drawScreen_1(void);

  int state = 1;
  bool wifi = true;
  int gyroS = 3;
  int gyroG = 2;
  int gyroA = 1;
  int gyroM = 0;
  bool goal = true;
  int mode = 0;
  int speed = 100;
  float gyroOffset = 67.69;
  bool robotOn = false;
  uint32_t robotLastOnTime = 0;
  bool speedMenu = false;


  bool btnPlusClick = false;
  bool  btnMinusClick = false;

  bool  btnPlusLongPress = false;
  bool  btnMinusLongPress = false;

  bool  btnPlusIsDown = false;
  bool  btnMinusIsDown = false;




// #include <Wire.h>
// #include <FastADC_Mux.h>
// #include "Low/config_hw.h"
#include "driver/gpio.h"

struct BTNs { //button state4
    gpio_num_t pin;
    bool LastPos = false;
    bool StablePos = false;
    uint32_t ChangeTime = 0;

    bool Click = false;
    bool LongPress = false;
    bool IsDown = false;
    
    uint32_t PressStartTime = 0;
    bool LongSent = false;
};

constexpr int BTN_DEBOUNCE_MS = 20;
constexpr int BTN_LONGPRESS_MS = 500;

BTNs btnSPlus;
BTNs btnSMinus;

// void I2C_FastADC_init_() {

//     Wire.begin(HW::GenericCfg::I2C_SDA_Pin, HW::GenericCfg::I2C_SCL_Pin);
//     Wire.setClock(400000); //MAX 800kHz

//     fadcInit(8, HW::LineCfg::Line_A_Read_Pin, HW::LineCfg::Line_B_Read_Pin, HW::LineCfg::Line_X_Read_Pin, HW::MotionSenseCfg::A_Spd_Pin, HW::MotionSenseCfg::B_Spd_Pin, HW::MotionSenseCfg::C_Spd_Pin, HW::MotionSenseCfg::D_Spd_Pin, HW::MotionSenseCfg::DRBFR_Spd_Pin);

// }


void input_generic_init_() {
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);
    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_25, GPIO_PULLUP_ONLY);

    // gpio_set_direction(HW::GenericCfg::BukajModule_Pin, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(HW::GenericCfg::BukajModule_Pin, GPIO_PULLUP_ONLY);    

    btnSMinus.pin = GPIO_NUM_25;
    btnSPlus.pin = GPIO_NUM_4;
}



static void _input_generic_btn_update(BTNs& btn) {
    btn.Click = false;
    btn.LongPress = false;
    uint32_t now = millis();

    bool raw = !gpio_get_level(btn.pin); //active LOW

    if(raw != btn.StablePos) { //edge detection
        if(now - btn.ChangeTime >= BTN_DEBOUNCE_MS) { //debounde
            btn.StablePos = raw;
            btn.ChangeTime = now;
            
            if(btn.StablePos == true) {
              btn.PressStartTime = now;
              btn.LongSent = false;
            }
        }
    }

    btn.IsDown = btn.StablePos;
    btn.Click = (btn.LastPos == true && btn.StablePos == false && btn.LongSent == false);

    if(btn.StablePos == true && btn.LongSent == false) {
        if(now - btn.PressStartTime >= BTN_LONGPRESS_MS) {
            btn.LongPress = true;
            btn.LongSent = true; //dont send again
        }
    }

    btn.LastPos = btn.StablePos;
}

void input_generic_update() {

    // IN::generic.bukajModuleEn = gpio_get_level(HW::GenericCfg::BukajModule_Pin);

    _input_generic_btn_update(btnSPlus);
    _input_generic_btn_update(btnSMinus);

    btnPlusClick = btnSPlus.Click;
    btnMinusClick = btnSMinus.Click;

    btnPlusLongPress = btnSPlus.LongPress;
    btnMinusLongPress = btnSMinus.LongPress;

    btnPlusIsDown = btnSPlus.IsDown;
    btnMinusIsDown = btnSMinus.IsDown;
}


void state_update() {


    if(robotOn) {
        if(btnMinusIsDown || btnPlusIsDown) {
            robotOn = false;
            robotLastOnTime = millis();
        }
    }

    if(speedMenu == false) {

        if(btnPlusClick && millis() - robotLastOnTime >= 1000) {
            robotOn = true;
        }

        // Serial.println("After");
        if(btnMinusClick) state++;
        //   if(btnPlusClick) state++;
        //   if(btnPlusLongPress) state += 10;
        //   if(btnMinusLongPress) state -= 10;

        if(state > 2) state = 0;
        // if(state < 0) state = 3;


        if(btnMinusLongPress) {gyroOffset = random(0, 359.99);}

    }

    switch (state)
    {
    case 0: 
            if(btnPlusLongPress) {
                goal = !goal;
            }
        break;
    case 1: 
            if(btnPlusLongPress) {
                mode++;
                if(mode >= 3) mode = 0;
            }

        break;
    case 2:
            if(speedMenu == true && (btnPlusLongPress || btnMinusLongPress)) speedMenu = false;

            else if(btnPlusLongPress && speedMenu == false) {
                speedMenu = true;
            }

            if(speedMenu) {
                if(btnPlusClick) speed += 5;
                if(btnMinusClick) speed -= 5;

            }
        break;
    default:
        break;
    }
}

void setup() {
  Serial.begin(115200);

  Serial.print(__TIME__);
  Serial.print("   ");
  Serial.println(__DATE__);

  Wire.begin(21, 22);
  Wire.setClock(400000); //MAX 800kHz

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // skús 0x3D ak nič
    Serial.println("SSD1306 begin failed");
  }

  input_generic_init_();
  
  display.display();
  display.clearDisplay();
  display.display();
}

//MENU:
//GYRO RESET
//BRANKA
//SPEED

void loop() {
  // Serial.println("before");
  input_generic_update();

    state_update();
    display.clearDisplay();
    drawScreen_1();
    display.display();

}



static const unsigned char PROGMEM image_arrow_curved_down_right_bits[] = {0x20,0x40,0x40,0xc0,0xe8,0x78,0x38,0x78};

static const unsigned char PROGMEM image_External_ant_1_bits[] = {0x7f,0xff,0xc0,0x80,0x00,0x20,0x88,0x02,0x20,0x92,0x49,0x20,0x94,0xe5,0x20,0x94,0xe5,0x20,0x92,0x49,0x20,0x88,0x42,0x20,0x80,0x40,0x20,0x80,0x00,0x20,0x7f,0xff,0xc0};

static const unsigned char PROGMEM image_EviSmile1_bits[] = {0x0f,0x00,0x00,0x0f,0x00,0x0f,0x00,0x00,0x0f,0x00,0x3c,0x00,0x00,0x03,0xc0,0x3c,0x00,0x00,0x03,0xc0,0xfc,0x00,0x00,0x03,0xf0,0xfc,0x00,0x00,0x03,0xf0,0xff,0x0f,0xff,0x0f,0xf0,0xff,0x0f,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0xfc,0xff,0xff,0xf3,0xf0,0xfc,0xff,0xff,0xf3,0xf0,0xfc,0x3f,0xff,0xc3,0xf0,0xfc,0x3f,0xff,0xc3,0xf0,0xfc,0x0f,0xff,0x03,0xf0,0xfc,0x0f,0xff,0x03,0xf0,0xfc,0x03,0xfc,0x03,0xf0,0xfc,0x03,0xfc,0x03,0xf0,0xff,0x03,0xfc,0x0f,0xf0,0xff,0x03,0xfc,0x0f,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xcf,0xff,0x3f,0xc0,0x3f,0xcf,0xff,0x3f,0xc0,0x0f,0xf3,0x0c,0xff,0x00,0x0f,0xf3,0x0c,0xff,0x00,0x03,0xfc,0x03,0xfc,0x00,0x03,0xfc,0x03,0xfc,0x00,0x00,0xff,0xff,0xf0,0x00,0x00,0xff,0xff,0xf0,0x00,0x00,0x0f,0xff,0x00,0x00,0x00,0x0f,0xff,0x00,0x00};

static const unsigned char PROGMEM image_arrow_curved_left_down_bits[] = {0x00,0x0e,0x00,0x0e,0x00,0x0e,0x00,0x70,0x00,0x70,0x00,0x70,0x03,0xf0,0x03,0xf0,0x03,0xf0,0x03,0x80,0x03,0x80,0x03,0x80,0xff,0xfe,0xff,0xfe,0xff,0xfe,0x1f,0xf0,0x1f,0xf0,0x1f,0xf0,0x03,0x80,0x03,0x80,0x03,0x80};

static const unsigned char PROGMEM image_arrow_curved_right_up_bits[] = {0x03,0x80,0x03,0x80,0x03,0x80,0x1f,0xf0,0x1f,0xf0,0x1f,0xf0,0xff,0xfe,0xff,0xfe,0xff,0xfe,0x03,0x80,0x03,0x80,0x03,0x80,0x1f,0x80,0x1f,0x80,0x1f,0x80,0x1c,0x00,0x1c,0x00,0x1c,0x00,0xe0,0x00,0xe0,0x00,0xe0,0x00};



void drawScreen_1(void) {

    display.setTextColor(SSD1306_WHITE);
    display.setTextWrap(false);
    display.setTextSize(1);

    if(robotOn) {

        display.drawBitmap(50, 11, image_EviSmile1_bits, 36, 42, 1);
    }
    
    else if(speedMenu) {

        // Layer 1
        display.setTextColor(1);
        display.setTextSize(3);
        display.setTextWrap(false);
        display.setCursor(13, 4);
        display.print("Speed:");

        // Layer 1 copy 1
        display.setCursor(35, 31);
        display.print(speed);

        // arrow_curved_right_up
        display.drawBitmap(99, 30, image_arrow_curved_right_up_bits, 15, 21, 1);

        // arrow_curved_left_down
        display.drawBitmap(11, 31, image_arrow_curved_left_down_bits, 15, 21, 1);

    }

    else {
        // External_ant_1
        if(wifi) display.drawBitmap(108, 1, image_External_ant_1_bits, 19, 11, 1);

        // Gyro S
        display.setTextColor(1);
        display.setTextWrap(false);
        display.setCursor(90, 2);
        display.print("S:");
        display.setCursor(100, 2);
        display.print(gyroS);

        // Mode
        display.setCursor(3, 2);
        if(mode == 0) display.print("Atk");
        else if (mode == 1) display.print("Def");
        else display.print("Test");

        // Goal
        display.setCursor(33, 2);
        if(goal) display.print("Yellow");
        else display.print("Blue");

        // Speed
        display.setCursor(3, 15);
        display.print("Spd:");
        display.setCursor(26, 15);
        display.print(speed);

        // Gyro G
        display.setCursor(66, 15);
        display.print("G:");
        display.setCursor(76, 15);
        display.print(gyroG);

        // Gyro A
        display.setCursor(89, 15);
        display.print("A:");
        display.setCursor(99, 15);
        display.print(gyroA);

        // Gyro M
        display.setCursor(110, 15);
        display.print("M:");
        display.setCursor(120, 15);
        display.print(gyroM);


        display.setCursor(16, 32);
        display.print(gyroOffset);


        display.setCursor(76, 32);
        display.print("Set Goal");


        display.setCursor(11, 49);
        display.print("Set MODE");


        display.setCursor(77, 49);
        display.print("Set Speed");

        // Start Line
        // if(state == 0)display.drawLine(15, 39, 49, 39, 1);

        // Set Goal line
        if(state == 0)display.drawLine(75, 39, 122, 39, 1);

        // Set Mode line
        if(state == 1)display.drawLine(10, 56, 59, 56, 1);

        // Set SPD line
        if(state == 2)display.drawLine(74, 56, 126, 56, 1);


        // arrow_curved_down_right START
        // if(state == 0)display.drawBitmap(7, 31, image_arrow_curved_down_right_bits, 5, 8, 1);

        // Layer 24
        // display.drawLine(74, 56, 126, 56, 1);

        // arrow_curved_down_right copy Set Goal
        if(state == 0)display.drawBitmap(67, 32, image_arrow_curved_down_right_bits, 5, 8, 1);


        // arrow_curved_down_right copy Set Mode
        if(state == 1)display.drawBitmap(3, 48, image_arrow_curved_down_right_bits, 5, 8, 1);

        // arrow_curved_down_right Set Speed
        if(state == 2)display.drawBitmap(67, 48, image_arrow_curved_down_right_bits, 5, 8, 1);



        // main lines
        display.drawLine(1, 25, 126, 25, 1);


        // main lines
        display.drawLine(64, 26, 64, 63, 1);

        // main lines
        display.drawLine(1, 44, 127, 44, 1);


    }

}
