#include <iostream>
#include <string>

std::string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Алфавит для систем счисления до 36

//Объявляем функции, чтобы могли ссылаться друг на друга
std::string sum(std::string firstNumber, std::string secondNumber, int numberBase);
std::string subtraction(std::string firstNumber, std::string secondNumber, int numberBase);

// Ввод основания системы счисления
int inputNumberBase()
{
    while (true)
    {
        int numberBase;
        std::string temp_input, check_string;

        std::cout << "Введите основание системы счисления: ";

        getline(std::cin, temp_input);

        if ((temp_input[0] >= 48) && (temp_input[0] <= 57) && temp_input.length() <= 2)
        {
            numberBase = std::stoi(temp_input);
            check_string = std::to_string(numberBase);

            if ((check_string.length() != temp_input.length()) || numberBase < 2 || numberBase > 36)
            {
                std::cout << "Повторите ввод. Некорректное значение." << "\n";
                std::cin.clear();
            }
            else
            {
                return numberBase;
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

// Ввод чисел
std::string inputNumber(std::string text, int baseNumber)
{
    while (true)
    {
        std::string input;
        bool hasIncorrectSymbols = false;
        
        std::cout << text;
        getline(std::cin, input);
        int leng = input.length();

        // строчные буквы a-z преобразовываем в заглавные
        for (int i = 0; i < leng; i++)
        {
            if (97 <= input[i] && input[i] <= 122) // a-z 
            {
                input[i] -= 32;
            }
        }

        for (int i = 0; i < input.length(); i++)
        {
            if (i == 0 && input[i] == '-')
            {
                if (input.length() == 1)
                {
                    std::cout << std::endl << "Введен только символ указываюший, что строка отрицательная. Введите число." << input[i] << "\n";
                }
                continue;
            }

            std::size_t found = symbols.find(input[i]);
            if (found == -1)
            {
                std::cout << "Повторите ввод. Найден некорректный символ: " << input[i] << "\n";
                hasIncorrectSymbols = true;
                std::cin.clear();
                break;
            }

            if (found >= baseNumber) {
                std::cout << "Повторите ввод. Найден некорректный символ для системы счисления с основанием " << baseNumber << ": " << input[i] << "\n";
                hasIncorrectSymbols = true;
                std::cin.clear();
                break;
            }
        }
        
        if (!hasIncorrectSymbols)
        {
            return input;
        }
    }
}


// Ввод операции
std::string inputOperation()
{
    while (true)
    {
        std::string input;
        std::cout << "Введите операцию. Возможные варианты только '+' или '-': ";
        getline(std::cin, input);

        if (input.length() == 1 && (input[0] == '-' || input[0] == '+'))
        {
            return input;
        }
        else
        {
            std::cout << "Повторите ввод. Некорректное значение." << "\n";
        }
    }
}

// Сложение O(n)
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

// Вычитание O(n)
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
        int sub = 0;

        for (i = 0; i < tempFirst.length(); i++)
        {
            std::size_t foundFirst = symbols.find(tempFirst[i]);

            if (i < tempSecond.length())
            {
                std::size_t foundSecond = symbols.find(tempSecond[i]);
                sub = foundFirst - foundSecond - minus;
            }
            else
            {
                sub = foundFirst - minus;
            }

            if (sub >= 0)
            {
                minus = 0;
                result += symbols[sub];
            }
            else
            {
                sub = sub + numberBase;
                result += symbols[sub];
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

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 3. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Пользователь вводит основание системы счисления. Осуществить сложение и вычитание чисел в заданной системе счисления." << "\n";
    std::cout << "В другую систему счисления не переводить. В системах счисления больших десятичной использовать буквы по аналогии с шестнадцатеричной системой." << "\n";
    std::cout << "Разработать функции для выполнения операции сложения и функции для выполнения операции вычитания. Предусмотреть ввод положительных и отрицательных чисел." << "\n" << "\n";

    int numberBase;
    std::string firstNumber, secondNumber, operation, result;

    int repeat = 1;
    std::string temp_input1;

    do
    {
        numberBase = inputNumberBase();
        firstNumber = inputNumber("Введите первое число: ", numberBase);
        secondNumber = inputNumber("Введите второе число: ", numberBase);
        operation = inputOperation();

        std::cout << "\n" << "Основание системы счисления: " << numberBase << "\n";
        std::cout << "Первое число: " << firstNumber << "\n";
        std::cout << "Второе число: " << secondNumber << "\n";

        if (operation[0] == '-')
        {
            result = subtraction(firstNumber, secondNumber, numberBase);
            std::cout << "Результат вычитания: " << result.c_str() << "\n";
        }
        else
        {
            result = sum(firstNumber, secondNumber, numberBase);
            std::cout << "Результат сложения: " << result.c_str() << "\n";
        }

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