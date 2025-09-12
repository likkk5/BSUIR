#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    double h, t;
    const double g = 9.8;
    std::cin >> h;
    t = sqrt(2 * h / g);
    std::cout << std::setprecision(9);
    std::cout << t;
    return 0;
}