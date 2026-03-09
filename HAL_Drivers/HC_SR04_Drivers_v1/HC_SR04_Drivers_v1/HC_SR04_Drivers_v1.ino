#define TRIG_PIN  8
#define LED       13
#define ECHO_PIN  2

#define TIMER_COMPARE_VALUE 127 // 8us

volatile uint8_t  gISR_Flag = 0;
volatile uint32_t gCounter_us = 0;

void setup() {
  // Init serial at 115200 bps
  Serial.begin(115200);

  // Init GPIO
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), isr_echo, CHANGE);

  // Init Timer 1 (16 bits)
  // Speed of Timer 1 = 16MHz/prescaler
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = TIMER_COMPARE_VALUE;
  TCCR1B |= (1<<WGM12);  // CTC mode
  //TCCR1B |= (1<<CS12); // no prescaler
  TIMSK1 |= (1<<OCIE1A); // enable timer compare interrupt
  interrupts();
}

void loop() {
  // Trigger Signal - 10us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  if (gISR_Flag) {
    gISR_Flag = 0;

    float distance = (float)(gCounter_us*8) / 58.0; // convert us to cm
    Serial.print(gCounter_us);
    Serial.print(" - ");
    Serial.println(distance);
  }

  // delay - 60ms
  delay(60);
}

void isr_echo() {
  // Check Echo
  if (digitalRead(ECHO_PIN)) {
    // Start timer
    gCounter_us = 0;
    TCCR1B |= (1<<CS10);
  }
  else {
    // End timer
    TCCR1B &= ~(1<<CS10);
    gISR_Flag = 1;
  }
}

ISR(TIMER1_COMPA_vect){
  gCounter_us++;
}
