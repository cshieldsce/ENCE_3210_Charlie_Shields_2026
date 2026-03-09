/*!
* @brief Timer 2 FAST PWM
*
* https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm/
*
* Date: 2/11/2024
*/
#define RED_LED   8
#define GREEN_LED 4
#define BLUE_LED  7

// Timer 0 PWM Pins
#define PIN_5     5  // OC0A -> RGB_BLUE
#define PIN_6     6  // OC0B -> RGB_GREEN

// Timer 1 PWM Pins
#define PIN_9     9   // OC1A -> RGB_RED
#define PIN_10    10  // OC1B

// Timer 2 PWM Pins
#define PIN_11    11  // OC2A
#define PIN_3     3   // OC2B -> BUTTON_2

void setup() {
  // Initialize serial
  Serial.begin(9600);

  // Initialize LEDs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Initialize PWM Pins
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_5, OUTPUT);
  pinMode(PIN_6, OUTPUT);
  pinMode(PIN_9, OUTPUT);
  pinMode(PIN_10, OUTPUT);
  pinMode(PIN_11, OUTPUT);

  // Initialize Timer2 (8bit)
  // Speed of Timer2 = 16MHz/64 = 250kHz
  TCCR2A = 0;
  TCCR2B = 0;

  // Waveform Mode
  TCCR2A |= (1<<WGM21) | (1<<WGM20);  // FAST PWM OCR1A TOP
  TCCR2B |= (1<<WGM22); 
  // Control
  TCCR2A |= (1<<COM2A0) | (1<<COM2B1); 
  // Start Timer by setting the prescaler
  TCCR2B |= (1<<CS22);  // 64 prescaler

  OCR2A = 180;  // FAST PWM Frequency -> 250kHz/(180+1) = 1.38kHz
}

void loop() 
{
  // idle
  for(int i=0; i<180; i++){
    OCR2B = i;
    //delayMicroseconds(500); 
    delay(10);
  }
}
