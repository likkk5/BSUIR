#include <iostream>

int main()
{
    double x, y, z;
    std::cin >> x;
    std::cin >> y;
    std::cin >> z;
    if ((x > 0) && (y > 0) && (z > 0) && (x + y > z) && (x + z > y) && (y + z > x))
    {
        std::cout << "YES" << "\n";
    }
    else
    {
        std::cout << "NO" << "\n";
    }



    return 0;
}