/* Question 4
 * 
 * Write a C program such that the global integer array x with 10 elements will be filled initially.
 * For this problem, fill it at the beginning of the code. When an interrupt comes from button 1 the 
 * ISR will be called. The ISR will calculate the global integer array y defined 
 * as 𝑦[𝑛] = 2 ∗ 𝑥[𝑛] − 𝑥[𝑛 − 1] where 𝑛 is the index for the array. In fact, this is a 
 * simple filtering operation working with interrupts. In the actual application, the interrupt 
 * should come from some other source. The array 𝑥 should also be filled by other module or a peripheral (such as ADC).
 * 
 */

#define BUTTON_1 2                    
#define ARRAY_SIZE 10

int gTarget[ARRAY_SIZE];
int gResult[ARRAY_SIZE];

volatile int gISRCalculate = 0;

void setup() {
  Serial.begin(9600);                                     // Start serial at 9600 baud rate
  pinMode(BUTTON_1, INPUT);                               // Setup buttons as input with pullup resistor

  // Populate array
  for (int i = 0; i<=ARRAY_SIZE-1; i++) {
    gTarget[i] = i;
  }

  // Setup interrupt to button pin on any change
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button, FALLING);
}

void loop() {
  if (gISRCalculate)
  {
    Serial.print("--------------------\n");
    for (int i = 0; i<=ARRAY_SIZE-1; i++) {
      gResult[i] = 2 * gTarget[i] - gTarget[i-1];

      Serial.print("Target Value: ");
      Serial.print(gTarget[i]);
      Serial.print("  Result Value: ");
      Serial.println(gResult[i]);
    }
    gISRCalculate = ~gISRCalculate;
  }
}

void isr_button() {
  gISRCalculate = ~gISRCalculate;
}
