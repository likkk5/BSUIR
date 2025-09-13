#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <array>
#include <stdexcept>
#include <clocale>

void unsafeFunction(const char* input) {
    char buffer[10]; 

    try {
        if (std::strlen(input) >= sizeof(buffer)) {
            throw std::overflow_error(std::string("Ошибка: переполнение буфера! Входные данные: ") + input);
        }

        std::strcpy(buffer, input);

        std::cout << "Небезопасный буфер: " << buffer << std::endl;
    }
    catch (const std::overflow_error& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }
}

void safeFunction(const char* input) {
    std::array<char, 10> buffer{};  // Безопасный буфер с нулевой инициализацией

    // Используем безопасную версию копирования строки с ограничением размера
    std::snprintf(buffer.data(), buffer.size(), "%s", input);

    std::cout << "Безопасный буфер: " << buffer.data() << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::string userInput;
    int choice;

    while (true) {
        std::cout << "\nВыберите режим работы:\n";
        std::cout << "1 - Безопасная функция\n";
        std::cout << "2 - Небезопасная функция\n";
        std::cout << "Введите 'exit' для выхода\n";
        std::cout << "Ваш выбор: ";

        std::string inputChoice;
        std::cin >> inputChoice;
        std::cin.ignore();

        if (inputChoice == "exit") {
            std::cout << "Выход из программы...\n";
            break;
        }

        try {
            choice = std::stoi(inputChoice); 
        }
        catch (...) {
            std::cout << "Ошибка: Введите число 1 или 2, либо 'exit' для выхода.\n";
            continue;
        }

        std::cout << "Введите строку для обработки: ";
        std::getline(std::cin, userInput);

        std::cout << "\n--------------------------------------\n";
        if (choice == 1) {
            safeFunction(userInput.c_str());
        }
        else if (choice == 2) {
            unsafeFunction(userInput.c_str());
        }
        else {
            std::cout << "Ошибка: Неверный режим! Введите 1, 2 или 'exit'.\n";
        }
    }

    return 0;
}
