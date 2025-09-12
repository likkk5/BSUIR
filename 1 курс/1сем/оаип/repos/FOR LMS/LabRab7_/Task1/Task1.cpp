#include <iostream>
#include <string>

std::string symbols = "01"; //Алфавит для двоичной системы счисления

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
            if (((string[i] == '0' || string[i] == '1') && (i !=1)) || (string[1] == ','))
            {
                hasIncorrectSymbols = true;
            }
            else 
            {
                hasIncorrectSymbols = false;
                break;
            }
        }
        if ((!hasIncorrectSymbols) || (string.length() < 3))
        {
            std::cout << "Повторите ввод. Некорректный формат или символы." << "\n";
            std::cin.clear();
        }
        else
        {
            string.erase(1,1); // удаляем ',' и дополняем нулями сзади до нужной разрядности
            if (string.length() <= max_len)
            {
                char temp = string[0];
                string.erase(0, 1);
                for (int i = 0; max_len - string.length() - 1;i++)
                {
                    string = '0' + string;
                }
                string = temp + string;
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

// конвертация из дополнительного кода в прямой код O(n)
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

    int MaxLen = 16; // разрядность
    std::cout << "Введите числа в дополнительном коде в формате X,XXX..., где Х = {0,1} - не более " << MaxLen << " символов, первый символ до запятой является знаковым." << "\n" << "\n";

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