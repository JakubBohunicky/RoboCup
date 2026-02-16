#include <WiFi.h>
#include <FastLED.h>
#include <ESP32Ping.h>   // [web:112]

IPAddress laptopIP(192,168,1,2);  // zmeň na IP tvojho notebooku

bool present = false;
int failCount = 0;

const unsigned long pingIntervalMs = 3000;
const int maxFails = 3;
unsigned long lastPing = 0;



const char* ssid = "-";
const char* password = "3141592653589";

WiFiServer server(80);
String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

// FastLED
#define LED_TYPE     WS2812B
#define COLOR_ORDER  GRB
#define DATA_PIN     2
#define NUM_LEDS     52
// #define BRIGHTNESS   255

CRGB leds[NUM_LEDS];

uint8_t gHue = 0;
unsigned long lastAnim = 0;
const unsigned long animIntervalMs = 20; // rýchlosť animácie


// UI states
int brightness = 128;  // default
bool ledEnabled = false;
int ledMode = 4;                 // tu bude "cislo statu"
const int MODE_MIN = 0;
const int MODE_MAX = 9;

static String getParam(const String& req, const String& key) {
  // Hladá "key=" v prvej riadke requestu: GET /set?key=... HTTP/1.1
  int q = req.indexOf('?');
  if (q < 0) return "";
  int sp = req.indexOf(' ', q);
  if (sp < 0) return "";
  String qs = req.substring(q + 1, sp);

  String needle = key + "=";
  int k = qs.indexOf(needle);
  if (k < 0) return "";

  int vStart = k + needle.length();
  int amp = qs.indexOf('&', vStart);
  if (amp < 0) amp = qs.length();
  return qs.substring(vStart, amp);
}
 
void renderMode(int mode) {
  switch (mode) {
    case 0: fill_solid(leds, NUM_LEDS, CRGB::Black); break;
    case 1: fill_solid(leds, NUM_LEDS, CRGB::Red); break;
    case 2: fill_solid(leds, NUM_LEDS, CRGB::Green); break;
    case 3: fill_solid(leds, NUM_LEDS, CRGB::Blue); break;
    case 4:
      // moving rainbow: hue sa mení v čase
      fill_rainbow(leds, NUM_LEDS, gHue, 7);
      break;
    default: fill_solid(leds, NUM_LEDS, CRGB::White); break;
  }
  FastLED.show();
}

void setup() {
  Serial.begin(115200);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  FastLED.clear(true);

  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}




void presenceTick() {
  if (millis() - lastPing < pingIntervalMs) return;
  lastPing = millis();

  bool ok = Ping.ping(laptopIP, 1);   // 1 echo request [web:112]
  if (ok) {
    failCount = 0;
    present = true;
  } else {
    failCount++;
    if (failCount >= maxFails) present = false;
  }

  ledEnabled = present;   // keď notebook online -> svieti, offline -> zhasne
}





void loop() {
  // ak je enable, zobraz zvolený mode (tu máš len statický render; pre animácie urob non-blocking)

  presenceTick();

  if (ledEnabled) {
  if (millis() - lastAnim >= animIntervalMs) {
    lastAnim = millis();
    gHue++;              // posun farieb
  }
  renderMode(ledMode);
} else {
  FastLED.clear(true);
}

  WiFiClient client = server.available();
  if (!client) return;

  currentTime = millis();
  previousTime = currentTime;
  Serial.println("New Client.");
  String currentLine = "";

  while (client.connected() && currentTime - previousTime <= timeoutTime) {
    currentTime = millis();
    if (!client.available()) continue;

    char c = client.read();
    header += c;

    if (c == '\n') {
      if (currentLine.length() == 0) {
        // --- spracuj request
        // Enable/Disable: /set?en=1 alebo /set?en=0
        if (header.indexOf("GET /set?") >= 0) {
          String en = getParam(header, "en");
          String mode = getParam(header, "mode");

          String br = getParam(header, "br");
          if (br.length()) {
            int b = br.toInt();
            if (b < 0) b = 0;
            if (b > 255) b = 255;
            brightness = b;
            FastLED.setBrightness(brightness);   // runtime zmena jasu [web:135]
            Serial.printf("brightness=%d\n", brightness);
          }


          if (en.length()) {
            ledEnabled = (en == "1");
            Serial.printf("ledEnabled=%d\n", (int)ledEnabled);
          }
          if (mode.length()) {
            int m = mode.toInt();
            if (m < MODE_MIN) m = MODE_MIN;
            if (m > MODE_MAX) m = MODE_MAX;
            ledMode = m;
            Serial.printf("ledMode=%d\n", ledMode);
          }
        }

        // --- odpoveď + HTML
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        client.println("<!DOCTYPE html><html><head>");
        client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
        client.println("<link rel=\"icon\" href=\"data:,\">");
        client.println("<style>");
        client.println("html{font-family:Helvetica;display:inline-block;margin:0px auto;text-align:center;}");
        client.println(".button{background-color:#3db441;border:none;color:white;padding:14px 28px;font-size:22px;margin:6px;cursor:pointer;}");
        client.println(".button2{background-color:#555555;}");
        client.println("</style></head><body>");

        client.println("<h1>PEDO LION FILIP PAVLOVIC PREDSEDA KOMISIE x GRAY GOOSE LED CONTROL</h1>");

        client.print("<p>Diddy party level: ");
        client.print(brightness);
        client.println("</p>");

        client.print("<input type='range' min='0' max='255' value='");
        client.print(brightness);
        client.println("' oninput=\"fetch('/set?br='+this.value)\">");

        // Enable button
        client.print("<p>Cigi party: ");
        client.print(ledEnabled ? "ON" : "OFF");
        client.println("</p>");

        if (!ledEnabled) {
          client.println("<p><a href=\"/set?en=1\"><button class=\"button\">ENABLE</button></a></p>");
        } else {
          client.println("<p><a href=\"/set?en=0\"><button class=\"button button2\">DISABLE</button></a></p>");
        }

        // Mode selector (cislo statu)
        client.print("<p>Vyber vek obete pre Epsteina: ");
        client.print(ledMode);
        client.println("</p>");

        for (int m = MODE_MIN; m <= MODE_MAX; m++) {
          client.print("<a href=\"/set?mode=");
          client.print(m);
          client.print("\"><button class=\"button\">");
          client.print(m);
          client.println("</button></a>");
        }

        client.println("</body></html>");
        client.println();

        break;
      } else {
        currentLine = "";
      }
    } else if (c != '\r') {
      currentLine += c;
    }
  }

  header = "";
  client.stop();
  Serial.println("Client disconnected.\n");
}
