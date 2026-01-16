/* Question 6
 * 
 * We would like to turn on and off the red, green, and blue LEDs in a sequence. 
 * Therefore, write a C program with the following specifications:
 * a) When the button is pressed, turn on the red, green, and blue color LEDs 
 *    with the followingorder: R – RG – RGB – GB – B – RB
 * b) This procedure is repeated until the button is pressed again
 * 
 */

#define LED_GREEN 4                // Green LED pin
#define LED_RED 5                  // Red LED pin
#define BUTTON_1 2                 // Button pin

#define TIME 1000                  // Time delay in milliseconds

int isrLEDFlag = 0;                // Flag for ISR to control LED sequence

void setup() {
  Serial.begin(9600);              // Start serial at 9600 baud rate

  pinMode(LED_GREEN, OUTPUT);      // Set LED pins as output
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_RED, LOW);      // Turn off LEDs
  digitalWrite(LED_GREEN, LOW);

  pinMode(BUTTON_1, INPUT);        // Set button pin as input
  
  // Setup interrupt to button pin on state change
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button, CHANGE);
}

void loop() {
  if (isrLEDFlag) {                // If the flag is set run sequence:
    digitalWrite(LED_RED, HIGH);   // Turn on red LED
    delay(TIME);                   // Wait
    digitalWrite(LED_GREEN, HIGH); // Turn on green LED
    delay(TIME);                   // Wait
    digitalWrite(LED_RED, LOW);    // Turn off red LED
    delay(TIME);                   // Wait
    digitalWrite(LED_GREEN, LOW);  // Turn off green LED
    delay(TIME);                   // Wait
    isrLEDFlag = ~isrLEDFlag;      // Reset flag to stop sequence
  }
}

void isr_button() {
  // Check if button pressed
  if (digitalRead(BUTTON_1)) {
    isrLEDFlag = ~isrLEDFlag;      // Toggle flag 
  }
}
