#include <iostream>

int main(){
    int a, b;
    std::cin >> a;
    std::cin >> b;
    a = a ^ b; //исключающее или (поразрядная)
    std::cout << "1: a=" << a << " b=" << b << "\n";
    b = a ^ b;
    std::cout << "2: a=" << a << " b=" << b << "\n";
    a = a ^ b;
    std::cout << "3: a=" << a << " b=" << b << "\n";
    return 0;
}