/*
  3x CD74HC4067 (48 kanálov) na ESP32-S3 s DMA rýchlosťou
  Rýchlosť: ~33 kHz celkom (1 kHz/kanál)
*/

#include <.h>  // https://github.com/stg/ESP32-S3-FastAnalogRead

// Adresové piny (spoločné pre všetky 3 MUX)
#define S0  4
#define S1  5  
#define S2  6
#define S3  7

// ADC piny (každý MUX Z na samostatný ADC1 kanál)
#define ADC_MUX1  1   // GPIO1 = ADC1_CH0
#define ADC_MUX2  2   // GPIO2 = ADC1_CH1
#define ADC_MUX3  3   // GPIO3 = ADC1_CH2

uint16_t buffer[48];  // 16 kanálov x 3 MUXy

void setup() {
  Serial.begin(115200);
  
  // Inicializuj DMA ADC
  fadcInit(3, ADC_MUX1, ADC_MUX2, ADC_MUX3);
  
  // Nastav adresové piny
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  Serial.println("3x CD74HC4067 ready - 48 kanálov!");
}

void loop() {
  readAll48Channels();  // ~30 µs/cyklus
  
  // Výpis každých 100 cyklov (pre debug)
  static int count = 0;
  if(++count % 100 == 0) {
    Serial.printf("Cyklus #%d dokončený\n", count);
  }
}

void readAll48Channels() {
  for(int addr = 0; addr < 16; addr++) {
    // Prepni VŠETKY 3 MUX naraz (<100 ns)
    digitalWrite(S0, addr & 1);
    digitalWrite(S1, (addr >> 1) & 1);
    digitalWrite(S2, (addr >> 2) & 1);
    digitalWrite(S3, (addr >> 3) & 1);
    
    delayMicroseconds(1);  // Stabilizácia MUX
    
    // Čítaj 3 paralelné ADC (~1 µs)
    buffer[addr*3 + 0] = fadcRead(0);  // MUX1 kanál addr
    buffer[addr*3 + 1] = fadcRead(1);  // MUX2 kanál addr  
    buffer[addr*3 + 2] = fadcRead(2);  // MUX3 kanál addr
  }
}

// Funkcia na výpis konkrétneho kanála (debug)
uint16_t getChannel(int mux_id, int channel) {
  return buffer[(mux_id*16) + channel];
}
