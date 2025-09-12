#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
int main()
{
    int m=20;
    double a=0, b=M_PI/2, h, x, y;
    h = (b - a) / m;
    for ( int i=0; i<=m; i++)
    {
        x = a + i * h;
        y = sin(x) - cos(x);
        std::cout << y << "\n";
    }
    return 0;
}