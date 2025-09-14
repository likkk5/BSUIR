#include "ALU.h"

int main() {
    setlocale(LC_ALL, "Russian");
    float a, b;
    cout << "Введите 2 числа: ";
    cin >> a >> b;
    cout << endl;
    try {
        ALU::addition(a, b);
        ALU::subtraction(a, b);
        ALU::multiplication(a, b);
        ALU::division(a, b);
    } catch (const string &ex) {
        cout << "Ошибка: " << ex << endl;
    }
    return 0;
}

