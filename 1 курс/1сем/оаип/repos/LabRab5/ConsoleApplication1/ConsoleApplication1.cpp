#include <iostream>
#include <string>


int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 4. Лишик Ксения. Группа 253505" << "\n";

    double ElementArray;
    std::string temp_input = "";

    getline(std::cin, temp_input);

    ElementArray = std::stod(temp_input);
    std::cout << ElementArray << "\n";
}
