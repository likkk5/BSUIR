
#include <iostream>
#include <iomanip>
#include <cmath> 

int main()
{
    std::cout << std::setprecision(20);
    long double a, b, c, d, z;
    std::cin >> a >> b >> c >> d;
    if (c == 0)
    {
        std::cout << "ERROR" << "\n";
    }
    else
    {
        if ((c >= d) && (a < d))
        {
            z = a + b / c;
        }
        else
        {
            if ((c < d) && (a >= d))
            {
                z = a - b / c;
            }
            else
            {
                z = 0;
            }
        }
        std::cout << z <<"\n";
    }
    return 0;
}