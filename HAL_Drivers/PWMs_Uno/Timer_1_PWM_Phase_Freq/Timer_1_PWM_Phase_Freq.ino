/*!
* @brief Question 4
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

// 50 = 16,000,000 / (2 * 64 * TOP)
// TOP = 2500
#define ICR1_TOP 2500

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

  // Initialize Timer1 (16bit)
  // Speed of Timer1 = 16MHz/1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;  // Reset timer

  // Waveform Mode: 8 - PWM, Phase Frequency Correct 
  TCCR1B |= (1<<WGM13);
  // Setting Compare Output Modes
  TCCR1A |= (1<<COM1A1) | (1<<COM1B1);
  // Start Timer by setting the prescaler
  TCCR1B |= (1<<CS10) | (1<<CS11); // 1024 prescaler

  ICR1 = ICR1_TOP;  // Set ICR1 TOP -> 16MHz/2/Prescaler/ICR1
  OCR1A = 125;
  OCR1B = 125;
}

void loop() 
{
  // // idle
  // for(int i=0; i<2400*0.05; i++){
  //   OCR1A = i;
  //   OCR1B = i;
  //   delayMicroseconds(200); 
  // }
}




