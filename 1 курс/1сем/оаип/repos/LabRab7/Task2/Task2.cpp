#include <iostream>
#include <string>

std::string symbols = "01"; //Алфавит для двоичной системы счисления

//Объявляем функции, чтобы могли ссылаться друг на друга
std::string sum(std::string firstNumber, std::string secondNumber, int numberBase);
std::string subtraction(std::string firstNumber, std::string secondNumber, int numberBase);

// Ввод двоичного числа в естественной форме (целое)
std::string inputNumber(std::string input, int max_len)
{
    std::string tempInput, string;
 
    while (true)
    {
        std::cout << input;
        getline(std::cin, string);

        bool hasIncorrectSymbols = false;
        int l=0;

        for (int i = 0; i < string.length(); i++)
        {
            if ((string[i] == '0') || (string[i] == '1') || ((string[0] == '-') && (string.length() > 1)))
            {
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
        if ((!hasIncorrectSymbols) || (l > 1) || ((l == 1) && (string.length() == 1) && (string.length() > max_len + 2)) || ((l==0) && (string.length() > max_len)))
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

// инверсия O(n)
std::string revertNumber(std::string number)
{
    for (int i = 0; i < number.length(); i++)
    {
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

// Сложение O(n)
std::string sum(std::string firstNumber, std::string secondNumber, int numberBase)
{
    std::string tempFirst, tempSecond, result;
    int add = 0, i = 0;
    int sum = 0;
 
    // переворачиваем строки
    std::reverse(firstNumber.begin(), firstNumber.end());
    std::reverse(secondNumber.begin(), secondNumber.end());
  
    tempFirst = firstNumber;
    tempSecond = secondNumber;

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
    int minus = 0, i = 0;

    if (firstNumber == secondNumber) //если два числа одинаковые, то сразу 0
    {
        result = '0';
    }
    else
    {
        tempFirst = firstNumber;
        tempSecond = secondNumber;

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
        std::reverse(result.begin(), result.end());
    }

    return result;
}

// перевод двоичного числа в естественной форме в двоичное число в дополнительном коде (max_len-разрядный) O(n)
std::string ConvertFromNaturalCodeToAdditional(std::string number, int max_len)
{
    std::string temp_str;
    int ii = 0, jj = 0;
  
    // формируем знаковый бит: 1 - отрицательное, 0 - положительное 
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
    
    // дополняем нулями после знакового бита
    while (ii < max_len + 1 - number.length() + jj)
    {
        temp_str += '0';
        ii++;
    }

    while (ii < max_len + 1)
    {
        temp_str += number[jj];
        ii++;
        jj++;
    }
   
    std::cout << "Двоичное число в прямом коде (" << max_len << "-разрядный): " << temp_str << "\n";
    
    // если число положительное, то дополнительный код = прямому
    // если число отрицательное, то делаем преобразование: обратный код + 1
    if (temp_str[0] == '1')
    {
        temp_str = revertNumber(temp_str);
        temp_str = sum(temp_str, "1", 2);
        temp_str[0] = '1';
    }
    return temp_str;
}

// перевод двоичного числа в дополнительном коде в двоичное число в естественной форме O(n)
std::string ConvertFromAddCodeToNatural(std::string number)
{
    if (number == "100000000000000000")
    {
        number = "0";
    }
    else {
        int ii = 0;
        int len = number.length();

        // если число положительное, то дополнительный код = прямому
         // если число отрицательное, то делаем преобразование: -1, обратный код
        if (number[0] == '1')
        {
            number = subtraction(number, "1", 2);
            number = revertNumber(number);
            number[0] = '-';
        }

        //чистим все ведущие нули
        if (number[0] == '-')
        {
            ii++;
        }

        for (int jj = ii; jj < len; jj++)
        {
            if (number[ii] != '0')
            {
                break;
            }
            else
            {
                number.erase(ii, 1);
            }
        }
    }
    return number;
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 2. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Осуществить сложение чисел. Разработать функции для операции сложения. Предусмотреть ввод положительных и отрицательных чисел." << "\n";
    std::cout << "Вариант 13. Найти сумму двоичных чисел, заданных в естественной форме. Сложение выполните в дополнительном коде. Ответ выразите в естественной форме." << "\n" << "\n";

    int MaxLen = 16; // разрядность
    int numberBase = 2; // двоичная система счисления

    std::string firstNumber, secondNumber, result;
    
    int repeat = 1;
    std::string temp_input1;

    do
    {
        firstNumber = inputNumber("Введите первое двоичное число в естественной форме: ", MaxLen);
        secondNumber = inputNumber("Введите второе двоичное число в естественной форме: ", MaxLen);
       
        std::cout << "\n";
        firstNumber = ConvertFromNaturalCodeToAdditional(firstNumber, MaxLen);
        secondNumber = ConvertFromNaturalCodeToAdditional(secondNumber, MaxLen);

        std::cout << "\n" << "Первое двоичное число в дополнительном коде (" << MaxLen << "-разрядный): " << firstNumber << "\n";
        std::cout << "Второе двоичное число в дополнительном коде (" << MaxLen << "-разрядный): " << secondNumber << "\n" << "\n";

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