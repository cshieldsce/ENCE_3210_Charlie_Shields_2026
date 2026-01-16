/* Question 7
 * 
 *  We would like to develop a simple calculator with the following specifications:
 *  a) There will be three arrays each with 10 elements. The first two arrays will have integer numbers.
 *     The third array will be empty. We will apply arithmetic operations on the first two arrays.
 *  b) When the button is pressed once, a counter will be incremented once. This will correspond to
 *     the addition operation. The red color LED will turn on.
 *  c) When the button is pressed twice, the counter will be incremented twice. This will correspond
 *     to the subtraction operation. The green color LED will turn on.
 *  d) When the button is pressed three times, the counter will be incremented thrice. This will
 *     correspond to the multiplication operation. The blue color LED will turn on.
 *  e) When a second button is pressed, the selected operation will be applied on the two elements of
 *     the first and second arrays. The result will be saved in the third array and all LEDs will turn off.
 *     The operation will be applied to all remaining array elements. When all the results are saved, all
 *     LEDs will turn on.
 * 
 */

#define LED_GREEN 4                                       // Green LED pin
#define LED_RED 5                                         // Red LED pin
#define BUTTON_1 2                                        // First button pin
#define BUTTON_2 3                                        // Second button pin
#define TIMER_COMPARE_VALUE 6250                          // 100ms

int gCalc1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};          // First integer array
int gCalc2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};          // Second integer array
int gCalc3[10];                                           // Result array

volatile unsigned long gISRTimer = 0;                     // Timer variable
volatile int gISRButton = 0;                              // Button press flag
volatile unsigned long gISRLastPressTime = 0;             // Last button press time
volatile int gISRPressCount = 0;                          // Number of button presses

void setup() {
  Serial.begin(9600);                                     // Start serial at 9600 baud rate

  pinMode(LED_GREEN, OUTPUT);                             // Set LED pins as output
  pinMode(LED_RED, OUTPUT);

  pinMode(BUTTON_1, INPUT_PULLUP);                        // Setup buttons as input with pullup resistor
  pinMode(BUTTON_2, INPUT_PULLUP);

  // Setup interrupt to button pin on any change
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button, CHANGE);

  // Initialize Timer1 (16 bit)
  // Speed = 16Mhz/256 = 62.5kHz
  noInterrupts();
  TCCR1A=0;
  TCCR1B=0;
  OCR1A=TIMER_COMPARE_VALUE;                              // compare match register 16Mhz/256
  TCCR1B |= (1<<WGM12);                                   // CTC mode

  // Start Timer by setting the prescaler
  TCCR1B |= (1<<CS12);                                    // 256 prescler
  TIMSK1 |= (1<<OCIE1A);                                  // enable timer compare interrupt
  interrupts();
}
void loop() {
  unsigned long currentTime; 
  unsigned long lastPressTime;
  int count;

  currentTime = gISRTimer;                                // get current time
  lastPressTime = gISRLastPressTime;                      // get last press time
  count = gISRPressCount;                                 // get press count

  // Reset the press count if more than 1 second has passed
  // since the clock is in 100ms increments, 10 increments = 1 second
  if ((currentTime - lastPressTime > 10) && (count != 0)) {
    gISRPressCount = 0;                                   // reset press count
    count = 0;                                            // Update local variable so LEDs update immediately
  }

  // Update the LEDs based on the count value to show operation (ADD, SUB, MUL)
  if (count == 0) {
    digitalWrite(LED_RED, LOW);                           // Red LED off
    digitalWrite(LED_GREEN, LOW);                         // Green LED off
  } 
  else if (count == 1) {                                  // Addition
    digitalWrite(LED_RED, HIGH);                          // Red LED on
    digitalWrite(LED_GREEN, LOW);                         // Green LED off
  } 
  else if (count == 2) {                                  // Subtraction
    digitalWrite(LED_RED, LOW);                           // Red LED off
    digitalWrite(LED_GREEN, HIGH);                        // Green LED on
  } 
  else if (count == 3) {                                  // Multiplication
    digitalWrite(LED_RED, HIGH);                          // Red LED on
    digitalWrite(LED_GREEN, HIGH);                        // Green LED on
  }

  // Second button pressed:
  // Perform calculation based on count value
  if (digitalRead(BUTTON_2) == HIGH && count > 0) {
    
    digitalWrite(LED_RED, LOW);                           // Turn off Red LED
    digitalWrite(LED_GREEN, LOW);

    Serial.println("Starting Calculation...");

    // For loop going through array and performing selected operation
    for (int i = 0; i < 10; i++) {
      if (count == 1) { 
        gCalc3[i] = gCalc1[i] + gCalc2[i];                // Addition
      }      
      else if (count == 2) {
        gCalc3[i] = gCalc1[i] - gCalc2[i];                // Subtraction
      }
      else if (count == 3) {
        gCalc3[i] = gCalc1[i] * gCalc2[i];                // Multiplication
      }
      
      // Print the result
      Serial.print("Index ");
      Serial.print(i);
      Serial.print(": "); 
      Serial.println(gCalc3[i]);
    }

    // All calculations done turn on all LEDs
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);

    // Wait before allowing next calculation
    delay(3000);
    
    // Reset counter
    gISRPressCount = 0;
  }

  // Small delay
  delay(100); 
}

ISR(TIMER1_COMPA_vect) {
  gISRTimer++;                                            // Increment timer every 100ms
}

void isr_button() {
  unsigned long currentTime = gISRTimer;                  // Get the current time
  
  // If the current time minus the last press time is greater than 200ms,
  // consider it a new press and increment the press count
  if (currentTime - gISRLastPressTime > 2) { 
    gISRPressCount++;                                     // Increment press count
    
    if (gISRPressCount > 3) {
      gISRPressCount = 3;                                 // Only allow up to 3 presses (only 3 operations)
    }

    gISRLastPressTime = currentTime;                      // Update the time to current time
  }
  
}
