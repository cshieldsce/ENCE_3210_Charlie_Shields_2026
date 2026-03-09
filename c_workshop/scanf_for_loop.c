#include <stdio.h>

#define ARRAY_SIZE 10            // Define size of the array

int myArray[ARRAY_SIZE] = { 0 }; // Array to hold input values
int gSum = 0;                    // Global variable to hold sum of values
float gAvg = 0;                  // Global variable to hold average of values

int main()
{
    for (int i=0; i<ARRAY_SIZE; i++) {    // Loop for array size
        scanf("%d", &myArray[i]);         // Read integer input into array
    }
    
    for (int i=0; i<ARRAY_SIZE; i++) {    // Loop for array size
        gSum += myArray[i];               // Add each array element to sum
    }
    gAvg = (float)gSum/(float)ARRAY_SIZE; // Calculate average
    
    printf("Sum: %d\n", gSum);            // Print the sum
    printf("Avg: %.2f", gAvg);            // Print the average
    return 0;
}