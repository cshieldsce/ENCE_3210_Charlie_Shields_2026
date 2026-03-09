/* Question 1
 * 
 * Write a program in C language such that: 
 * (a) It contains a function that calculates twice the square of a given integer; 
 * (b) Your program should calculate twice the square of numbers between 0 and 511
 * using your function. The results should be saved in an array.
 * 
 */

void setup() {
  Serial.begin(9600);           // Start serial at 9600 baud rate
  calculate();                  // Call the calculate function
}

void loop() {
}

int two_quad(int n) {           // function to compute 2*n^2
  return 2*n*n;  
}

void calculate() {
  double result[512];           // array to store results

  for (int i=1; i<=511; i++) {  // loop from 1 to 512
    result[i] = two_quad(i);    // call the two_quad function
    Serial.print(i);            // print the index
    Serial.print(":");
    Serial.println(result[i]);  // print the result
  }
}
