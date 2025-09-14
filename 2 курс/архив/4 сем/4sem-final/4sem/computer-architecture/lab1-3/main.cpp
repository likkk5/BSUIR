#include <iostream>
#include "ALU.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int a, b;
    cout << "Введите числа a и b: " << endl;
    cin >> a >> b;
    cout << endl;
    try {
        ALU::add(a, b);
        ALU::sub(a, b);
        ALU::multiply(a, b);
        ALU::divide(a, b);
    } catch (string &ex) {
        cout << "Ошибка: " << ex << endl << endl;
    }

    return 0;
}