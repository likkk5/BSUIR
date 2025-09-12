#include <iostream>
#include <string>

int inputNumber()
{
   
    while (true)
    {
        std::cout << "Введите число" << std::endl;
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

                if ((check_string.length() != temp_input.length()) || (number < 1))
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
            std::cout << "Повторите ввод. Некорректное значение." << "\n";
            std::cin.clear();
        }
    }
    std::cout << "\n";
}


bool mod3(int a) {
    while (a > 5) {
        int s = 0;
        while (a != 0) {
            s += (a & 3);
            a = a >> 2;
        }
        a = s;
    }

    if (a == 0 || a == 3) {
        return true;
    }

    return false;
}

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

bool isDivideZero(int x, int y)
{
    while (x >= y) {
        int z = y;
        while (z != 0)
        {
            int borrow = (~x) & z;
            x = x ^ z;
            z = borrow << 1;
        }
    }

    return x == 0;
}

int main(void) {
    setlocale(LC_ALL, "RUS");
    int n = inputNumber();
    std::cout << (mod3(n) ? "Делится на 3" : "Не делится на 3") << std::endl;
    std::cout << (isDivideZero(n, 23) ? "Делится на 23" : "Не делится на 23") << std::endl;
    std::cout << (isDivideZero(n, 107) ? "Делится на 107" : "Не делится на 107") << std::endl;

    std::cout << n;
}