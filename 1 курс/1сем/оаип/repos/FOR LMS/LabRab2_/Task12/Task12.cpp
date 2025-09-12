#include <iostream>
int main()
{
    long double a, b, c, x, y;
    std::cin >> a >> b >> c >> x >> y;
    if ((a > 0) && (b > 0) && (c > 0) && (x > 0) && (y > 0))
    {
        if ((c <= x) && (b <= y) || (c <= x) && (a <= y) || (b <= x) && (a <= y) || (c <= y) && (b <= x) || (c <= y) && (a <= x) || (b <= y) && (a <= x))
        {
            std::cout << "YES";
        }
        else
        {
            std::cout << "NO";
        }
    }
    else
    {
        std::cout << "Incorrect input";
    }
    return 0;
}
