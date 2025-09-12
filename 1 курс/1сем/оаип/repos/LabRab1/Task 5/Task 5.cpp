#include <iostream>
#include <iomanip>

int main() {
    long long a1, a100;
    long double d, s70;
    std::cin >> a1;
    std::cin >> a100;
    d = (a100-a1)/(100-1);
    s70 = (2 * a1 + d*(70 - 1)) * 70 / 2;
    std::cout << std::setprecision(10);
    std::cout << d <<"\n";
    std::cout << s70;
    return 0;
}