/* 
 * Question 2
 * 
 * Write a program in C language such that:
 * (a) It contains a function that calculates the cosine of a given angle in degrees;
 * (b) Your program should calculate the cosine of angles between 0 and 360 degrees
 * using your function. The results should be saved in an array.
 * 
 */

#include <math.h>
float cosine[361];                                // array to store cosine values

void setup() {
  Serial.begin(9600);                             // Start serial at 9600 baud rate
  
  for (int degrees=0; degrees<=360; degrees++) {  // for loop from 0 to 360
     float radians = degrees * ( 3.14 / 180.0);   // convert degrees to radians
     cosine[degrees] = cos(radians);              // calculate cosine
     Serial.print(degrees);                       // print the degrees
     Serial.print(", "); 
     Serial.println(cosine[degrees]);             // print the cosine value
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
