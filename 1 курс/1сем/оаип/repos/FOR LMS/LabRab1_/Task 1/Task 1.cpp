#include <iostream>

int main() {
    long double x, a, b, c, d, f1, f2;
    std::cout << "Input x=";
    std::cin >> x;
    a = x * x;
    b = 69 * a + 8;
    c = 23 * a + 32;
    d = x * c;
    f1 = b + d;
    f2 = b - d;
    std::cout << "f1=" << f1 << "\n";
    std::cout << "f1=" << f2;
    return 0;
}
