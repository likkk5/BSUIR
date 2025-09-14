#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include "Register.h"


void handleInput();


int main() {

    Register a(-32768);
    Register b(-1);

    Register res;
    res = a / b;

//    handleInput();

    return 0;
}


void handleInput(){
    std::cout << "---Эмулятор АЛУ---\n";
    std::cout << "Выполнение заданной операции\n";
    std::cout << "Вводите исходные данные:\n";

    Register a;
    Register b;
    Register result;

    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;

    std::cout << "Операция ( + | - | * | / ) : ";
    char sign;
    std::cin >> sign;

    std::cout << "Выполнеие: " << (int)a << " " << sign << " " << (int)b << '\n';
    if (sign == '+')
        result = a + b;
    else if (sign == '-')
        result = a - b;
    else if (sign == '*')
        result = a * b;
    else if (sign == '/')
        result = a / b;

    std::cout << "\nРезультат: " << (int)a << " " << sign << " " << (int)b
        << " = " << int(result) <<'\n';

}
