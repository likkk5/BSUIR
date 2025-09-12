#include <iostream>
#include <string>

// Ввод целого числа и проверка на корректность ввода (целое число, не отрицательное, не вещественное, не содержит буквы, не превышает |2147483647|)
int inputNumber()
{
    while (true)
    {
        std::cout << "Введите число: ";
        std::string temp_input, check_string;

        int number;
        std::string tempInput, string;

        getline(std::cin, temp_input);

        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
        {
            // <=2147483647
            if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
            {
                number = std::stoi(temp_input);
                check_string = std::to_string(number);

                if (check_string.length() != temp_input.length())
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                }
                else
                {
                    return number;
                }
            }

            else
            {
                std::cout << "Повторите ввод. Некорректное значение." << "\n";
                std::cin.clear();
            }
        }
        else
        {
            if ((temp_input[0] == 45) && (temp_input[1] >= 48) && (temp_input[1] <= 57))
            {
                // >= - 2147483648
                if ((temp_input.length() < 11) || ((temp_input.length() == 11) && ((temp_input[1] < 50) || ((temp_input[1] == 50) && (temp_input[2] <= 49) && (temp_input[3] <= 52) && (temp_input[4] <= 55) && (temp_input[5] <= 52) && (temp_input[6] <= 56) && (temp_input[7] <= 51) && (temp_input[8] <= 54) && (temp_input[9] <= 52) && (temp_input[10] <= 56)))))
                {
                    number = std::stoi(temp_input);
                    //std::cout << number << "\n";
                    check_string = std::to_string(number);

                    if (check_string.length() != temp_input.length())
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                    }
                    else
                    {
                        return number;
                        break;
                    }
                }
                else
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                }
            }
            else
            {
                std::cout << "Повторите ввод. Некорректное значение." << "\n";
                std::cin.clear();
            }
        }
    }
    std::cout << "\n";
}

// O(n)
int subtract(int x, int y)
{
    while (y != 0)
    {
        int borrow = (~x) & y;
        x = x ^ y;
        y = borrow << 1;
    }
    return x;
}

// O(n^2)
bool isDivideZero(int x, int y)
{
    std::cout << "x=" << x << " y=" << y << "\n";
    while (x >= y)
    {
        int z = y;
        x = subtract(x, z);
        /*
        // x - z // x = subtract(x, z);
        while (z != 0)
        {
            int borrow = (~x) & z;
            //std::cout << "borrow=" << borrow << "\n";
            x = x ^ z;
            //std::cout << "x=" << x << "\n";
            z = borrow << 1; //(*2)
            //std::cout << "z=" << z << "\n" << "\n";
        }
        //std::cout << "\n";*/
    }
   
    if (x == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    std::cout << "Задание 6. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Необходимо разработать программу, которая проверяет, делится ли введенное пользователем число на заданное простое." << "\n";
    std::cout << "Программа не должна содержать операции умножения, деления, вычитания (в том числе взятие остатка от деления)." << "\n";
    std::cout << "Вариант 13. Простые числа: 3, 23, 107." << "\n" << "\n";
    // 3 = 11
    // 23 = 10111
    // 107 = 1101011

    int repeat = 1;
    std::string temp_input1;

    do
    {
        int n = inputNumber();
        if (n < 0)
        {
            n = subtract(0, n);
        }
        
        std::cout << (isDivideZero(n, 3) ? "Делится на 3" : "Не делится на 3") << "\n";
        std::cout << (isDivideZero(n, 23) ? "Делится на 23" : "Не делится на 23") << "\n";
        std::cout << (isDivideZero(n, 107) ? "Делится на 107" : "Не делится на 107") << "\n";
       
        // Повторный запуск программы
        std::cout << '\n' << "Для повторного ввода данных введите 1 и нажать ENTER; для окончания работы - любой другой символ и нажать ENTER: ";
        std::cin >> temp_input1;
        if ((temp_input1[0] == '1') && (temp_input1.length() == 1))
        {
            repeat = 1;
            while (std::cin.get() != '\n');
        }
        else
        {
            std::cout << "Программа завершила работу." << "\n";
            repeat = 0;
        }
    } while (repeat == 1);

    return 0;
}
