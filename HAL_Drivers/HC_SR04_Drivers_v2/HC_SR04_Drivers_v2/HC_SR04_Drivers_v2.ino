#define TRIG_PIN  8
#define LED       13
#define ECHO_PIN  2

volatile uint8_t  gISR_Flag = 0;
volatile uint32_t gCounter_us = 0;

void setup() {
  // Init serial at 115200 bps
  Serial.begin(115200);

  // Init GPIO
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Attach interrupt to Echo pin
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), isr_echo, CHANGE);

  // Init Timer 1 (16 bits) in Normal mode
  // Speed of Timer 1 = 16MHz/prescaler
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS10); // no prescaler
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

    TCNT1 = 0;            // Reset timer
    gCounter_us = 0;      // Reset counter
    TCCR1B |= (1<<CS10);  // Start timer
  }
  else {

    TCCR1B &= ~(1<<CS10); // Stop timer

    gCounter_us = TCNT1;  // Read timer (16 cycles - 1us)
    gCounter_us /= 16;    // convert to us

    gISR_Flag = 1;        // Set flag
  }
}