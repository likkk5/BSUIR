#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
    long double R, P, Q;
    std::cin >> R >> P >> Q;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Incorrect input";
        return 0;
    }

    if ((P > 0) && (R > 0) && (Q > 0) && (Q < 90))
    {
        if ((R - (P * sin(Q*M_PI/180)) / 2) <= 1.0e-15)
        {
            std::cout << "YES"; // шар входит
        }
        else
        {
            std::cout << "NO"; // не входит
        }
    }
    else
    {
        std::cout << "Incorrect data";
    }
    return 0;
}