/* 
 * Question 3
 * 
 * You have to search for the second maximum of a given integer array 
 * with 50 elements. The array is saved as a global variable in the program. 
 * Write the results to the memory location just after the array ends.
 * 
 */

#define ARRAY_SIZE 50                      // Define size of the array
int gArr[ARRAY_SIZE] = { 0 };              // Global array to hold values with size ARRAY_SIZE

int gMax = 0;                              // Global variable to hold the maximum value
int g2Max = 0;                             // Global variable to hold second maximum value

void setup() {
  Serial.begin(9600);                      // Start serial at 9600 baud rate
  
  for ( int i=0; i<=ARRAY_SIZE-1; i++ ) {  // Initialize array for values 0 to 49
    gArr[i] = i;      
  }

  // Iterate through array to find max value
  for ( int i=0; i<=ARRAY_SIZE-1; i++ ) {
    if (gArr[i] > gMax) {                  // If current value >  max
      g2Max = gMax;                        // Update second max to previous max
      gMax = gArr[i];                      // Update max to current value
    }
    else if (gArr[i] > g2Max) {            // If current value > second max 
      g2Max = gArr[i];                     // Update second max to current value
    }
  }
  
  Serial.print("Max value: ");             // Print max and second max values
  Serial.println(gMax);
  Serial.print("Second max value: ");
  Serial.println(g2Max);
}

void loop() {
}
