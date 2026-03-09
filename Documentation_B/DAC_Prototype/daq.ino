/* DAQ Prototype Code
* Writes a counting pattern to 5 DAC output pins.
* Used for testing DAC functionality.
*/

int dacPins[5] = {8, 7, 6, 5, 4}; // DAC output pins
int gCounter = 0;                 // Global counter variable

void setup() {
  Serial.begin(9600);
  
  /* Initialize all DAC pins as outputs */
  for (int i = 0; i < 5; i++) {
    pinMode(dacPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 31; i++) {                        // Count from 0 to 30 (2^8 = 32)
    gCounter = (gCounter + 1) % 32;                     // Increment counter (wrap around at 32)

    for (int j = 0; j < 5; j++) {                       // Cycle through each DAC pin
      digitalWrite(dacPins[j], (gCounter >> j) & 0x01); // Set each pin according to the corresponding bit
    }
    delay(10);                                          // Short delay for stability
  }
}