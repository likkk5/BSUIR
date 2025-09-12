#include <iostream>
#include <string>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 2. Инициализировать при объявлении статический двумерный массив целых чисел размером N*M." << '\n';
    std::cout << "Вариант 13. Найти сумму элементов, расположенных в четных (по номеру) строках матрицы." << '\n';
    std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    std::string temp_input, check_string;
    int array_size_N = 0, array_size_M = 0, sum, repeat = 1;
    int a[100][100]{};

    do
    {
        sum = 0;

        // Ввод количества строк массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        while (true)
        {
            std::cout << "Введите количество строк массива (натуральное число): ";
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

        // Ввод количества столбцов массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        while (true)
        {
            std::cout << "Введите количество столбцов массива (натуральное число): ";
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

        // Ввод элементов массива и проверка на корректность ввода (целые числа, не содержит буквы)
        std::cout << "Введите элементы матрицы (целые числа)" << "\n";
        for (int i = 0; i < array_size_N; i++)
        {
            for (int j = 0; j < array_size_M; j++)
            {
                while (true)
                {
                    std::cout << "Введите a[" << i << "][" << j << "] = ";
                    getline(std::cin, temp_input);
                    if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                    {
                        // <=2147483647
                        if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
                        {
                            a[i][j] = std::stoi(temp_input);
                            check_string = std::to_string(a[i][j]);

                            if (check_string.length() != temp_input.length())
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
                        if ((temp_input[0] == 45) && (temp_input[1] >= 48) && (temp_input[1] <= 57))
                        {
                            // >= - 2147483648
                            if ((temp_input.length() < 11) || ((temp_input.length() == 11) && ((temp_input[1] < 50) || ((temp_input[1] == 50) && (temp_input[2] <= 49) && (temp_input[3] <= 52) && (temp_input[4] <= 55) && (temp_input[5] <= 52) && (temp_input[6] <= 56) && (temp_input[7] <= 51) && (temp_input[8] <= 54) && (temp_input[9] <= 52) && (temp_input[10] <= 56)))))
                            {
                                a[i][j] = std::stoi(temp_input);
                                check_string = std::to_string(a[i][j]);

                                if (check_string.length() != temp_input.length())
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
                }
            }
        }

        std::cout << "\n" << "Введены следующие данные:" << "\n";

        std::cout << "Размерность массива " << array_size_N << "x" << array_size_M << "\n";

        std::cout << "Элементы массива: " << "\n ";
        for (int i = 0; i < array_size_N; i++)
        {
            for (int j = 0; j < array_size_M; j++)
            {
                std::cout << a[i][j] << " ";
            }
            std::cout << "\n ";

            if ((i + 1) % 2 == 0)
            {
                for (int j = 0; j < array_size_M; j++)
                    sum = sum + a[i][j];
            }

        }

        if (array_size_N > 1)
        {
            std::cout << "\n" << "Сумма элементов массива, расположенных в четных (по номеру) строках матрицы: " << sum << "\n";
        }
        else 
        {
            std::cout << "\n" << "В массиве нет четных (по номеру) строк. " << "\n";
        }

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

