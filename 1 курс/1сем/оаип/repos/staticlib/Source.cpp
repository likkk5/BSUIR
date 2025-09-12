#pragma once

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

                if ((check_string.length() != temp_input.length()) || (array_size < 2))
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

// Ввод элемента массива (вещественное число) и проверка на корректность ввода (вещественное число, не содержит буквы)
double InputElementArray(int p, int q, int size_row, int size_col)
{
    double ElementArray;
    std::string temp_input = "";
    int pp, k, l, m;
    
    while (true)
    {
        k = 0;
        l = 0;
        m = 0;

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

        if ((temp_input[0] == 45) && (temp_input[1] == 44))
        {
            std::cout << "Повторите ввод. Некорректное значение." << "\n";
            std::cin.clear();
        }
        else
        {
            for (pp = 0;pp < temp_input.length(); pp++)
            {
                if (((temp_input[pp] < 48) || (temp_input[pp] > 57)) && (temp_input[pp] != 44) && (temp_input[pp] != 45))
                {
                    k = k + 1;
                }
                if (temp_input[pp] == 44)
                {
                    l = l + 1;
                }
                if ((temp_input[pp] == 45) && (pp != 0))
                {
                    m = m + 1;
                }
            }

            if ((k == 0) && (l < 2) && (m == 0))
            {
                ElementArray = std::stod(temp_input);
                return ElementArray;
                break;
            }
            else
            {
                std::cout << "Повторите ввод. Некорректное значение." << "\n";
                std::cin.clear();
            }
        }
    }
}


// Ввод элементов массива (вещественные числа) и проверка на корректность ввода (вещественные числа, не содержит буквы)
double** InputArray(double** array, int array_size_row, int array_size_col)
{
    for (int pp = 0; pp < array_size_row; pp++)
    {
        for (int qq = 0; qq < array_size_col; qq++)
        {
            array[pp][qq] = InputElementArray(pp, qq, array_size_row, array_size_col);
        }
    }
    return array;
}


// Вывод массива вещественных чисел
void OutputArray(double** array, int array_size_row, int array_size_col)
{
    for (int pp = 0; pp < array_size_row; pp++)
    {
        for (int qq = 0; qq < array_size_col; qq++)
        {
            std::cout << array[pp][qq] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Определение элементов матрицы А - Task1
double** CreateNewArray(double** new_array, double** array1, double** array2, int array_size_row, int array_size_col)
{
    for (int p = 0; p < array_size_row; p++)
    {
        for (int q = 0; q < array_size_col; q++)
        {
            if (fabs(array1[p][q]) > fabs(array2[p][q]))
            {
                new_array[p][q] = array1[p][q];
            }
            else
            {
                new_array[p][q] = array2[p][q];
            }
        }
    }
    return new_array;
}
