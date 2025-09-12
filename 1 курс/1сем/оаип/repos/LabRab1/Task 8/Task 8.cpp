
#include <iostream>


int main()
{
    int h1, min1, h2, min2, h, min, x;
    std::cin >> h1 >> min1;
    std::cin >> h2 >> min2;
    if ((h1 >= 0) && (h1 <= 23) && (min1 >= 0) && (min1 <= 59) && (h2 >= 0) && (h2 <= 23) && (min2 >= 0) && (min2 <= 59))
    {
        if ((h1 < h2) || ((h1=h2) && (min1<=min2)))
        {
            x = h2 * 60 + min2 - h1 * 60 - min1; // minutes
            h = x / 60;
            min = x % 60;
            std::cout << h << " " << min;
        }
        else
        {
            std::cout << "End time less than start time";
        }
    }
    else
    {
        std::cout << "Incorrect data";
    }
    return 0;
}
