#include <stdio.h>
#include <math.h>
#include <string.h>

struct s_Quadratic {
    float x1;
    float x2;
};

struct s_Quadratic quadratic(int a, int b, int c) 
{
    struct s_Quadratic x;
    x.x1 = 0;
    x.x2 = 0;
    
    float x_s = sqrt(b * b - 4 * a * c);
    
    if (x_s >= 0) {
        x.x1 = (-b + x_s) / (2 * a);
        x.x2 = (-b - x_s) / (2 * a);
    }
    return x; 
}

int main()
{
    struct s_Quadratic y;
    y = quadratic(1, -5, 6);   
    
    printf("value: %.2f, %.2f", y.x1, y.x2);

    return 0;
}