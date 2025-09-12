#include <iostream>
#include <string>

int getnumber(int begin, int end, std::string text)
{
    int number;
    while (true)
    {
        std::cout << text;
        std::cin >> number;
        if (std::cin.fail() || number < begin || number > end)
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "  Input Error. Please repeat " << "\n";
        }
        else
        {
            return number;
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int t, i, j;
    
    t = getnumber(1, 1000, "Введите количество тестов: ");

    for (j = 0; j < t; j++)
    {
        i = getnumber(1, 1000000000, "Введите число: ");
        std::cout << "Количество интересных чисел до " << i << ": " <<i / 9 << "\n" << "\n";
    }

    return 0;
}

