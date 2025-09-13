#include <iostream>
#include <fstream>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");
    int answ;
    do {
        std::cout << "Введите строку: ";

        // Считываем строку с клавиатуры
        std::string inputString;
        std::getline(std::cin, inputString);

        // Выводим индексы и символы на консоль
        std::cout << "Индексы символов в строке:" << std::endl;

        for (int i = 0; i < inputString.length(); ++i) {
            std::cout << "Индекс " << i << ": " << inputString[i] << std::endl;
        }

        // Выводим общее количество символов на консоль
        std::cout << "Общее количество символов: " << inputString.length() << std::endl;

        // Сохраняем результаты в файл
        std::ofstream outputFile("outputx.txt", std::ios::app);  // Открываем файл для записи (app - дописывать в конец файла)
        if (outputFile.is_open()) {
            outputFile << "Введенная строка: " << inputString << std::endl;
            outputFile << "Индексы символов в строке:" << std::endl;
            for (int i = 0; i < inputString.length(); ++i) {
                outputFile << "Индекс " << i << ": " << inputString[i] << std::endl;
            }
            outputFile << "Общее количество символов: " << inputString.length() << std::endl;
            outputFile << "----------------------------------" << std::endl;
            outputFile.close();  // Закрываем файл
        }
        else {
            std::cerr << "Невозможно открыть файл для записи!" << std::endl;
        }

        std::cout << "If you want to continue, press 1: ";
        std::cin >> answ;
        std::cin.ignore();

    } while (answ == 1);

    return 0;
}

