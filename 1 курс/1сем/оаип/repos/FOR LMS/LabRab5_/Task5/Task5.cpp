#include <iostream>
#include <string>


// Ввод размерности (количество строк, количества столбцов) массива
// и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
int InputArraySize(std::string input)
{
    int array_size;
    std::string temp_input, check_string;

    while (true)
    {
        std::cout << input;
        getline(std::cin, temp_input);

        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
        {
            // <=2147483647
            if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
            {
                array_size = std::stoi(temp_input);
                check_string = std::to_string(array_size);

                if ((check_string.length() != temp_input.length()) || (array_size < 1))
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                }
                else
                {
                    return array_size;
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
}

// Ввод элемента массива (целое число) и проверка на корректность ввода (целое число, не содержит буквы)
int InputIntElementArray(int p, int q, int size_row, int size_col)
{
    int ElementArray;
    std::string temp_input, check_string;

    while (true)
    {
        if (size_row == 1)
        {
            std::cout << "Введите [" << q << "] = ";
        }
        if (size_col == 1)
        {
            std::cout << "Введите [" << p << "] = ";
        }
        if ((size_row > 1) && (size_col > 1))
        {
            std::cout << "Введите [" << p << "][" << q << "] = ";
        }

        getline(std::cin, temp_input);
        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
        {
            // <=2147483647
            if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
            {
                ElementArray = std::stoi(temp_input);
                check_string = std::to_string(ElementArray);

                if (check_string.length() != temp_input.length())
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                }
                else
                {
                    return ElementArray;
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
                    ElementArray = std::stoi(temp_input);
                    check_string = std::to_string(ElementArray);

                    if (check_string.length() != temp_input.length())
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                    }
                    else
                    {
                        return ElementArray;
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

// Ввод элементов массива (целые числа) и проверка на корректность ввода (целые числа, не содержит буквы)
int* InputArray(int* array, int array_size_row, int array_size_col)
{
    for (int pp = 0; pp < array_size_row; pp++)
    {
        for (int qq = 0; qq < array_size_col; qq++)
        {
            *(array + pp * array_size_col + qq) = InputIntElementArray(pp, qq, array_size_row, array_size_col);
        }
    }
    return array;
}

// Вывод массива целых чисел
void OutputArray(int* array, int array_size_row, int array_size_col)
{
    for (int pp = 0; pp < array_size_row; pp++)
    {
        for (int qq = 0; qq < array_size_col; qq++)
        {
            std::cout << *(array + pp * array_size_col + qq) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Определение количества элементов матрицы B - Task5
int NewSizeArray5(int* array, int array_size_row, int array_size_col)
{
    int array_size_new = 0;

    for (int p = 0; p < array_size_row; p++)
    {
        for (int q = 0; q < array_size_col; q++)
        {
            if ((*(array + p * array_size_col + q) % 2 != 0) && (q % 2 == 0))
            {
                array_size_new = array_size_new + 1;
            }
        }
    }
    return array_size_new;
}

// Определение элементов матрицы B - Task5
int* CreateNewArray5(int* array, int array_size_row, int array_size_col, int* new_array)
{
    int l = 0;
    for (int p = 0; p < array_size_row; p++)
    {
        for (int q = 0; q < array_size_col; q++)
        {
            if ((*(array + p * array_size_col + q) % 2 != 0) && (q % 2 == 0))
            {
                *(new_array + l) = *(array + p * array_size_col + q);
                l = l + 1;
            }
        }
    }
    return new_array;
}

// Среднее арифметическое элементов массива B  - Task5
double AverageElementArray(int* array, int array_size_col)
{
    double sum = 0;
    for (int p = 0; p < array_size_col; p++)
    {
        sum = sum + (*(array + p));
    }
    return sum / array_size_col;
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 5. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Дан двумерный динамический массив целых чисел А." << "\n";
    std::cout << "Создать динамический массив из элементов, расположенных в четных столбцах данного массива и имеющих нечетное значение." << "\n";
    std::cout << "Вычислить среднее арифметическое элементов динамического массива. Созданный массив и результат вывести на экран." << "\n" << "\n";
    //std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    int array_size_N = 0, array_size_K = 0, array_size_M = 0, repeat = 1;
    double average_sum = 0;
    std::string temp_input1;

    do
    {
        average_sum = 0;
        array_size_M = 0;
        
        // Ввод размерность двумерного массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        array_size_N = InputArraySize("Введите количество строк массива (натуральное число): ");
        array_size_K = InputArraySize("Введите количество столбцов массива (натуральное число): ");

        // Выделение динамической памяти для массива A
        int* a = nullptr;
        a = new int[array_size_N * array_size_K];

        // Ввод элементов массива A и проверка на корректность ввода (целые числа, не содержит буквы)
        std::cout << "Введите элементы матрицы A (целые числа)" << "\n";
        a = InputArray(a, array_size_N, array_size_K);

        std::cout << "\n" << "Введены следующие данные:" << "\n";

        std::cout << "Размерность массива А: " << array_size_N << "x" << array_size_K << "\n" << "\n";

        std::cout << "Элементы массива A: " << "\n ";
        OutputArray(a, array_size_N, array_size_K);

        // Определение количества элементов матрицы B
        array_size_M = NewSizeArray5(a, array_size_N, array_size_K);

        if ( array_size_M != 0)
        {
            // Выделение динамической памяти для массива B
            int* b = nullptr;
            b = new int[array_size_M];

            // Определение элементов матрицы B
            b = CreateNewArray5(a, array_size_N, array_size_K, b);

            // Среднее арифметическое элементов массива B
            average_sum = AverageElementArray(b, array_size_M);
                                    
            std::cout << "Размерность массива B: " << array_size_M << "\n";

            std::cout << "Элементы массива B: ";
            OutputArray(b, 1, array_size_M);

            std::cout << "Среднее арифметическое элементов массива B: " << average_sum << "\n ";

            delete[] b;
            b = nullptr;
        }
        else
        {
            std::cout << "В массиве А в четных столбцах нет элементов, имеющих нечетное значение. " << "\n ";
        }

        delete[] a;
        a = nullptr;

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

