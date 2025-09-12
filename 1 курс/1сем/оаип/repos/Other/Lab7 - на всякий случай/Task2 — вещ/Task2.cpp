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
        int k = 0, l=0;

        for (int i = 0; i < string.length(); i++)
        {
            if ((string[i] == '0') || (string[i] == '1') || (string[0] != '.') || ((string[0] == '-') && (string.length() > 1)))
            {
                if (string[i] == '.')
                {
                    k = k + 1;
                }
                if (string[i] == '-')
                {
                    l = l + 1;
                }
                hasIncorrectSymbols = true;
            }
            else
            {
                hasIncorrectSymbols = false;
                break;
            }
        }
        if ((!hasIncorrectSymbols) || (k > 1) || (l > 1) || ((l == 1) && (string.length() == 1)))
        {
            std::cout << "Повторите ввод. Некорректные символы." << "\n";
            std::cin.clear();
        }
        else
        {
            return string;
            break;
        }
    }

    std::cout << "\n";
}

// обратный код
std::string revertNumber(std::string number)
{
    for (int i = 0; i < number.length(); i++)
    {
        //number[i] = number[i] == '0' ? '1' : '0';
        if (number[i] == '0')
        {
            number[i] = '1';
        }
        else
        {
            number[i] = '0';
        }
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

// порядок двоичного числа в нормализованном виде 1.xxx * 2^exponenta
int FindExponent(std::string number)
{
    int pos = number.find('.', 1);
       
    if (pos == std::string::npos) // введенное число без дробной части
    {
        return number.length() - 1;
    }
    else
    {
        return pos;
    }
}



// перевод двоичного числа в естественной форме в дополнительнвй код (max_len-разрядный)
std::string ConvertFromNaturalCodeToAdditional(std::string number, int max_len)
{
    std::string temp_str;
    int pos;
    int ii = 0, jj = 0;

    if (number[0] == '-')
    {
        temp_str += '1';
        jj = jj + 1;
    }
    else
    {
        temp_str += '0';
    }
    ii = ii + 1;

    pos = number.find('.',1);
    std::cout << "pos = " << pos << "\n";
    std::cout << "temp_str = " << temp_str << "\n";
    std::cout << "ii = " << ii << "\n";
    std::cout << "jj = " << jj << "\n";
    std::cout << "number.length() = " << number.length() << "\n";

    if (pos == std::string::npos) // введенное число без дробной части
    {
        if (number.length() >= max_len) // что делать, если ввели больше чем разрядность? при вводе проверить, если ввели без точки?
        {
            while (ii < max_len)
            {
                temp_str = temp_str + number[jj];
                ii++;
                jj++;
            }
        }
        else 
        {
            while (ii <= number.length())
            {
                temp_str += number[jj];
                ii++;
                jj++;

                std::cout << "temp_str = " << temp_str << "\n";
                std::cout << "ii = " << ii << "\n";
                std::cout << "jj = " << jj << "\n";
            }
                   
            // дополняем нулями в конце
            while (ii < max_len)
            {
                temp_str += '0';
                ii++;
            }
            std::cout << "temp_str = " << temp_str << "\n";
        }
    }
    else // введенное число с дробной частью
    {
        while (jj < pos)
        {
            temp_str = temp_str + number[jj];
            ii++;
            jj++;
        }

        jj++; // точку не записываем

        if (number.length() > max_len) // если после запятой много знаков, то отбрасываем. Вопрос тот же, если до запятой много знаков???? 
        {
            while (ii < max_len)
            {
                temp_str = temp_str + number[jj];
                ii++;
                jj++;
            }
        }
        else
        {
            while (ii < number.length())
            {
                temp_str = temp_str + number[jj];
                ii++;
                jj++;
            }

            // дополняем нулями в конце
            while (ii < max_len)
            {
                temp_str += '0';
                ii++;
            }
            std::cout << "temp_str = " << temp_str << "\n";
        }

    }

    std::cout << "\n" << "Двоичное число в нормальной форме (" << max_len << "-разрядн.): " << temp_str << "\n";
    
    // если число положительное, то дополнительный код = прямому
    // если число отрицательное, то делаем преобразование - обратный код +1
    if (temp_str[0] == '1')
    {
        temp_str = revertNumber(temp_str);
        temp_str = sum(temp_str, "1", 2);
    }
    return temp_str;
}

std::string addSignAttibute(std::string number, std::string sign) {

    if (sign[0] == '1') {
        number = '-' + number;
    }

    return number;
}

std::string ConvertFromAddCodeToNatural(std::string number) {
    number = subtraction(number, "1", 2);
    number = revertNumber(number);

    return number;
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 2. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Осуществить сложение чисел. Разработать функции для операции сложения. Предусмотреть ввод положительных и отрицательных чисел." << "\n";
    std::cout << "Вариант 13. Найти сумму двоичных чисел, заданных в естественной форме. Сложение выполните в дополнительном коде. Ответ выразите в естественной форме." << "\n" << "\n";

    int MaxLen = 32; // 32-битный формат IEEE754 (1 бит - знак, 2 - 9 бит - экспонента, 10 - 32 бит - мантисса)
    int numberBase = 2; // двоичная система счисления

    std::string firstNumber, secondNumber, result;
    int exponent1, exponent2;

    int repeat = 1;
    std::string temp_input1;

    do
    {
        firstNumber = inputNumber("Введите первое двоичное число в естественной форме: ", MaxLen);
        secondNumber = inputNumber("Введите второе двоичное число в естественной форме: ", MaxLen);
       
        //exponent1 = FindExponent(firstNumber);
        //exponent2 = FindExponent(secondNumber);

        firstNumber = ConvertFromNaturalCodeToAdditional(firstNumber, MaxLen);
        secondNumber = ConvertFromNaturalCodeToAdditional(secondNumber, MaxLen);

        std::cout << "\n" << "Первое двоичное число в дополнительном коде (" << MaxLen << "-разрядный): " << firstNumber << "\n";
        std::cout << "\n" << "Второе двоичное число в дополнительном коде (" << MaxLen << "-разрядный): " << secondNumber << "\n";

        result = sum(firstNumber, secondNumber, numberBase);
        std::cout << "Результат сложения в дополнительном коде: " << MaxLen << "-разрядный): " << result << "\n";
        std::cout << "Результат сложения в естественном коде: " << ConvertFromAddCodeToNatural(result) << "\n";

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