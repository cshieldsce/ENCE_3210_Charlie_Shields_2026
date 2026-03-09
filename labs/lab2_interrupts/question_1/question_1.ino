/* Question 1 
 *  
 * Write a C program to count the difference between 
 * the number of times two different buttons arepressed.
 * a) The button pressing operation should be defined in an ISR.
 * b) Observe the count value from the watch window.
 * c) If button 1 is pressed more than button 2, then turn on 
 * the red color LED. If the button pressed numbers is equal, 
 * then turn on the blue color LED. Otherwise, turn on the green color LED.
 * If the button press numbers are equal, then turn on the blue color LED.
 *  
 */

#define LED_GREEN 4                                       // Green LED pin
#define LED_RED 5                                         // Red LED pin
#define BUTTON_1 2                                        // First button pin
#define BUTTON_2 3                                        // Second button pin

volatile int gISRButton = 0;                              // Button press flag
volatile int gISRPressCount1 = 0;                         // Number of button presses
volatile int gISRPressCount2 = 0;                         // Number of button presses

void setup() {
  Serial.begin(9600);                                     // Start serial at 9600 baud rate

  pinMode(LED_GREEN, OUTPUT);                             // Set LED pins as output
  pinMode(LED_RED, OUTPUT);

  pinMode(BUTTON_1, INPUT_PULLUP);                        // Setup buttons as input with pullup resistor
  pinMode(BUTTON_2, INPUT_PULLUP);

  // Setup interrupt to button pin on falling edge
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_button2, FALLING);
}

void loop() {
  int pressCount1;                                        // Local variable to hold button press counts
  int pressCount2;

  noInterrupts();
  pressCount1 = gISRPressCount1;                          // get press count
  pressCount2 = gISRPressCount2;                          // get press count
  interrupts();

  // Print the button press counts
  Serial.print("Button 1: ");
  Serial.print(pressCount1);
  Serial.print(" Button 2: ");
  Serial.println(pressCount2);

  // If button 1 pressed more, turn on red LED
  if (pressCount1 > pressCount2) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
  }
  // If button 2 pressed more, turn on green LED
  else if (pressCount2 > pressCount1) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }
  // If both buttons pressed equal times, turn on both LEDs
  else if (pressCount1 != 0 && pressCount2 != 0 ) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
  }

  // Wait for a second
  delay(1000);
}

void isr_button1() {  
  // Check if button is pressed
  if (digitalRead(BUTTON_1) == LOW) {
      gISRPressCount1++;                                     // Increment press count
  }
}

void isr_button2() {  
  // Check if button is pressed
  if (digitalRead(BUTTON_2) == LOW) {
      gISRPressCount2++;                                     // Increment press count
  }
}
