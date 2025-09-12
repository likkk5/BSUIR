#include <iostream>
#include <Windows.h>

// Ввод строки (не более max символов)
char* InputString(char* input_str, int max)
{
    int c, i = 0, len = 0;
    while (true)
    {
        std::cout << "Введите строку (не более " << max << " символов): ";
        do
        {
            c = getchar();
            *(input_str + i) = c;
            i++;
        } while (c != '\n');
        len = i;

        if (len > max)
        {
            std::cout << "Повторите ввод. Вы ввели строку больше " << max << " символов. Количество символов в строке: " << i << "\n" << "\n";
            for (i = 0;i < len;i++)
            {
                *(input_str + i) = '\0';
            }
            i = 0;
        }
        else
        {
            return input_str;
            break;
        }
    }
}

// Вывод строки, длины строки
int OutputString(char* input_str)
{
    int i = 0;
    std::cout << "\n" << "Вы ввели строку: ";
    while (*(input_str + i) != '\n')
    {
        std::cout << * (input_str + i);
        i = i + 1;
    }
    std::cout << "\n";

    //std::cout << "Длина строки: " << i << "\n" << "\n";

    return i;
}

// Поиск различныx символов в строке
void SearchDifferentSymbol(char* input_str, int len)
{
    int p = 0, q = 0;

    std::cout << "Строка состоит из следующих символов: ";
    
    for (int j = -128;j <= 127; j++)
    {
        q = 0;
        for (int i = 0;i < len;i++)
        {
            if (*(input_str + i) == j)
            {
                q = q + 1;
            }
        }
        
        if (q != 0)
        {
            p = p + 1;
        }
               
        if ((q != 0) && (p==1))
        {
                std::cout << "'" << char(j) << "'";
        }
        
        if ((q != 0) && (p != 1))
        {
                std::cout << ", '" << char(j) << "'";
        }
    }
    std::cout << "." << "\n";
}

int main()
{
    //setlocale(LC_ALL, "rus");
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Задание 3. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Ввести строку и определить все входящие в нее символы." << "\n";
    std::cout << "Результат вывести на экран." << "\n" << "\n";

    int Max_Len = 256, max_str = 255, len_str;

    int repeat = 1;
    std::string temp_input1;

    do
    {
        // Выделение динамической памяти для массива символов char
        char* str = nullptr;
        str = new char[Max_Len];

        // Ввод строки (не более max_str символов)
        str = InputString(str, max_str);

        // Вывод строки, длины строки
        len_str = OutputString(str);

        // Поиск различныx символов в строке
        SearchDifferentSymbol(str, len_str);

        // Освобождение динамической памяти
        delete[] str;
        str = nullptr;

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
