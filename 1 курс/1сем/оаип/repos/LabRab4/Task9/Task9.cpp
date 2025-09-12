#include <iostream>
#include <string>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 9. Дан трехмерный динамический массив размером n*n*n неотрицательных целых чисел." << '\n';
    std::cout << "Необходимо определить диагональ с наибольшей суммой чисел." << '\n';
    std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    std::string temp_input, check_string;
    int array_size_N = 0, repeat = 1;
    int i, j, k, l;
    int d1, d2, d3, d4, sum_max;

    do
    {
        // Ввод размерности массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        while (true)
        {
            std::cout << "Введите размерность трехмерного массива (натуральное число): ";
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

        // выделение динамической памяти
        int*** a = NULL;
        a = (int***)malloc(array_size_N * sizeof(int**));
        for (int j = 0; j < array_size_N; j++)
        {
            a[j] = (int**)malloc(array_size_N * sizeof(int*));
            for (int k = 0; k < array_size_N; k++)
            {
                a[j][k] = (int*)malloc(array_size_N * sizeof(int));
            }
        }

        // Ввод элементов массива и проверка на корректность ввода (неотрицательные целые числа, не содержит буквы)
        std::cout << "Введите элементы матрицы (неотрицательные целые числа)" << "\n";
        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_N; j++)
            {
                for (k = 0; k < array_size_N; k++)
                {
                    while (true)
                    {
                        std::cout << "Введите a[" << i << "][" << j << "][" << k << "] = ";
                        getline(std::cin, temp_input);

                        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
                        {
                            // <=2147483647
                            if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
                            {
                                *(a[j][k]+i*array_size_N) = std::stoi(temp_input);
                                check_string = std::to_string(std::stoi(temp_input));

                                if ((check_string.length() != temp_input.length()) || (array_size_N < 0))
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

        std::cout << "Элементы трехмерной матрицы размера " << array_size_N << "x" << array_size_N << "x" << array_size_N << "\n";
        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_N; j++)
            {
                for (k = 0; k < array_size_N; k++)
                {
                    std::cout << "a[" << i << "][" << j << "][" << k << "] = " << *(a[j][k] + i * array_size_N) << " " << "\n ";
                }
            }
        }

        sum_max = 0;

        // элементы и сумма элементов диагоналей матрицы
        l = 0;
        d1 = 0;
        std::cout << "\n" << "Элементы 1-ой диагонали: " << "\n";
        while (l < array_size_N)
        {
            std::cout << "a[" << l << "][" << l << "][" << l << "] = " << (*(a[l][l] + l * array_size_N)) << "\n";
            d1 = d1 + (*(a[l][l] + l * array_size_N));
            l = l + 1;
        }
        std::cout << "Сумма элементов 1-ой диагонали: " << d1 << "\n";

        l = 0;
        d2 = 0;
        std::cout << "\n" << "Элементы 2-ой диагонали: " << "\n";
        while (l < array_size_N)
        {
            std::cout << "a[" << array_size_N - 1 - l << "][" << l << "][" << l << "] = " << (*(a[l][l] + (array_size_N - 1 - l) * array_size_N)) << "\n";
            d2 = d2 + (*(a[l][l] + (array_size_N - 1 - l) * array_size_N));
            l = l + 1;
        }
        std::cout << "Сумма элементов 2-ой диагонали: " << d2 << "\n";

        l = 0;
        d3 = 0;
        std::cout << "\n" << "Элементы 3-ей диагонали: " << "\n";
        while (l < array_size_N)
        {
            std::cout << "a[" << l << "][" << array_size_N - 1 - l << "][" << l << "] = " << (*(a[array_size_N - 1 - l][l] + l * array_size_N)) << "\n";
            d3 = d3 + (*(a[array_size_N - 1 - l][l] + l * array_size_N));
            l = l + 1;
        }
        std::cout << "Сумма элементов 3-ей диагонали: " << d3 << "\n";

        l = 0;
        d4 = 0;
        std::cout << "\n" << "Элементы 4-ой диагонали: " << "\n";
        while (l < array_size_N)
        {
            std::cout << "a[" << l << "][" << l << "][" << array_size_N - 1 - l << "] = " << (*(a[l][array_size_N - 1 - l] + l * array_size_N)) << "\n";
            d4 = d4 + (*(a[l][array_size_N - 1 - l] + l * array_size_N));
            l = l + 1;
        }
        std::cout << "Сумма элементов 4-ой диагонали: " << d4 << "\n";

        if (d1 > d2)
        {
            sum_max = d1;
        }
        else
        {
            sum_max = d2;
        }

        if (d3 > sum_max)
        {
            sum_max = d3;
        }

        if (d4 > sum_max)
        {
            sum_max = d4;
        }

        std::cout << "\n" << "Наибольшая сумма элементов равна " << sum_max << " (диагональ ";
        if (d1 == sum_max)
        {
            std::cout << 1 << " ";
        }
        if (d2 == sum_max)
        {
            std::cout << 2 << " ";
        }
        if (d3 == sum_max)
        {
            std::cout << 3 << " ";
        }
        if (d4 == sum_max)
        {
            std::cout << 4 << " ";
        }
        std::cout << ")" << "\n";


        // удаление массива из памяти        
        /*for (j = 0; j < array_size_N; j++)
        {
            for (k = 0; k < array_size_N; k++)
            {
                free(a[j][k]);
            }
        }
        for (j = 0; j < array_size_N; j++)
        {
            free(a[j]);
        }*/

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