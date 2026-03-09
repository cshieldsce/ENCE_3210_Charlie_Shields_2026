/* Lab 3 - Asynchronous Tasks
 * 
 * Build the program with the following specs: 
 * 1. You will have 2 tasks running simultaneously and 1 foreground task (the main task).
 * 2. Each task has a respective timer running at a certain frequency (Task1 = 1 Hz, Task2 = 10 Hz).
 * 3. Task 1 is responsible for blinking the Green LED at a rate of 1 Hz. It is also responsible for incrementing a counter that will be used by the main task as a “timer”.
 * 4. Task 2 (running at 10 Hz) is responsible for reading an input pin (Button) and if it is equals to 1 it turns on the Red LED otherwise it turns off the Red LED.
 * 5. The input pin can be either Button 1 or Button 2 on your board.
 * 6. The main task (foreground task) prints over the serial port every 3 seconds a message of your choice. It uses the counter from task 1 as a “timer”. *[Note: pay attention to variables that should be declared as volatile]*
 * 7. Provide a block diagram of your code showing how the tasks interact with each other.
 * 
 */

#define LED_GREEN 4                                   // Green LED at pin 4
#define LED_RED 5                                     // Red LED at pin 5                   
#define BUTTON_1 2                                    // Button 1 at pin 2
#define TIMER_COMPARE_VALUE 1562                      // For 10 Hz with 16 MHz clock and 1024 prescaler

volatile int gTimer = 0;                              // Counts number of 100 ms intervals
volatile bool gButton1State = false;                  // State of BUTTON_1

/*
 * Setup function to initialize pins and Timer1
 */
void setup() {
  pinMode(LED_GREEN, OUTPUT);                         // Setup Green LED as output
  pinMode(LED_RED, OUTPUT);                           // Setup Red LED as output
  pinMode(BUTTON_1, INPUT);                           // Setup Button 1 as input
  Serial.begin(9600);                                 // Start serial communication at 9600 bps

  /* Configure Timer1 for 10 Hz */
  noInterrupts();                                     // Disable interrupts during timer setup             
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 7;   // toggle after counting to 8
  TCCR1A |= (1 << COM1A0);   // Toggle OC1A on Compare Match.
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1 << CS10);     // clock on, no pre-scaler      
  interrupts();                               // Enable interrupts
}

/*
 * Loop that updates button state and prints message
 */
void loop() {
  gButton1State = (digitalRead(BUTTON_1) == HIGH);    // Update button state
  
  if (gTimer >= 30) {                                 // 3 secs / 100 ms = 30
    Serial.println("3 seconds have passed!");         // Print message  
    gTimer = 0;                                       // Reset timer
  }
}

/*
 * Timer interrupt routine that handles both tasks
 */
ISR(TIMER1_COMPA_vect) { 
  static int greenCounter = 0;                        // Local counter for green LED timing
  gTimer++;                                           // Increment timer every 100 ms (10hz)

  /* Green LED: 1 Hz */
  greenCounter++;                                     // Increment green LED counter
  if (greenCounter >= 5) {                            // 1 Hz = every 5 * 100 ms      
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN)); // Toggle green LED
    greenCounter = 0;                                 // Reset green LED counter
  }

  /* Red LED: 10 Hz */
  if (gButton1State) {                                // If button is pressed
    digitalWrite(LED_RED, !digitalRead(LED_RED));     // Toggle red LED
  } else {
    digitalWrite(LED_RED, LOW);                       // Turn off red LED if button not pressed
  }
}