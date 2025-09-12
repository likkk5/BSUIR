#include <iostream>
#include <string>

std::string symbols = "01"; //Алфавит для двоичной системы счисления

//Объявляем функции, чтобы могли ссылаться друг на друга
std::string sum(std::string firstNumber, std::string secondNumber, int numberBase);
std::string subtraction(std::string firstNumber, std::string secondNumber, int numberBase);

// Ввод числа
std::string inputNumber(std::string input, int max_len)
{
    std::string tempInput, string;

    while (true)
    {
        std::cout << input;
        getline(std::cin, string);

        bool hasIncorrectSymbols = false;

        for (int i = 0; i < string.length(); i++)
        {
            if ((string[i] == '0' || string[i] == '1') || (string[i] == '.' && (i == 1)))
            {
                hasIncorrectSymbols = true;
            }
            else 
            {
                hasIncorrectSymbols = false;
                break;
            }
        }
        if (!hasIncorrectSymbols) 
        {
            std::cout << "Повторите ввод. Некорректные символы." << "\n";
            std::cin.clear();
        }
        else
        {
            if (((string.length() <= max_len + 1) && (string[1] == '.')) || ((string.length() <= max_len) && (string[1] != '.')))
            {
                if ((string.length() < max_len + 1) && (string[1] == '.'))
                {
                    for (int i = 0; max_len + 1 - string.length();i++)
                    {
                        string = string + '0';
                    }
                }
                if ((string.length() < max_len) && (string[1] != '.'))
                {
                    for (int i = 0; max_len - string.length();i++)
                    {
                        string = '0' + string;
                    }
                }

                return string;
                break;
            }
            else 
            {
                std::cout << "Повторите ввод. Превышена разрядность." << "\n";
                std::cin.clear();
            }
        }
    }

    std::cout << "\n";
}

std::string revertNumber(std::string number)
{
    for (int i = 0; i < number.length(); i++) {
        number[i] = number[i] == '0' ? '1' : '0';
    }

    return number;
}

// Сложение
std::string sum(std::string firstNumber, std::string secondNumber, int numberBase)
{
    std::string tempFirst, tempSecond, result;
    int add = 0, i = 0;
    int sum = 0;

    // если число отрицательное, то делаем его положительным (строка без нулевого символа), а вместо операции сложения будет операция вычитания
    if (secondNumber[0] == '-')
    {
        tempSecond = secondNumber.substr(1, secondNumber.length());
        return subtraction(firstNumber, tempSecond, numberBase);
    }
    if (firstNumber[0] == '-')
    {
        tempFirst = firstNumber.substr(1, firstNumber.length());
        return subtraction(secondNumber, tempFirst, numberBase);
    }

    // переворачиваем строки
    std::reverse(firstNumber.begin(), firstNumber.end());
    std::reverse(secondNumber.begin(), secondNumber.end());

    // определяем большее число
    if (firstNumber.length() >= secondNumber.length())
    {
        tempFirst = firstNumber;
        tempSecond = secondNumber;
    }
    else
    {
        tempFirst = secondNumber;
        tempSecond = firstNumber;
    }

    for (i = 0; i < tempFirst.length(); i++)
    {
        std::size_t foundFirst = symbols.find(tempFirst[i]);
        if (i < tempSecond.length())
        {
            std::size_t foundSecond = symbols.find(tempSecond[i]);
            sum = foundFirst + foundSecond + add;
        }
        else
        {
            sum = foundFirst + add;
        }

        if (sum >= numberBase)
        {
            add = 1;
            result += symbols[sum - numberBase];
        }
        else
        {
            result += symbols[sum];
            add = 0;
        }
    }

    if (add != 0)
    {
        i++;
        result += symbols[1];
    }

    std::reverse(result.begin(), result.end());

    return result;
}

// Вычитание
std::string subtraction(std::string firstNumber, std::string secondNumber, int numberBase)
{
    std::string tempFirst, tempSecond, result;
    bool addMinus = false;
    int minus = 0, i = 0;

    if (firstNumber == secondNumber) //если два числа одинаковые, то сразу 0
    {
        result = '0';
    }
    else
    {
        //вычитание отрицательного числа равно сложению с положительным
        if (firstNumber[0] == '-' && secondNumber[0] != '-')
        {
            tempFirst = firstNumber.substr(1, firstNumber.length());
            result = '-' + sum(tempFirst, secondNumber, numberBase);
            return result;
        }

        if (secondNumber[0] == '-')
        {
            tempSecond = secondNumber.substr(1, secondNumber.length());
            return sum(firstNumber, tempSecond, numberBase);
        }

        if (firstNumber.length() > secondNumber.length())
        {
            tempFirst = firstNumber;
            tempSecond = secondNumber;
        }
        else
        {
            if (firstNumber.length() == secondNumber.length())
            {
                for (i = 0; i < firstNumber.length(); i++)
                {
                    std::size_t foundFirst = symbols.find(firstNumber[i]);
                    std::size_t foundSecond = symbols.find(secondNumber[i]);

                    if (foundFirst > foundSecond)
                    {
                        tempFirst = firstNumber;
                        tempSecond = secondNumber;
                    }
                }

                if (tempFirst.length() == 0)
                {
                    tempFirst = secondNumber;
                    tempSecond = firstNumber;
                    addMinus = true;
                }
            }
            else
            {
                tempFirst = secondNumber;
                tempSecond = firstNumber;
                addMinus = true;
            }
        }

        if (tempFirst[0] == '-')
        {
            tempFirst = tempFirst.substr(1, tempFirst.length());
        }

        if (tempSecond[0] == '-')
        {
            tempSecond = tempSecond.substr(1, tempSecond.length());
        }

        std::reverse(tempFirst.begin(), tempFirst.end());
        std::reverse(tempSecond.begin(), tempSecond.end());
        int sum = 0;

        for (i = 0; i < tempFirst.length(); i++)
        {
            std::size_t foundFirst = symbols.find(tempFirst[i]);

            if (i < tempSecond.length())
            {
                std::size_t foundSecond = symbols.find(tempSecond[i]);
                sum = foundFirst - foundSecond - minus;
            }
            else
            {
                sum = foundFirst - minus;
            }

            if (sum >= 0)
            {
                minus = 0;
                result += symbols[sum];
            }
            else
            {
                sum = sum + numberBase;
                result += symbols[sum];
                minus = 1;
            }
        }

        //чистим все ведущие нули после вычитания
        if (tempSecond[0] == '-')
        {
            result = result.substr(0, i - 1);
        }

        std::reverse(result.begin(), result.end());

        if (addMinus || minus == 1)
        {
            result = '-' + result;
        }
    }

    return result;
}

std::string ConvertFromAddCodeToDirect(std::string number) 
{
    number = subtraction(number, "1", 2);
    number = revertNumber(number);
    number[0] = '1';
    return number;
}


int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 1. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Перевести числа. Предусмотреть ввод положительных и отрицательных чисел." << "\n";
    std::cout << "Вариант 13. Из дополнительного кода в прямой код." << "\n" << "\n";

    int MaxLen = 8; // разрядность
    std::cout << "Дополнительный код для целого числа - не более " << MaxLen << " символов {0,1};" << "\n";
    std::cout << "для вещественного числа - в формате x.xxxx..., где x = { 0,1 }, первый символ до точки является знаковым, количество знаков после запятой - не более " << MaxLen - 1 << "." << "\n" << "\n";

    std::string Number;
    int repeat = 1;
    std::string temp_input1;

    do
    {
        Number = inputNumber("Введите число в дополнительном коде: ", MaxLen);
        std::cout << "\n" << "Число в дополнительном коде (" << MaxLen << "-разрядный): " << Number << "\n";

        //если число отрицательное, то делаем преобразование
        if (Number[0] == '1')
        {
            Number = ConvertFromAddCodeToDirect(Number);
        }
        std::cout << "Число в прямом коде: " << Number << "\n";

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