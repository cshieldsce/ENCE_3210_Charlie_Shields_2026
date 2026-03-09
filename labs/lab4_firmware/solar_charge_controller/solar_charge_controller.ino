#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ================= OLED ================= */
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* ================= PINS ================= */
#define SOLAR_PIN  A0
#define BAT_PIN    A1

#define THRESHOLD  2.5

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 FAILED"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Solar Controller");
  display.println("Ready!");
  display.display();
  delay(1500);
}

void loop() {
  float solarV = analogRead(SOLAR_PIN) * (5.0 / 1023.0);
  float batV   = analogRead(BAT_PIN)   * (5.0 / 1023.0);

  bool solarActive  = solarV >= THRESHOLD;
  bool charging     = batV < solarV && solarV < THRESHOLD;
  String source     = solarActive ? "SOLAR" : "BATTERY";

  // Serial
  Serial.print("Solar: ");        Serial.print(solarV);
  Serial.print("V | Battery: ");  Serial.print(batV);
  Serial.print("V | Source: ");   Serial.print(source);
  if (charging) Serial.print(" | Charging: BAT -> Solar");
  Serial.println();

  // OLED
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Line 1: voltages
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("SOL:");
  display.print(solarV, 2);
  display.print("V  BAT:");
  display.print(batV, 2);
  display.print("V");

  // Line 2: source big
  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print(source);

  // Line 3: charging indicator
  if (charging) {
    display.setTextSize(1);
    display.setCursor(70, 24);
    display.print("BAT->SOL");
  }

  // // Note A1 fault if stuck high
  // if (batV > 4.9) {
  //   display.setTextSize(1);
  //   display.setCursor(70, 14);
  //   //display.print("[A1 FAULT]");
  // }

  display.display();
  delay(300);
}