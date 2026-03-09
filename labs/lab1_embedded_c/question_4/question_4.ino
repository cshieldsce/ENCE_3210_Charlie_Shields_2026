/* Question 4
 *  
 *  Find the R, G, and B letters in an array. If the letters are detected, 
 *  the red, green, and blue colors LEDs will turn on, respectively. 
 *  Your program should count the number of occurrences of each letter 
 *  in the array.
 *  
 */

#define LED_GREEN 4
#define LED_RED 5
 
char gSentence[] = "Really Great Boots are Made of Leather"; // test sentence input array

void setup() {
  Serial.begin(9600);                                  // Start serial at 9600 baud rate

  pinMode(LED_GREEN, OUTPUT);                          // Set LED pins as output
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_GREEN, LOW);                        // Turn off LEDs
  digitalWrite(LED_RED, LOW); 

  // Counters for R, G, B (set to zero)
  int countRed = 0;
  int countGreen= 0;
  int countBlue = 0;

  int size = sizeof(gSentence) / sizeof(gSentence[0]); // calculate size of array

  // Loop through the array and count occurrences of R, G, B
  for (int i = 0; i<=size-1; i++) {
    if (gSentence[i] == 'R') {
      countRed++;                                      // increment red counter
    } 
    else if (gSentence[i] == 'G') {
      countGreen++;                                    // increment green counter
    } 
    else if (gSentence[i] == 'B') {
      countBlue++;                                     // increment blue counter
    }
  }

  // Turn on LEDs based on count
  if (countRed>0) {
    digitalWrite(LED_RED, HIGH);                       // turn on red LED
  }
  if (countGreen>0) {
    digitalWrite(LED_GREEN, HIGH);                     // turn on green LED
  }
  // NO BLUE LED
  //  if (countBlue>0) {                 
  //    digitalWrite(LED_BLUE, HIGH);
  //  }

  // Print counts to Serial Monitor
  Serial.print("Red Count: ");
  Serial.println(countRed);
  Serial.print("Green Count: ");
  Serial.println(countGreen);
  Serial.print("Blue Count: ");
  Serial.println(countBlue);
}

void loop() {
}
