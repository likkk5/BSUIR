#include <iostream>
#include <string>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 11. Игра Сапер. Игровое поле n*m " << '\n';
    std::cout << "Пустое место - '.'; мина -  '*'." << '\n';
    std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    std::string temp_input, check_string;
    int array_size_N = 0, array_size_M = 0, repeat = 1, repeat1 = 1;
    int i, j;


    do
    {
        do
        {
            // Ввод количества строк поля и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
            while (true)
            {
                std::cout << "Введите количество строк игрового поля (натуральное число): ";
                getline(std::cin, temp_input);
                if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                {
                    // <=2147483647
                    if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
                    {
                        array_size_N = std::stoi(temp_input);
                        check_string = std::to_string(array_size_N);

                        if ((check_string.length() != temp_input.length()) || (array_size_N < 1))
                        {
                            std::cout << "Повторите ввод. Некорректное значение." << "\n";
                            std::cin.clear();
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
                    }
                }
                else
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                }
            }
            std::cout << "\n";

            // Ввод количества столбцов игрового поля и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
            while (true)
            {
                std::cout << "Введите количество столбцов игрового поля (натуральное число): ";
                getline(std::cin, temp_input);
                if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                {
                    // <=2147483647
                    if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
                    {
                        array_size_M = std::stoi(temp_input);
                        check_string = std::to_string(array_size_M);

                        if ((check_string.length() != temp_input.length()) || (array_size_M < 1))
                        {
                            std::cout << "Повторите ввод. Некорректное значение." << "\n";
                            std::cin.clear();
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
                    }
                }
                else
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
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

        // выделение динамической памяти для игрового поля
        char** a = NULL;
        a = (char**)malloc(array_size_N * sizeof(char*));
        for (i = 0; i < array_size_N; i++)
        {
            a[i] = (char*)malloc(array_size_M * sizeof(char));
        }

        // Ввод элементов игрового поля и проверка на корректность ввода (могут быть только '.' и '*')
        std::cout << "Введите элементы игрового поля: . - пустое место; * - мина" << "\n";
        repeat1 = 0;
        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_M; j++)
            {
                while (true)
                {
                    std::cout << "Введите a[" << i << "][" << j << "] = ";
                    getline(std::cin, temp_input);
                    a[i][j] = temp_input[0];

                    if (temp_input.length() > 1 || (a[i][j] != '.') && (a[i][j] != '*'))
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                    }
                    else
                    {
                        break;
                    }

                }
            }
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
        std::cout << '\n' << "Для повторного ввода данных введите 1 и нажать ENTER; для окончания работы - любой другой символ и нажать ENTER: ";
        std::cin >> temp_input;

        if ((temp_input[0] == '1') && (temp_input.length() == 1))
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