#include <stdio.h>
#include <math.h>
#include <string.h>

struct s_Quadratic // Structure to hold the roots for quadratic equation
{ 
    float x1;      // First root
    float x2;      // Second root
};

struct s_Quadratic quadratic(int a, int b, int c) 
{
    struct s_Quadratic x;                // Instance of structure to hold roots
    x.x1 = 0;                            // Set roots to 0
    x.x2 = 0;                            // Set roots to 0
    
    float x_s = sqrt(b * b - 4 * a * c); // Calculate square root part of quadratic formula
    
    if (x_s >= 0) {                      // Check if roots are real numbers
        x.x1 = (-b + x_s) / (2 * a);     // Calculate first root
        x.x2 = (-b - x_s) / (2 * a);     // Calculate second root
    }
    return x;                            // Return the structure with the roots
}

int main()
{
    struct s_Quadratic y;                    // Instance of structure to hold roots
    y = quadratic(1, -5, 6);                 // Call quadratic function
    
    printf("value: %.2f, %.2f", y.x1, y.x2); // Print the roots

    return 0;
}