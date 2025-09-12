#include <iostream> 
#include <iomanip>

int main()
{
    int h;
    double t;
    const double g = 9.8;
    std::cout << "Input height h=";
    std::cin >> h;
    t = sqrt(2 * h / g);
    std::cout << std::setprecision(9);
    std::cout << "Time of falling stone frome a height " << h << ": t = " << t;
    return 0;
}