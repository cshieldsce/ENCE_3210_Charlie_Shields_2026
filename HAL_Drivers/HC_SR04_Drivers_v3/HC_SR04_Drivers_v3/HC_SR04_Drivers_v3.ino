
#define TRIG_PIN  8
#define LED       13
#define ECHO_PIN  2

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Trigger Signal - 10us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration*0.0343)/2;

  Serial.print("Distance :");
  Serial.println(distance);

  // delay - 60ms
  delay(60);
}

