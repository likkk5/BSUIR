#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 11. Игра Сапер. Игровое поле n*m " << '\n';
    std::cout << "Пустое место - '.'; мина -  '*'." << '\n';
    std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    std::string temp_input, check_string;
    int array_size_N = 0, array_size_M = 0, number, repeat = 1, repeat1 = 1;
    int i, j, k, number_i, number_j;


    do
    {
        do
        {
            // Ввод количества строк поля и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы)
            while (true)
            {
                std::cout << "Введите количество строк игрового поля (натуральное число): ";
                std::cin >> temp_input;
                if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                {
                    array_size_N = std::stoi(temp_input);
                    check_string = std::to_string(array_size_N);

                    if ((check_string.length() != temp_input.length()) || (array_size_N == 0))
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                        while (std::cin.get() != '\n');
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                }
            }
            std::cout << "\n";

            // Ввод количества столбцов игрового поля и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы)
            while (true)
            {
                std::cout << "Введите количество столбцов игрового поля (натуральное число): ";
                std::cin >> temp_input;
                if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                {
                    array_size_M = std::stoi(temp_input);
                    check_string = std::to_string(array_size_M);

                    if ((check_string.length() != temp_input.length()) || (array_size_M == 0))
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                        while (std::cin.get() != '\n');
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                }
            }
            std::cout << "\n";

            if ((array_size_N == 1) && (array_size_M == 1))
            {
                std::cout << "Повторите ввод. Игровое поле не может быть 1x1" << "\n";
                repeat1 = 1;
            }
            else
            {
                repeat1 = 0;
            }
        } while (repeat1 == 1);

        // Ввод количества мин на игровом поле и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы)
        while (true)
        {
            std::cout << "Введите количество мин на игровом поле (натуральное число): ";
            std::cin >> temp_input;
            if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
            {
                number = std::stoi(temp_input);
                check_string = std::to_string(number);

                if ((check_string.length() != temp_input.length()) || (number == 0) || (number >= array_size_N * array_size_M))
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Повторите ввод. Некорректное значение." << "\n";
                std::cin.clear();
                while (std::cin.get() != '\n');
            }
        }
        std::cout << "\n";

        // выделение динамической памяти для игрового поля
        char** a = NULL;
        a = (char**)malloc(array_size_N * sizeof(char*));
        for (i = 0; i < array_size_N; i++)
        {
            a[i] = (char*)malloc(array_size_M * sizeof(char));
        }

        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_M; j++)
            {
                a[i][j] = '.'; // *(a[j] + i * array_size_M)
            }
        }

        // Ввод координат, где располагаются мины и проверка на корректность ввода (неотрицательные целые числа, не содержит буквы)
        std::cout << "Введите координаты мин на игровом поле (неотрицательные целые числа)" << "\n";
        std::cout << "   номер строки от 0 до " << array_size_N - 1 << "\n";
        std::cout << "   номер столбца от 0 до  " << array_size_M - 1 << "\n";

        for (k = 1; k <= number; k++)
        {
            std::cout << "Введите координаты " << k << " мины: " << "\n";
            while (true)
            {
                std::cout << "   номер строки, в которой располагается мина: ";
                std::cin >> temp_input;
                if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                {
                    number_i = std::stoi(temp_input);
                    check_string = std::to_string(number_i);
                    if (check_string.length() != temp_input.length() || (number_i > array_size_N - 1))
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                        while (std::cin.get() != '\n');
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                }
            }
            while (true)
            {
                std::cout << "   номер столбца, в которой располагается мина: ";
                std::cin >> temp_input;
                if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                {
                    number_j = std::stoi(temp_input);
                    check_string = std::to_string(number_j);
                    if (check_string.length() != temp_input.length() || (number_j > array_size_M - 1))
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                        while (std::cin.get() != '\n');
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                }
            }
            a[number_i][number_j] = '*';
        }

        std::cout << "\n" << "Введены следующие данные:" << "\n";

        std::cout << "Игровое поле " << array_size_N << "x" << array_size_M << "\n";
        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_M; j++)
            {
                std::cout << a[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        // замена '.' на 0 
        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_M; j++)
            {
                if (a[i][j] == '.')
                {
                    a[i][j] = '0';
                }
                //std::cout << a[i][j] << " ";
            }
            //std::cout << "\n";
        }

        // игровое поле NxM
        if ((array_size_N > 1) && (array_size_M > 1))
        {
            // если a[0][0] = '*'
            if (a[0][0] == '*')
            {
                if (a[0][1] != '*') { a[0][1] = a[0][1] + 1; }
                if (a[1][0] != '*') { a[1][0] = a[1][0] + 1; }
                if (a[1][1] != '*') { a[1][1] = a[1][1] + 1; }
            }

            // если a[0][array_size_M-1] = '*'
            if (a[0][array_size_M - 1] == '*')
            {
                if (a[0][array_size_M - 2] != '*') { a[0][array_size_M - 2] = a[0][array_size_M - 2] + 1; }
                if (a[1][array_size_M - 2] != '*') { a[1][array_size_M - 2] = a[1][array_size_M - 2] + 1; }
                if (a[1][array_size_M - 1] != '*') { a[1][array_size_M - 1] = a[1][array_size_M - 1] + 1; }
            }

            // если a[array_size_N-1][0] = '*'
            if (a[array_size_N - 1][0] == '*')
            {
                if (a[array_size_N - 2][0] != '*') { a[array_size_N - 2][0] = a[array_size_N - 2][0] + 1; }
                if (a[array_size_N - 2][1] != '*') { a[array_size_N - 2][1] = a[array_size_N - 2][1] + 1; }
                if (a[array_size_N - 1][1] != '*') { a[array_size_N - 1][1] = a[array_size_N - 1][1] + 1; }
            }

            // если a[array_size_N-1][array_size_M-1] = '*'
            if (a[array_size_N - 1][array_size_M - 1] == '*')
            {
                if (a[array_size_N - 2][array_size_M - 1] != '*') { a[array_size_N - 2][array_size_M - 1] = a[array_size_N - 2][array_size_M - 1] + 1; }
                if (a[array_size_N - 2][array_size_M - 2] != '*') { a[array_size_N - 2][array_size_M - 2] = a[array_size_N - 2][array_size_M - 2] + 1; }
                if (a[array_size_N - 1][array_size_M - 2] != '*') { a[array_size_N - 1][array_size_M - 2] = a[array_size_N - 1][array_size_M - 2] + 1; }
            }

            // 0-строка
            for (j = 1; j <= array_size_M - 2; j++)
            {
                if (a[0][j] == '*')
                {
                    if (a[0][j - 1] != '*') { a[0][j - 1] = a[0][j - 1] + 1; }
                    if (a[0][j + 1] != '*') { a[0][j + 1] = a[0][j + 1] + 1; }
                    if (a[1][j - 1] != '*') { a[1][j - 1] = a[1][j - 1] + 1; }
                    if (a[1][j] != '*') { a[1][j] = a[1][j] + 1; }
                    if (a[1][j + 1] != '*') { a[1][j + 1] = a[1][j + 1] + 1; }
                }
            }

            // последняя строка
            for (j = 1; j <= array_size_M - 2; j++)
            {
                if (a[array_size_N - 1][j] == '*')
                {
                    if (a[array_size_N - 1][j - 1] != '*') { a[array_size_N - 1][j - 1] = a[array_size_N - 1][j - 1] + 1; }
                    if (a[array_size_N - 1][j + 1] != '*') { a[array_size_N - 1][j + 1] = a[array_size_N - 1][j + 1] + 1; }
                    if (a[array_size_N - 2][j - 1] != '*') { a[array_size_N - 2][j - 1] = a[array_size_N - 2][j - 1] + 1; }
                    if (a[array_size_N - 2][j] != '*') { a[array_size_N - 2][j] = a[array_size_N - 2][j] + 1; }
                    if (a[array_size_N - 2][j + 1] != '*') { a[array_size_N - 2][j + 1] = a[array_size_N - 2][j + 1] + 1; }
                }
            }

            // 0-столбец
            for (i = 1; i <= array_size_N - 2; i++)
            {
                if (a[i][0] == '*')
                {
                    if (a[i - 1][0] != '*') { a[i - 1][0] = a[i - 1][0] + 1; }
                    if (a[i + 1][0] != '*') { a[i + 1][0] = a[i + 1][0] + 1; }
                    if (a[i - 1][1] != '*') { a[i - 1][1] = a[i - 1][1] + 1; }
                    if (a[i][1] != '*') { a[i][1] = a[i][1] + 1; }
                    if (a[i + 1][1] != '*') { a[i + 1][1] = a[i + 1][1] + 1; }
                }
            }

            // последний столбец
            for (i = 1; i <= array_size_N - 2; i++)
            {
                if (a[i][array_size_M - 1] == '*')
                {
                    if (a[i - 1][array_size_M - 1] != '*') { a[i - 1][array_size_M - 1] = a[i - 1][array_size_M - 1] + 1; }
                    if (a[i + 1][array_size_M - 1] != '*') { a[i + 1][array_size_M - 1] = a[i + 1][array_size_M - 1] + 1; }
                    if (a[i - 1][array_size_M - 2] != '*') { a[i - 1][array_size_M - 2] = a[i - 1][array_size_M - 2] + 1; }
                    if (a[i][array_size_M - 2] != '*') { a[i][array_size_M - 2] = a[i][array_size_M - 2] + 1; }
                    if (a[i + 1][array_size_M - 2] != '*') { a[i + 1][array_size_M - 2] = a[i + 1][array_size_M - 2] + 1; }
                }
            }

            // внутри игрового поля
            for (i = 1; i <= array_size_N - 2; i++)
            {
                for (j = 1; j <= array_size_M - 2; j++)
                {
                    if (a[i][j] == '*')
                    {
                        if (a[i - 1][j - 1] != '*') { a[i - 1][j - 1] = a[i - 1][j - 1] + 1; }
                        if (a[i - 1][j] != '*') { a[i - 1][j] = a[i - 1][j] + 1; }
                        if (a[i - 1][j + 1] != '*') { a[i - 1][j + 1] = a[i - 1][j + 1] + 1; }
                        if (a[i][j - 1] != '*') { a[i][j - 1] = a[i][j - 1] + 1; }
                        if (a[i][j + 1] != '*') { a[i][j + 1] = a[i][j + 1] + 1; }
                        if (a[i + 1][j - 1] != '*') { a[i + 1][j - 1] = a[i + 1][j - 1] + 1; }
                        if (a[i + 1][j] != '*') { a[i + 1][j] = a[i + 1][j] + 1; }
                        if (a[i + 1][j + 1] != '*') { a[i + 1][j + 1] = a[i + 1][j + 1] + 1; }
                    }
                }
            }
        }

        // игровое поле 1xM
        if ((array_size_N == 1) && (array_size_M > 1))
        {
            // если a[0][0] = '*'
            if (a[0][0] == '*')
            {
                if (a[0][1] != '*') { a[0][1] = a[0][1] + 1; }
            }

            // если a[0][array_size_M-1] = '*'
            if (a[0][array_size_M - 1] == '*')
            {
                if (a[0][array_size_M - 2] != '*') { a[0][array_size_M - 2] = a[0][array_size_M - 2] + 1; }
            }

            // 0-строка
            for (j = 1; j <= array_size_M - 2; j++)
            {
                if (a[0][j] == '*')
                {
                    if (a[0][j - 1] != '*') { a[0][j - 1] = a[0][j - 1] + 1; }
                    if (a[0][j + 1] != '*') { a[0][j + 1] = a[0][j + 1] + 1; }
                }
            }
        }


        // игровое поле Nx1
        if ((array_size_N > 1) && (array_size_M == 1))
        {
            // если a[0][0] = '*'
            if (a[0][0] == '*')
            {
                if (a[1][0] != '*') { a[1][0] = a[1][0] + 1; }
            }

            // если a[array_size_N-1][0] = '*'
            if (a[array_size_N - 1][0] == '*')
            {
                if (a[array_size_N - 2][0] != '*') { a[array_size_N - 2][0] = a[array_size_N - 2][0] + 1; }
            }

            // 0-столбец
            for (i = 1; i <= array_size_N - 2; i++)
            {
                if (a[i][0] == '*')
                {
                    if (a[i - 1][0] != '*') { a[i - 1][0] = a[i - 1][0] + 1; }
                    if (a[i + 1][0] != '*') { a[i + 1][0] = a[i + 1][0] + 1; }
                }
            }
        }




        // игровое поле
        std::cout << "Игровое поле, дополненное числами, как в оригинальной игре " << "\n";
        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_M; j++)
            {
                std::cout << a[i][j] << " ";
            }
            std::cout << "\n";
        }

        // удаление массива из памяти        
        for (i = 0; i < array_size_N; i++)
        {
            free(a[i]);
        }
        free(a);
        a = NULL;

        // Повторный запуск программы
        std::cout << '\n' << "Для повторного ввода данных введите 1 и нажмите ENTER; для окончания работы - любой другой символ и нажмите ENTER: ";
        std::cin >> temp_input;
        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
        {
            repeat = std::stoi(temp_input);
            check_string = std::to_string(repeat);
            if ((check_string.length() != temp_input.length()) || (repeat != 1))
            {
                std::cout << "Программа завершила работу." << "\n";
                repeat = 0;
            }
        }
        else
        {
            std::cout << "Программа завершила работу." << "\n";
            repeat = 0;
        }

    } while (repeat == 1);

    return 0;
}