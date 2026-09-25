// #include <Arduino.h>
// #include <ps5Controller.h>

// #define Robot_A true

// constexpr int BTN_DEBOUNCE_MS = 20;
// constexpr int BTN_LONGPRESS_MS = 500;

// namespace ST {
//     uint32_t now_ms;
// }

// namespace _Raw {
//     struct BTNs { //button state
//         gpio_num_t pin;
//         bool LastPos = false;
//         bool StablePos = false;
//         uint32_t ChangeTime = 0;

//         bool Click = false;
//         bool LongPress = false;
//         bool IsDown = false;
        
//         uint32_t PressStartTime = 0;
//         bool LongSent = false;
//     };

//     struct Controller {
//         char BT_MAC[18] = "FF:FF:FF:FF:FF:FF";
//         bool connected = false;

//         BTNs Right;
//         BTNs Down;
//         BTNs Up;
//         BTNs Left;

//         BTNs Square;
//         BTNs Cross;
//         BTNs Circle;
//         BTNs Triangle;

//         BTNs L1;
//         BTNs R1;
//         BTNs L3;
//         BTNs R3;

//         BTNs Share;
//         BTNs Options;
//         BTNs PSButton;
//         BTNs Touchpad;

//         int16_t L2;
//         int16_t R2;

//         int16_t LStickX;
//         int16_t LStickY;
//         int16_t RStickX;
//         int16_t RStickY;
//     };
// }

// namespace IN {
//     _Raw::Controller controller;
// }

// namespace HW {


//     namespace Controller{
//         constexpr const char* BT_MAC_A = "1a:2b:3c:01:01:01";
//         constexpr const char* BT_MAC_B = "1a:2b:3c:01:01:01";
//     }
    
// }

// static void _input_generic_btn_update(_Raw::BTNs& btn, bool raw) {
//     btn.Click = false;
//     btn.LongPress = false;

//     if (raw != btn.StablePos) {
//         if (ST::now_ms - btn.ChangeTime >= BTN_DEBOUNCE_MS) {
//             btn.StablePos = raw;
//             btn.ChangeTime = ST::now_ms;

//             if (btn.StablePos) {
//                 btn.PressStartTime = ST::now_ms;
//                 btn.LongSent = false;
//             }
//         }
//     }

//     btn.IsDown = btn.StablePos;
//     btn.Click = (btn.LastPos == true && btn.StablePos == false && btn.LongSent == false);

//     if (btn.StablePos == true && btn.LongSent == false) {
//         if (ST::now_ms - btn.PressStartTime >= BTN_LONGPRESS_MS) {
//             btn.LongPress = true;
//             btn.LongSent = true;
//         }
//     }

//     btn.LastPos = btn.StablePos;
// }


// void input_controller_ps5_init_() {
//     if(Robot_A) {
//         strcpy(IN::controller.BT_MAC, HW::Controller::BT_MAC_A);
//     } else {
//         strcpy(IN::controller.BT_MAC, HW::Controller::BT_MAC_B);
//     }

//     ps5.begin(IN::controller.BT_MAC);
// }




// void input_controller_ps5_update() {
//     IN::controller.connected = ps5.isConnected();

//     if(IN::controller.connected == true) {

//         _input_generic_btn_update(IN::controller.Right,    ps5.Right());
//         _input_generic_btn_update(IN::controller.Down,     ps5.Down());
//         _input_generic_btn_update(IN::controller.Up,       ps5.Up());
//         _input_generic_btn_update(IN::controller.Left,     ps5.Left());

//         _input_generic_btn_update(IN::controller.Square,   ps5.Square());
//         _input_generic_btn_update(IN::controller.Cross,    ps5.Cross());
//         _input_generic_btn_update(IN::controller.Circle,   ps5.Circle());
//         _input_generic_btn_update(IN::controller.Triangle, ps5.Triangle());

//         _input_generic_btn_update(IN::controller.L1,       ps5.L1());
//         _input_generic_btn_update(IN::controller.R1,       ps5.R1());

//         _input_generic_btn_update(IN::controller.Share,    ps5.Share());
//         _input_generic_btn_update(IN::controller.Options,  ps5.Options());
//         _input_generic_btn_update(IN::controller.L3,       ps5.L3());
//         _input_generic_btn_update(IN::controller.R3,       ps5.R3());

//         _input_generic_btn_update(IN::controller.PSButton, ps5.PSButton());
//         _input_generic_btn_update(IN::controller.Touchpad, ps5.Touchpad());

//         IN::controller.L2 = ps5.L2Value();
//         IN::controller.R2 = ps5.R2Value();

//         IN::controller.LStickX = ps5.LStickX();
//         IN::controller.LStickY = ps5.LStickY();
//         IN::controller.RStickX = ps5.RStickX();
//         IN::controller.RStickY = ps5.RStickY();

        

//         if (ps5.Right()) Serial.println("Right Button");
//         if (ps5.Down()) Serial.println("Down Button");
//         if (ps5.Up()) Serial.println("Up Button");
//         if (ps5.Left()) Serial.println("Left Button");

//         if (ps5.Square()) Serial.println("Square Button");
//         if (ps5.Cross()) Serial.println("Cross Button");
//         if (ps5.Circle()) Serial.println("Circle Button");
//         if (ps5.Triangle()) Serial.println("Triangle Button");

//         if (ps5.UpRight()) Serial.println("Up Right");
//         if (ps5.DownRight()) Serial.println("Down Right");
//         if (ps5.UpLeft()) Serial.println("Up Left");
//         if (ps5.DownLeft()) Serial.println("Down Left");

//         if (ps5.L1()) Serial.println("L1 Button");
//         if (ps5.R1()) Serial.println("R1 Button");

//         if (ps5.Share()) Serial.println("Share Button");
//         if (ps5.Options()) Serial.println("Options Button");
//         if (ps5.L3()) Serial.println("L3 Button");
//         if (ps5.R3()) Serial.println("R3 Button");

//         if (ps5.PSButton()) Serial.println("PS Button");
//         if (ps5.Touchpad()) Serial.println("Touch Pad Button");

//         if (ps5.L2()) {
//         Serial.printf("L2 button at %d\n", ps5.L2Value());
//         }
//         if (ps5.R2()) {
//         Serial.printf("R2 button at %d\n", ps5.R2Value());
//         }

//         if (ps5.LStickX()) {
//         Serial.printf("Left Stick x at %d\n", ps5.LStickX());
//         }
//         if (ps5.LStickY()) {
//         Serial.printf("Left Stick y at %d\n", ps5.LStickY());
//         }
//         if (ps5.RStickX()) {
//         Serial.printf("Right Stick x at %d\n", ps5.RStickX());
//         }
//         if (ps5.RStickY()) {
//         Serial.printf("Right Stick y at %d\n", ps5.RStickY());
//         }

//         Serial.println();

//     }
// }


// void setup() {
//     input_controller_ps5_init_();
// }


// void loop() {
//     ST::now_ms = millis();
//     input_controller_ps5_update();
// }