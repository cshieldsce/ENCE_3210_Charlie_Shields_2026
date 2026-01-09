#include <stdio.h>

#define ARRAY_SIZE 10

int myArray[ARRAY_SIZE] = { 0 };
int gSum = 0;
float gAvg = 0;

int main()
{
    for (int i=0; i<ARRAY_SIZE; i++) {
        scanf("%d", &myArray[i]);
    }
    
    for (int i=0; i<ARRAY_SIZE; i++) {
        gSum += myArray[i];
    }
    gAvg = (float)gSum/(float)ARRAY_SIZE;
    
    printf("Sum: %d\n", gSum);
    printf("Avg: %.2f", gAvg);
    return 0;
}