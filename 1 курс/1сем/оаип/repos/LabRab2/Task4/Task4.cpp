#include <iostream>

int main()
{   
    double x, y;
    std::cin >> x >> y;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Incorrect input";
        return 0;
    }
    bool a = x > y;
    std::cout << (a ? x : y) << "\n"; // с использованием переменной логического типа
    
    std::cout << (x > y ? x : y) << "\n"; // без использования
    
    return 0;
}