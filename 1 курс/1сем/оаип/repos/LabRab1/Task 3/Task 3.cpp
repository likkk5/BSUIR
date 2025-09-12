#include <iostream>
#include <iomanip>

int main() {
    long double a, t, v0, s;
    std::cin >> a;
    std::cin >> t;
    std::cin >> v0;
    s = v0 * t + (a * t * t) / 2;
    std::cout << std::setprecision(20);
    std::cout << s;
    return 0;
}