#include <iostream>
#include <string>

// Ввод строки (не более max символов), английские буквы 
std::string InputString(int max, int number)
{
    std::string input_str;
    int kk = 0;
    while (true)
    {
        std::cout << "Введите строку (не более " << max << " символов) : ";
        getline(std::cin, input_str);
        if (input_str.length() > max)
        {
            std::cout << "Повторите ввод. Вы ввели строку больше " << max << " символов. Количество символов в строке: " << input_str.length() << "\n" << "\n";
            std::cin.clear();
        }
        else
        {
            for (int pp = 0; pp < input_str.length(); pp++)
            {
                if (input_str[pp] < 0)
                {
                    kk = kk + 1;
                }
            }
            if (kk != 0)
            {
                std::cout << "Повторите ввод. Вы ввели строку, которая содержит не только английские буквы." << "\n" << "\n";
                std::cin.clear();
                kk = 0;
            }
            else
            {
                return input_str;
                break;
            }
        }
    }
}

// Ввод текста
std::string* InputText(std::string* input_text, int count_string, int max)
{
    for (int pp = 0; pp < count_string; pp++)
    {
        *(input_text + pp) = InputString(max, pp);
    }
    return input_text;
}

// Вывод текста
void OutputText(std::string* input_text, int count_string, std::string output_string)
{
    std::cout << "\n" << output_string << "\n";
    for (int pp = 0; pp < count_string; pp++)
    {
        std::cout << *(input_text + pp) << "\n";
    }
}

std::string* ChangeSymbols(std::string* input_text, int count_string)
{
    std::string temp_string;
    std::string new_string;
    int len = 0, i = 0, pp, qq, last = 0;

    for (pp = 0; pp < count_string; pp++)
    {
        temp_string = *(input_text + pp);
        len = temp_string.length();
        new_string = "";
        i = 0;

        for (qq = 0; qq < len - 1; qq++)
        {
            new_string = new_string + temp_string[qq];
            last = 0;

            if (temp_string[qq] == 'c')
            {
                if ((temp_string[qq + 1] == 'e') || (temp_string[qq + 1] == 'i') || (temp_string[qq + 1] == 'y') || (temp_string[qq + 1] == 'E') || (temp_string[qq + 1] == 'I') || (temp_string[qq + 1] == 'Y'))
                {
                    new_string[i] = 's';
                }
                else
                {
                    new_string[i] = 'k';
                }
            }

            if (temp_string[qq] == 'C')
            {
                if ((temp_string[qq + 1] == 'e') || (temp_string[qq + 1] == 'i') || (temp_string[qq + 1] == 'y') || (temp_string[qq + 1] == 'E') || (temp_string[qq + 1] == 'I') || (temp_string[qq + 1] == 'Y'))
                {
                    new_string[i] = 'S';
                }
                else
                {
                    new_string[i] = 'K';
                }
            }

            if ((temp_string[qq] == 'q') && ((temp_string[qq + 1] == 'u') || (temp_string[qq + 1] == 'U')))
            {
                new_string[i] = 'k';
                new_string = new_string + 'v';
                qq = qq + 1;
                last = 1;
                i = i + 1;
            }

            if ((temp_string[qq] == 'Q') && ((temp_string[qq + 1] == 'u') || (temp_string[qq + 1] == 'U')))
            {
                new_string[i] = 'Q';
                new_string = new_string + 'v';
                qq = qq + 1;
                last = 1;
                i = i + 1;
            }

            if (temp_string[qq] == 'x')
            {
                new_string[i] = 'k';
                new_string = new_string + 's';
                i = i + 1;
            }

            if (temp_string[qq] == 'X')
            {
                new_string[i] = 'K';
                new_string = new_string + 's';
                i = i + 1;
            }

            if (temp_string[qq] == 'w')
            {
                new_string[i] = 'v';
            }

            if (temp_string[qq] == 'W')
            {
                new_string[i] = 'V';
            }

            if (temp_string[qq] == 'q')
            {
                new_string[i] = 'k';
            }

            if (temp_string[qq] == 'Q')
            {
                new_string[i] = 'K';
            }

            if ((temp_string[qq] == 'p') && ((temp_string[qq + 1] == 'h') || (temp_string[qq + 1] == 'H')))
            {
                new_string[i] = 'f';
                qq = qq + 1;
                last = 1;
            }

            if ((temp_string[qq] == 'P') && ((temp_string[qq + 1] == 'h') || (temp_string[qq + 1] == 'H')))
            {
                new_string[i] = 'F';
                qq = qq + 1;
                last = 1;
            }

            if ((temp_string[qq] == 'o') && ((temp_string[qq + 1] == 'o') || (temp_string[qq + 1] == 'O')))
            {
                new_string[i] = 'u';
                qq = qq + 1;
                last = 1;
            }

            if ((temp_string[qq] == 'O') && ((temp_string[qq + 1] == 'o') || (temp_string[qq + 1] == 'O')))
            {
                new_string[i] = 'U';
                qq = qq + 1;
                last = 1;
            }

            if ((temp_string[qq] == 'e') && ((temp_string[qq + 1] == 'e') || (temp_string[qq + 1] == 'E')))
            {
                new_string[i] = 'i';
                qq = qq + 1;
                last = 1;
            }

            if ((temp_string[qq] == 'E') && ((temp_string[qq + 1] == 'e') || (temp_string[qq + 1] == 'E')))
            {
                new_string[i] = 'I';
                qq = qq + 1;
                last = 1;
            }

            if ((temp_string[qq] == 't') && ((temp_string[qq + 1] == 'h') || (temp_string[qq + 1] == 'H')))
            {
                new_string[i] = 'z';
                qq = qq + 1;
                last = 1;
            }

            if ((temp_string[qq] == 'T') && ((temp_string[qq + 1] == 'h') || (temp_string[qq + 1] == 'H')))
            {
                new_string[i] = 'Z';
                qq = qq + 1;
                last = 1;
            }

            i = i + 1;
        }

        // для последнего символа строки

        if (last != 1)
        {
            new_string = new_string + temp_string[len - 1];
        }


        if (temp_string[len - 1] == 'c')
        {
            new_string[i] = 'k';
        }

        if (temp_string[len - 1] == 'C')
        {
            new_string[i] = 'K';
        }

        if (temp_string[len - 1] == 'x')
        {
            new_string[i] = 'k';
            new_string = new_string + 's';
        }
    
        if (temp_string[len - 1] == 'X')
        {
            new_string[i] = 'k';
            new_string = new_string + 's';
        }

        if (temp_string[len - 1] == 'w')
        {
            new_string[i] = 'v';
        }

        if (temp_string[len - 1] == 'W')
        {
            new_string[i] = 'V';
        }

        if (temp_string[len - 1] == 'q')
        {
            new_string[i] = 'k';
        }

        if (temp_string[len - 1] == 'Q')
        {
            new_string[i] = 'K';
        }
         
        *(input_text + pp) = new_string;
    }
    
    return input_text;
}

// замена you
std::string* ChangeYou(std::string* input_text, int count_string)
{
    std::string temp_string;
    std::string new_string;
    int len = 0, i = 0, pp, qq, last = 0;

    for (pp = 0; pp < count_string; pp++)
    {
        temp_string = *(input_text + pp);
        len = temp_string.length();
        new_string = "";
        i = 0;

        for (qq = 0; qq < len - 2; qq++)
        {
            new_string = new_string + temp_string[qq];
            last = 0;
            if ((temp_string[qq] == 'y') && ((temp_string[qq + 1] == 'o') || (temp_string[qq + 2] == 'u') || (temp_string[qq + 1] == 'O') || (temp_string[qq + 2] == 'U')))
            {
                new_string[i] = 'u';
                qq = qq + 2;
                last = 1;
            }

            if ((temp_string[qq] == 'Y') && ((temp_string[qq + 1] == 'o') || (temp_string[qq + 2] == 'u') || (temp_string[qq + 1] == 'O') || (temp_string[qq + 2] == 'U')))
            {
                new_string[i] = 'U';
                qq = qq + 2;
                last = 1;
            }

            i = i + 1;
        }

        if (last != 1)
        {
            new_string = new_string + temp_string[len - 2];
            new_string = new_string + temp_string[len - 1];
        }

        if (len < 3)
        {
            new_string = temp_string;
        }

        *(input_text + pp) = new_string;
    }

    return input_text;
}

// замена в тексте заглавной буквы в середине слова на строчную
std::string* DeleteBig(std::string* input_text, int count_string)
{
    std::string temp_string;
    std::string new_string;
    int len = 0, i = 0, pp, qq;

    for (pp = 0; pp < count_string; pp++)
    {
        temp_string = *(input_text + pp);
        len = temp_string.length();
        new_string = "";
        i = 0;

        for (qq = 0; qq < len - 1; qq++)
        {
            new_string = new_string + temp_string[qq];
            if ((temp_string[qq] >= 65) && (temp_string[qq] <= 90) && (qq != 0))
            {
                if (((temp_string[qq - 1] != ' ') && (temp_string[qq + 1] == ' '))|| ((temp_string[qq - 1] != ' ') && (temp_string[qq + 1] != ' ')))
                {
                    new_string[i] = temp_string[qq] + 32;
                }
            }
            i = i + 1;
        }

        // для последнего символа строки
       new_string = new_string + temp_string[len - 1];
       if ((temp_string[len - 1] >= 65) && (temp_string[len - 1] <= 90))
       {
           new_string[i] = temp_string[len - 1] + 32;
       }
       
        *(input_text + pp) = new_string;
    }

    return input_text;
}

// согласный - true; гласный - false
bool Сonsonants(char symbol)
{
    bool cons = false;

    // заглавные буквы
    if (((symbol >= 65) && (symbol <= 90)) && ((symbol != 65) && (symbol != 69) && (symbol != 73) && (symbol != 79) && (symbol != 85) && (symbol != 89)))
    {
        cons = true;
    }

    // строчные буквы
    if (((symbol >= 97) && (symbol <= 122)) && ((symbol != 97) && (symbol != 101) && (symbol != 105) && (symbol != 111) && (symbol != 117) && (symbol != 121)))
    {
        cons = true;
    }
    return cons;
}

// замена двойных согласных на один символ в строке
std::string DeleteDoubleСonsonantsString(std::string temp_string)
{
    std::string new_string;
    int len = 0, i = 0, qq = 0;
    len = temp_string.length();
    new_string = "";
    i = 0;

    for (qq = 0; qq < len - 1; qq++)
    {
        new_string = new_string + temp_string[qq];
        if (Сonsonants(temp_string[qq]))
        {
            if ((temp_string[qq] == temp_string[qq + 1]) || (temp_string[qq] == char(temp_string[qq + 1] + 32)) || (temp_string[qq] == char(temp_string[qq + 1] - 32)))
            {
                new_string[i] = temp_string[qq];
                qq = qq + 1;
            }
        }
        i = i + 1;
    }
    if (qq <= len - 1)
    {
        new_string = new_string + temp_string[len - 1];
    }
    if (len < 2)
    {
        new_string = temp_string;
    }

    return new_string;
}

// замена двойных согласных на один символ в тексте
std::string* DeleteDoubleСonsonantsText(std::string* input_text, int count_string)
{
    std::string final_string;
    int len = 0, new_len = 0, i = 0, pp;

    for (pp = 0; pp < count_string; pp++)
    {
        final_string = *(input_text + pp);
        do
        {
            len = final_string.length();
            final_string = DeleteDoubleСonsonantsString(final_string);
            new_len = final_string.length();
        } while (new_len != len);

        *(input_text + pp) = final_string;
    }
    return input_text;
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 4. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "В консоль вводится текст на английском языке, без переносов слов. Длина строк не превышает 100 символов." << "\n";
    std::cout << "Осуществить преобразования." << "\n" << "\n";

    int size_text = 1; // В тексте 1 строка
    int max_str = 100; // В строке не больше 100 символов
    int repeat = 1;
    std::string temp_input1;

    do
    {
        // Выделение динамической памяти для текста
        std::string* text = nullptr;
        text = new std::string[size_text * max_str];

        // Ввод текста
        text = InputText(text, size_text, max_str);

        // Вывод текста
        //OutputText(text, size_text, "Вы ввели следующий текст:");

        // Преобразование теста
        text = ChangeSymbols(text, size_text);
        text = ChangeYou(text, size_text);
        text = DeleteBig(text, size_text);
        text = DeleteDoubleСonsonantsText(text, size_text);

        // Вывод преобразованного текста
        OutputText(text, size_text, "Текст после преобразования:");
        
        // Освобождение динамической памяти
        delete[] text;
        text = nullptr;

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