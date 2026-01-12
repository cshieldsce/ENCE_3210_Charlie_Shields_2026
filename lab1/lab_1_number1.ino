unsigned long result[512];

void setup() {
  Serial.begin(9600); // Start serial at 9600 baud rate
  calculate();
}

void loop() {
}

int two_quad(int n) { // function to compute 2*n^2
  return 2*n*n;  
}

void calculate() {
  for (int i=1; i<=512; i++) {  // loop from 1 to 512
    result[i] = two_quad(i);    // call the two_quad function
    Serial.print(i);            // print the index
    Serial.print(":");
    Serial.println(result[i]);  // print the result
  }
}
