#include <iostream>
#include <iomanip>

int main() {
    double b1, s;
    const double q = 1.0 / 1001.0;
    std::cin >> b1;
    s = b1 / (1 - q);
    std::cout << std::setprecision(8);
    std::cout << s;
    return 0;
}