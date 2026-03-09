/*
 * Fan Controller
 * - Timer2 PWM on Pin 11 (OC2A) ~244Hz for LED/fan
 * - Timer1 interrupt every 50ms to take ADC sample
 * - 10 samples per average (~500ms update rate)
 * - Button1 (D2): toggle fan on/off
 * - Button2 (D3): cycle sensitivity LOW/MED/HI
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ================= OLED ================= */
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* GPIO PINS  */
#define BUTTON_1    2
#define BUTTON_2    3
#define TEMP_PIN    A0
#define FAN_LED_PIN 11

/*  POT RANGE  */
#define TEMP_MIN  0.0
#define TEMP_MAX  50.0

/*  SENSITIVITY  */
const float sensMultiplier[3] = { 0.4, 0.7, 1.0 };
const char* sensLabel[3]      = { "LOW", "MED", "HI" };

/*  STATE  */
volatile bool    gFanOn     = true;
volatile uint8_t gSensLevel = 1;
volatile bool    gBtn1Flag  = false;
volatile bool    gBtn2Flag  = false;

volatile uint8_t gSampleIndex = 0;
volatile long    gSampleSum   = 0.0;
volatile bool    gSampleReady = false;
volatile float   gAvgRaw      = 0.0;

uint8_t gPWMValue = 0;

/* ================= ISRs ================= */
void isr_btn1() {
  static unsigned long lastPress = 0; // simple debounce
  if (millis() - lastPress > 200) {   // 200ms
    gBtn1Flag = true;                 // set flag, actual toggle happens in main loop
    lastPress = millis();
  }
}

void isr_btn2() {
  static unsigned long lastPress = 0; // simple debounce
  if (millis() - lastPress > 200) {   // 200ms
    gBtn2Flag = true;                 // set flag, actual sensitivity change happens in main loop 
    lastPress = millis();
  }
}

ISR(TIMER1_COMPA_vect) {
  int reading = analogRead(TEMP_PIN);         // Read ADC value (0-1023)
  float tempC = map(reading, 0, 1023, 0, 50); // Convert ADC to temperature (0-50C range)
  gSampleSum  += tempC;                       // Accumulate for averaging
  gSampleIndex++;                             // Increment sample count

  OCR2A = gFanOn ? calculatePWM(tempC) : 0;   // Update PWM immediately

  if (gSampleIndex >= 10) {                   // After 10 samples (~500ms)
    gAvgRaw      = gSampleSum / 10.0;         // Calculate average
    gSampleSum   = 0;
    gSampleIndex = 0;
    gSampleReady = true;
  }
}

/*  SETUP  */
void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_1,    INPUT);
  pinMode(BUTTON_2,    INPUT);
  pinMode(FAN_LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_btn1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_btn2, FALLING);

  noInterrupts();

  // Timer2 Fast PWM on pin 11 ~244Hz
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A |= (1 << WGM21) | (1 << WGM20); // Fast PWM mode
  TCCR2A |= (1 << COM2A1);               // Clear OC2A on compare match
  TCCR2B |= (1 << CS22) | (1 << CS21);   // Prescaler 256 -> ~244Hz
  OCR2A = 0;

  // Timer1 CTC every 50ms
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);  // CTC mode
  TCCR1B |= (1 << CS12);   // Prescaler 256
  OCR1A   = 3124;
  TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare interrupt

  interrupts();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 FAILED"));
    for (;;);
  }
  Serial.println("Display OK");

  // Force a real splash immediately so we know it's alive
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Fan Controller");
  display.println("Ready!");
  display.display(); 
  delay(1500);

  Serial.println("Fan Controller Ready");
  Serial.println("Turn pot | BTN1=Fan on/off | BTN2=Sensitivity");
}

void loop() {

  if (gBtn1Flag) {
    gBtn1Flag = false;               // Clear flag
    gFanOn = !gFanOn;                // Toggle fan state
    OCR2A = gFanOn ? gPWMValue : 0;  // Update PWM immediately on fan toggle
    updateDisplay();
    Serial.print(">> Fan: ");
    Serial.println(gFanOn ? "ON" : "OFF"); // Print new state to serial
  }

  if (gBtn2Flag) {
    gBtn2Flag = false;
    gSensLevel = (gSensLevel + 1) % 3; // Cycle sensitivity level
    updateDisplay();
    Serial.print(">> Sens: ");
    Serial.println(sensLabel[gSensLevel]);
  }

  if (gSampleReady) {
    gSampleReady = false;
    gPWMValue = calculatePWM(gAvgRaw); // Update PWM based on new average temperature
    updateDisplay();                   // Refresh OLED with new values

    Serial.print("Temp: "); Serial.print(gAvgRaw, 1); Serial.print("C");
    Serial.print(" | PWM: ");    Serial.print(gPWMValue);
    Serial.print("/255 | Fan:"); Serial.print(gFanOn ? "ON" : "OFF");
    Serial.print(" | Sens: ");   Serial.println(sensLabel[gSensLevel]);
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);


  // Line 1: ADC value and fan state
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp:");
  display.print(gAvgRaw, 1);
  display.print("C");
  display.setCursor(64, 0);
  display.print("FAN:");
  display.print(gFanOn ? "ON " : "OFF");

  // Line 2: PWM bar
  display.setCursor(0, 12);
  display.print("PWM:");
  display.print(gPWMValue);
  int barW = map(gPWMValue, 0, 255, 0, 80);
  display.drawRect(45, 12, 80, 7, SSD1306_WHITE);
  display.fillRect(45, 12, barW, 7, SSD1306_WHITE);

  // Line 3: sensitivity + speed label
  display.setCursor(0, 24);
  display.print("SENS:");
  display.print(sensLabel[gSensLevel]);
  display.setCursor(55, 24);
  if (!gFanOn)             display.print("[ OFF ]");
  else if (gPWMValue == 0) display.print("[ STALL ]");
  else if (gPWMValue < 85) display.print("[ SLOW ]");
  else if (gPWMValue < 170)display.print("[ MED  ]");
  else                     display.print("[ FAST ]");

  display.display();
}

uint8_t calculatePWM(float raw) {
  if (!gFanOn)         return 0;
  if (raw <= TEMP_MIN) return 0;
  if (raw >= TEMP_MAX) return (uint8_t)(255 * sensMultiplier[gSensLevel]);

  float ratio = (raw - TEMP_MIN) / (TEMP_MAX - TEMP_MIN);
  return (uint8_t)(ratio * 255.0 * sensMultiplier[gSensLevel]);
}