//#include <ArduinoOTA.h>
#include <FastLED.h>

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN    11        // často funguje GPIO5; zmeň podľa zapojenia
#define buttonVoltage 4
#define buttonSense 2 
#define NUM_LEDS    52
#define BRIGHTNESS  255

int16_t state = 4;

CRGB leds[NUM_LEDS];

void setup() {

  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // WS2812B na DATA_PIN [web:74]
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);

  pinMode(buttonVoltage, OUTPUT);
  pinMode(buttonSense, INPUT_PULLUP);
  digitalWrite(buttonVoltage, 0);

  
  // fill_solid(leds, NUM_LEDS, CRGB::White); FastLED.show();

  //while (WiFi.status() != WL_CONNECTED) delay(100);

  //WiFi.setSleep(false);   // raz stačí [web:126]

  //ArduinoOTA.begin();
  
}

void loop() {

  Serial.print(digitalRead(buttonSense));
  Serial.print("    ");
 
  static uint8_t last = HIGH;
  uint8_t cur = digitalRead(buttonSense);

  if (last == LOW && cur == HIGH) { // pustenie pri INPUT_PULLUP
    state++;
    delay(30); // debounce
  }
  last = cur;


  if(state > 6) state = -1;

  Serial.println(state);


  switch (state)
  {
  case 0:{
    fill_solid(leds, NUM_LEDS, CRGB::White);   FastLED.show();
    break;}
  case 1:{
    fill_solid(leds, NUM_LEDS, CRGB::Red);   FastLED.show();
    break;}
  case 2:{
    fill_solid(leds, NUM_LEDS, CRGB::Green);   FastLED.show();
    break;}
  case 3:{
    fill_solid(leds, NUM_LEDS, CRGB::Blue);   FastLED.show();
    break;}
  case 4:{
    static uint8_t hue = 0;
    fill_rainbow(leds, NUM_LEDS, hue, 7);
    FastLED.show();
    hue++;
    delay(20);
    break;}
  case 5:{
    static uint8_t hue5 = 0;
    fill_rainbow(leds, NUM_LEDS, hue5, 7);
    FastLED.show();
    hue5++;
    //delay(20);
    break;}
  case 6:{
    static uint8_t t = 0;

    // Hue rozsah (0-255): dolaď si podľa oka
    uint8_t hueMin6 = 140;   // modrá-ish
    uint8_t hueMax6 = 220;   // ružová/fialová-ish

    // plynulý pohyb tam a späť (sinus)
    uint8_t hue6 = hueMin6 + scale8(sin8(t), (uint8_t)(hueMax6 - hueMin6));

    fill_solid(leds, NUM_LEDS, CHSV(hue6, 255, 255));  // CHSV -> CRGB [web:135]
    FastLED.show();

    t++;                 // rýchlosť zmeny
    delay(20);

    break;}
  // case 7:{
  //   fill_solid(leds, NUM_LEDS, CRGB::White);   FastLED.show();
  //   break;}
  // case 8:{
  //   fill_solid(leds, NUM_LEDS, CRGB::White);   FastLED.show();
  //   break;}
  default:{
      fill_solid(leds, NUM_LEDS, CRGB::Black);   FastLED.show();
    break;}
  }


  //ArduinoOTA.handle();
  // 1) Jednoduché farby
  // fill_solid(leds, NUM_LEDS, CRGB::Red);   FastLED.show(); delay(2000);
  // fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); delay(2000);
  // fill_solid(leds, NUM_LEDS, CRGB::Blue);  FastLED.show(); delay(2000);

  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::Cyan1);  FastLED.show(); delay(2000);
  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::Cyan2);  FastLED.show(); delay(2000);
  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::Cyan3);  FastLED.show(); delay(2000);
  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::Cyan4);  FastLED.show(); delay(2000);
  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::Cyan);  FastLED.show(); delay(2000);
  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::DarkCyan);  FastLED.show(); delay(2000);
  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::LightCyan);  FastLED.show(); delay(2000);
  // fill_solid(&leds[NUM_LEDS - 4], 4, CRGB::White);  FastLED.show(); delay(2000);

  //2) Rainbow efekt
  // static uint8_t hue = 0;
  // fill_rainbow(leds, NUM_LEDS, hue, 7);
  // FastLED.show();
  // hue++;
  // delay(20);





  // static uint8_t t = 0;

  // // Hue rozsah (0-255): dolaď si podľa oka
  // uint8_t hueMin = 140;   // modrá-ish
  // uint8_t hueMax = 220;   // ružová/fialová-ish

  // // plynulý pohyb tam a späť (sinus)
  // uint8_t hue = hueMin + scale8(sin8(t), (uint8_t)(hueMax - hueMin));

  // fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));  // CHSV -> CRGB [web:135]
  // FastLED.show();

  // t++;                 // rýchlosť zmeny
  // delay(20);
}
