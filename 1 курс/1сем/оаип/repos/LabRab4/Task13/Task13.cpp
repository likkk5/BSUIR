#include <iostream>
#include <string>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 14. Построить магический квадрат размерности n*n." << '\n';
    std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    std::string temp_input, check_string;
    long long array_size_N = 0, amount, new_size_N, new_amount, change = 0, repeat = 1;
    long long number = 0;
    long long i, j, i_previous, j_previous, k, sum;
    //9223372036854775807 - максимальное число в long long
    //4294967296 = 2^32
    //3037000499 - максимальное число, для которого можно вычислить количество элементов магического квадрата (array_size_N * array_size_N) для типа данных long long
    //2097151 - максимальное число, для которого можно вычислить магическую константу (array_size_N * array_size_N) для типа данных long long,
    //          а также сумму элементов любой строки, любого столбца, диагоналей (проверка сформированного квадрата)

    do
    {
        // Ввод размерности магического квадрата и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы)
        while (true)
        {
            std::cout << "Введите размерность магического квадрата: ";
            getline(std::cin, temp_input);

            k = 0;

            if ((temp_input.length() > 19) || (temp_input[0] == 55))
            {
                std::cout << "Повторите ввод. Некорректное значение." << "\n";
                std::cin.clear();
            }
            else
            {
                array_size_N = 0;
                if ((temp_input.length() < 19) && (temp_input[0] != 55))
                {
                    for (unsigned int p = 0; p <= temp_input.length() - 1; p++)
                    {
                        if ((temp_input[p] >= 48) && (temp_input[p] <= 57))
                        {
                            number = long long(temp_input[p]) - 48;
                            for (unsigned int q = 1; q <= temp_input.length() - 1 - p; q++)
                            {
                                number = 10 * number;
                            }
                        }
                        else
                        {
                            k = 1;
                        }
                        array_size_N = array_size_N + number;
                    }

                    check_string = std::to_string(array_size_N);

                    if (check_string.length() != temp_input.length() || (array_size_N <= 0) || (k == 1))
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                    }
                    else
                    {
                        if (array_size_N == 2)
                        {
                            std::cout << "Повторите ввод. Нельзя построить магический квадрат 2x2." << "\n";
                            std::cin.clear();
                        }
                        else
                        {
                            if ((array_size_N > 35000) && (array_size_N <= 2097151))
                            {
                                std::cout << "Повторите ввод. Вы ввели очень большое число. Магический квадрат будет долго формироваться. Магическая константа равна " << (array_size_N * (array_size_N * array_size_N + 1)) / 2 << "\n";
                                std::cin.clear();
                            }
                            else
                            {
                                if ((array_size_N > 2097151) && (array_size_N <= 3037000499))
                                {
                                    std::cout << "Повторите ввод. Вы ввели слишком большое число. Магический квадрат будет очень-очень долго формироваться. Но осуществить проверку не сможем." << "\n";
                                    std::cin.clear();
                                }
                                else
                                {
                                    if (array_size_N > 3037000499)
                                    {
                                        std::cout << "Повторите ввод. Вы ввели слишком большое число. Сформировать магический квадрат не получится." << "\n";
                                        std::cin.clear();
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if ((temp_input.length() == 19) && (temp_input[0] >= 48) && (temp_input[0] <= 57) && (temp_input[1] <= 50) && (temp_input[2] <= 50) && (temp_input[3] <= 51) && (temp_input[4] <= 51) && (temp_input[5] <= 55) && (temp_input[6] <= 50) && (temp_input[7] <= 48) && (temp_input[8] <= 51) && (temp_input[9] <= 54) && (temp_input[10] <= 56) && (temp_input[11] <= 53) && (temp_input[12] <= 52) && (temp_input[13] <= 55) && (temp_input[14] <= 55) && (temp_input[15] <= 53) && (temp_input[16] <= 56) && (temp_input[17] <= 48) && (temp_input[18] <= 55))
                    {
                        array_size_N = 0;
                        for (unsigned int p = 0; p <= temp_input.length() - 1; p++)
                        {
                            if ((temp_input[p] >= 48) && (temp_input[p] <= 57))
                            {
                                number = long long(temp_input[p]) - 48;
                                for (unsigned int q = 1; q <= temp_input.length() - 1 - p; q++)
                                {
                                    number = 10 * number;
                                }
                            }
                            else
                            {
                                k = 1;
                            }
                            array_size_N = array_size_N + number;
                        }

                        check_string = std::to_string(array_size_N);

                        if (check_string.length() != temp_input.length() || (array_size_N <= 0) || (k == 1))
                        {
                            std::cout << "Повторите ввод. Некорректное значение." << "\n";
                            std::cin.clear();
                        }
                        else
                        {
                            std::cout << "Повторите ввод. Вы ввели слишком большое число. Сформировать магический квадрат не получится." << "\n";
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


        if (array_size_N > 14000)
        {
            std::cout << "\n" << "Вы ввели слишком большое число. Магический квадрат формируется. Ожидайте." << "\n";
        }

        // выделение динамической памяти для игрового поля
        long long** a = NULL;
        a = (long long**)malloc(array_size_N * sizeof(long long*));
        for (i = 0; i < array_size_N; i++)
        {
            a[i] = (long long*)malloc(array_size_N * sizeof(long long));
        }

        for (i = 0; i < array_size_N; i++)
        {
            for (j = 0; j < array_size_N; j++)
            {
                a[i][j] = 0;
                //std::cout << a[i][j] << "\t";
            }
            //std::cout << "\n";
        }

        // 1. n - нечетное
        if (array_size_N % 2 != 0)
        {
            amount = array_size_N * array_size_N;
            i = 0;
            j = array_size_N / 2;
            i_previous = 0;
            j_previous = 0;

            for (k = 1; k <= amount; k++)
            {
                if (i < 0)
                {
                    i = array_size_N - 1;
                }

                if (j > array_size_N - 1)
                {
                    j = 0;
                }

                if (a[i][j] != 0)
                {
                    i = i_previous + 1;
                    j = j_previous;
                }

                a[i][j] = k;
                i_previous = i;
                j_previous = j;

                i = i - 1;
                j = j + 1;
            }
        }


        // 2. n - одинарная четность (делится на 2, но не на 4)
        if ((array_size_N % 2 == 0) && (array_size_N % 4 != 0) && array_size_N >= 6)
        {
            new_size_N = array_size_N / 2;
            new_amount = new_size_N * new_size_N;
            // первый квадрат - верхний левый
            i = 0;
            j = new_size_N / 2;
            i_previous = 0;
            j_previous = 0;

            for (k = 1; k <= new_amount; k++)
            {
                if (i < 0)
                {
                    i = new_size_N - 1;
                }

                if (j > new_size_N - 1)
                {
                    j = 0;
                }

                if (a[i][j] != 0)
                {
                    i = i_previous + 1;
                    j = j_previous;
                }

                a[i][j] = k;
                i_previous = i;
                j_previous = j;

                i = i - 1;
                j = j + 1;
            }

            // второй квадрат - нижний правый
            i = new_size_N;
            j = new_size_N + new_size_N / 2;
            i_previous = 0;
            j_previous = 0;

            for (k = new_amount + 1; k <= 2 * new_amount; k++)
            {
                if (i < new_size_N)
                {
                    i = array_size_N - 1;
                }

                if (j > array_size_N - 1)
                {
                    j = new_size_N;
                }

                if (a[i][j] != 0)
                {
                    i = i_previous + 1;
                    j = j_previous;
                }

                a[i][j] = k;
                i_previous = i;
                j_previous = j;

                i = i - 1;
                j = j + 1;
            }

            // третий квадрат - верхний правый
            i = 0;
            j = new_size_N + new_size_N / 2;
            i_previous = 0;
            j_previous = 0;

            for (k = 2 * new_amount + 1; k <= 3 * new_amount; k++)
            {
                if (i < 0)
                {
                    i = new_size_N - 1;
                }

                if (j > array_size_N - 1)
                {
                    j = new_size_N;
                }

                if (a[i][j] != 0)
                {
                    i = i_previous + 1;
                    j = j_previous;
                }

                a[i][j] = k;
                i_previous = i;
                j_previous = j;

                i = i - 1;
                j = j + 1;
            }

            // четвертый квадрат - нижний левый
            i = new_size_N;
            j = new_size_N / 2;
            i_previous = 0;
            j_previous = 0;

            for (k = 3 * new_amount + 1; k <= 4 * new_amount; k++)
            {
                if (i < new_size_N)
                {
                    i = array_size_N - 1;
                }

                if (j > new_size_N - 1)
                {
                    j = 0;
                }

                if (a[i][j] != 0)
                {
                    i = i_previous + 1;
                    j = j_previous;
                }

                a[i][j] = k;
                i_previous = i;
                j_previous = j;

                i = i - 1;
                j = j + 1;
            }

            // некоторые элементы меняются с другими местами
            k = new_size_N / 2;
            // меняются местами элементы верхнего левого квадрата размера (new_size_N / 2) * (new_size_N / 2) из верхнего левого квадрата размера new_size_N * new_size_N 
            // с элементами верхнего левого квадрата размера (new_size_N / 2) * (new_size_N / 2) из нижнего левого квадрата размера new_size_N * new_size_N 
            for (i = 0; i <= (k - 1); i++)
            {
                for (j = 0; j <= (k - 1); j++)
                {
                    change = a[i][j];
                    a[i][j] = a[i + new_size_N][j];
                    a[i + new_size_N][j] = change;
                }
            }

            // меняются местами (new_size_N / 2) - элементов в строке (new_size_N / 2), начиная с j = 1 
            // с (new_size_N / 2) - элементами в строке (new_size_N / 2 + new_size_N), начиная с j = 1
            for (j = 1; j <= k; j++)
            {
                change = a[k][j];
                a[k][j] = a[k + new_size_N][j];
                a[k + new_size_N][j] = change;
            }

            // меняются местами элементы нижнего левого квадрата размера (new_size_N / 2) * (new_size_N / 2) из верхнего левого квадрата размера new_size_N * new_size_N 
            // с элементами нижнего левого квадрата размера (new_size_N / 2) * (new_size_N / 2) из нижнего левого квадрата размера new_size_N * new_size_N 
            for (i = k + 1; i <= new_size_N - 1; i++)
            {
                for (j = 0; j <= (k - 1); j++)
                {
                    change = a[i][j];
                    a[i][j] = a[i + new_size_N][j];
                    a[i + new_size_N][j] = change;
                }
            }

            // меняются местами элементы последних (new_size_N / 2 - 1) столбцов из верхнего правого квадрата размера new_size_N * new_size_N 
            // с элементами последних (new_size_N / 2 - 1) столбцов из верхнего правого квадрата размера new_size_N * new_size_N
            for (i = 0; i <= new_size_N - 1; i++)
            {
                for (j = array_size_N - (k - 1); j <= array_size_N - 1; j++)
                {
                    change = a[i][j];
                    a[i][j] = a[i + new_size_N][j];
                    a[i + new_size_N][j] = change;
                }
            }
        }

        // 3. n - двойная четность (делится на 4)
        if (array_size_N % 4 == 0)
        {
            amount = array_size_N * array_size_N;

            // заполняем квадрат числами от 1 до amount = array_size_N * array_size_N  
            for (i = 0; i < array_size_N; i++)
            {
                for (j = 0; j < array_size_N; j++)
                {
                    a[i][j] = (array_size_N * i) + j + 1;
                }
            }

            // меняем элементы квадрата по формуле (amount + 1) - a[i][j]

            // верхний левый квадрат размера (array_size_N / 4) * (array_size_N / 4)
            for (i = 0; i < array_size_N / 4; i++)
            {
                for (j = 0; j < array_size_N / 4; j++)
                {
                    a[i][j] = (amount + 1) - a[i][j];
                }
            }

            // верхний правый квадрат размера (array_size_N / 4) * (array_size_N / 4)
            for (i = 0; i < array_size_N / 4; i++)
            {
                for (j = 3 * (array_size_N / 4); j < array_size_N; j++)
                {
                    a[i][j] = (amount + 1) - a[i][j];
                }
            }

            // нижний левый квадрат размера (array_size_N / 4) * (array_size_N / 4) 
            for (i = 3 * array_size_N / 4; i < array_size_N; i++)
            {
                for (j = 0; j < array_size_N / 4; j++)
                {
                    a[i][j] = (amount + 1) - a[i][j];
                }
            }

            // нижний правый квадрат размера (array_size_N / 4) * (array_size_N / 4)
            for (i = 3 * array_size_N / 4; i < array_size_N; i++)
            {
                for (j = 3 * array_size_N / 4; j < array_size_N; j++)
                {
                    a[i][j] = (amount + 1) - a[i][j];
                }
            }

            // центральный квадрат размера (array_size_N / 2) * (array_size_N / 2)
            for (i = array_size_N / 4; i < 3 * array_size_N / 4; i++)
            {
                for (j = array_size_N / 4; j < 3 * array_size_N / 4; j++)
                {
                    a[i][j] = (amount + 1) - a[i][j];
                }
            }
        }


        // магический квадрат - вывод на экран
        k = 1;
        if ((array_size_N > 16) && (array_size_N <= 100))
        {
            std::cout << "\n" << "Магический квадрат " << array_size_N << "x" << array_size_N << " сформирован" << "\n";
            std::cout << "Отображаться на экране будет не очень понятно." << "\n";
            std::cout << "Если все-таки хотите напечатать магический квадрат, введите 1 и нажмите ENTER: ";
            std::cin >> temp_input;
            if ((temp_input[0] == '1') && (temp_input.length() == 1))
            {
                k = 1;
            }
            else
            {
                k = 2;
            }
        }

        if ((array_size_N > 100) && (array_size_N <= 500))
        {
            std::cout << "\n" << "Магический квадрат " << array_size_N << "x" << array_size_N << " сформирован" << "\n";
            std::cout << "Отображаться на экране будет долго или даже очень долго и не очень понятно." << "\n";
            std::cout << "Если все-таки хотите напечатать магический квадрат, введите 1 и нажмите ENTER: ";
            std::cin >> temp_input;
            if ((temp_input[0] == '1') && (temp_input.length() == 1))
            {
                k = 1;
            }
            else
            {
                k = 2;
            }
        }

        if (array_size_N > 500)
        {
            std::cout << "\n" << "Магический квадрат " << array_size_N << "x" << array_size_N << " сформирован" << "\n";
            std::cout << "Отображаться на экране будет очень-очень-очень долго. Даже не предлагаем его выводить на экран." << "\n";
            std::cout << "Если хотите напечатать проверку, что квадрат магический, введите 1 и нажмите ENTER: ";
            std::cin >> temp_input;
            if ((temp_input[0] == '1') && (temp_input.length() == 1))
            {
                k = 2;
            }
            else
            {
                k = 3;
            }

        }

        // вывод на экран магического квадрата
        if (k == 1)
        {
            std::cout << "\n" << "Магический квадрат " << array_size_N << "x" << array_size_N << "\n";
            for (i = 0; i < array_size_N; i++)
            {
                for (j = 0; j < array_size_N; j++)
                {
                    std::cout << a[i][j] << "\t";
                }
                std::cout << "\n";
            }
            k = 2;
        }

        // проверка

        if (k == 2)
        {
            std::cout << "\n" << "Магическая константа равна " << (array_size_N * (array_size_N * array_size_N + 1)) / 2 << "\n";

            for (i = 0; i < array_size_N; i++)
            {
                sum = 0;
                for (j = 0; j < array_size_N; j++)
                {
                    sum = sum + a[i][j];
                }
                std::cout << "Cумма элементов " << i << " строки равна " << sum << "\n";
            }

            for (j = 0; j < array_size_N; j++)
            {
                sum = 0;
                for (i = 0; i < array_size_N; i++)
                {
                    sum = sum + a[i][j];
                }
                std::cout << "Cумма элементов " << j << " столбца равна " << sum << "\n";
            }

            sum = 0;
            for (i = 0; i < array_size_N; i++)
            {
                sum = sum + a[i][i];

            }
            std::cout << "Cумма элементов 1-ой диагонали равна " << sum << "\n";

            sum = 0;
            for (i = 0; i < array_size_N; i++)
            {
                sum = sum + a[i][array_size_N - 1 - i];
            }
            std::cout << "Cумма элементов 2-ой диагонали равна " << sum << "\n";
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