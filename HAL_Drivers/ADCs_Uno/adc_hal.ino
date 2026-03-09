#define POT_1 A0
#define TIMER_COMPARE_VALUE 625 //100ms

volatile char gFlag = 0;
int gPot_1 = 0;

void setup() {
  // Initialize analog input
  pinMode(POT_1, INPUT);

  // Initialize serial port
  Serial.begin(115200);

  // Configure ADC
  ADMUX |= (1 << REFS0);                                // use AVCC as ref voltage
  ADCSRB = (1 << ADTS2) | (1 << ADTS0);                 // trigger source: timer/counter 1 compare match B
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC prescalar: 128

  // Configure Timer1
  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = TIMER_COMPARE_VALUE;  // compare match register
  OCR1B = TIMER_COMPARE_VALUE;  // compare same value to COMPB
  TCCR1B |= (1 << WGM12);       // CTC mode
  TCCR1B |= (1 << CS12);        // 256 prescaler
  TIMSK1 |= (1 << OCIE1B);      // enable timer compare interrupt

  ADCSRA |= (1 << ADATE);                             // enable adc automatic triggering
  ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADSC);  // start the adc

  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (gFlag) {
    // reset isr flag
    gFlag = 0;

    // print value
    Serial.print(1024);
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    Serial.println(gPot_1);
  }
}

ISR(ADC_vect) {
  // set isr flag
  gFlag = 1;

  // read the result from the ADC macro
  gPot_1 = ADC;
}

EMPTY_INTERRUPT(TIMER1_COMPB_vect);