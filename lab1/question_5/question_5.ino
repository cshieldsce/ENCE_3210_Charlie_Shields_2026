/* Question 5
 * 
 * Detect a specified pattern with three entries in an array. The pattern is saved in 
 * another array. When the pattern is detected, the green color LED will turn on. 
 * If the pattern is not detected, the red color LED will turn on at the end of the program. 
 * Your program should count the number of occurrences of the pattern.
 * 
 */

#define LED_GREEN 4
#define LED_RED 5

int gTarget[] = {1, 3, 4, 1, 2, 3, 0, 4, 3, 5, 1, 2, 3};       // target array
int gPattern[] = {1, 2, 3};                                    // pattern to detect

void setup() {
  Serial.begin(9600);                                          // Start serial at 9600 baud rate
  int targetLength = sizeof(gTarget) / sizeof(gTarget[0]);     // calculate size of target array
  int patternLength = sizeof(gPattern) / sizeof(gPattern[0]);  // calculate size of pattern array

  int matchCount = 0;                                          // counter for pattern matches

  // For loop to search for pattern in target array 
  // only search where pattern can fit
  for (int i = 0; i<=targetLength-patternLength; i++) {
    int match = 1;                                             // default match is true
    // Inner for loop to check for pattern match
    for (int j = 0; j < patternLength; j++) {
      if (gTarget[i + j] != gPattern[j]) {
        match = 0;                                             // only set match to false if a mismatch is found
        break;                                                 // exit inner loop early on mismatch
      }
    }
    // If no mismatches found, increment match count
    if (match == 1) {
      matchCount++;
    }
  }

  // Print the number of matches
  Serial.print("Matches: ");
  Serial.println(matchCount);

  // Turn on LEDs based on whether matches were found
  if (matchCount > 0) {
    digitalWrite(LED_GREEN, HIGH);                             // Turn on green LED if pattern found
    digitalWrite(LED_RED, LOW);                                // Turn off red LED
  } else {
    digitalWrite(LED_GREEN, LOW);                              // Turn off green LED
    digitalWrite(LED_RED, HIGH);                               // Turn on red LED if pattern not found
  }
}

void loop() {
}
