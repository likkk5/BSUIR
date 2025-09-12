#include <iostream>

int main()
{
    long double a, b, c, y;
    int n;
    std::cin >> a >> b >> c >> n;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Incorrect input";
        return 0;
    }

    switch (n)
    {
    case 2:
        y = b * c - a * a;
        std::cout << y << "\n";
        break;
    case 56:
        y = b * c;
        std::cout << y << "\n";
        break;
    case 7:
        y = a * a + c;
        std::cout << y << "\n";
        break;
    case 3:
        y = a - b * c;
        std::cout << y << "\n";
        break;

    default:
        y = (a + b) * (a + b) * (a + b);
        std::cout << y << "\n";
    }
    return 0;
}