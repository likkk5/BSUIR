#pragma once
#include "pch.h"
#include "framework.h"
#include <iostream>
#include <string>
#include <stdio.h>


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

// Ввод элемента массива (вещественное число) и проверка на корректность ввода (вещественное число, не содержит буквы)
double InputElementArray(int p, int q, int size_row, int size_col)
{
    double ElementArray;
    std::string temp_input = ""; // check_string;
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
       
        if ((temp_input[0] == 45) && (temp_input[1] == 46))
        {
            std::cout << "Повторите ввод. Некорректное значение." << "\n";
            std::cin.clear();
        }
        else
        {
            for (pp = 0;pp < temp_input.length(); pp++)
            {
                if (((temp_input[pp] < 48) || (temp_input[pp] > 57)) && (temp_input[pp] != 46) && (temp_input[pp] != 45))
                {
                    k = k + 1;
                }
                if (temp_input[pp] == 46)
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
double* InputArray(double* array, int array_size_row, int array_size_col)
{
    for (int pp = 0; pp < array_size_row; pp++)
    {
        for (int qq = 0; qq < array_size_col; qq++)
        {
            *(array + pp * array_size_col + qq) = InputElementArray(pp, qq, array_size_row, array_size_col);
        }
    }
    return array;
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

// Вывод массива вещественных чисел
void OutputArray(double* array, int array_size_row, int array_size_col)
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

// Определение элементов матрицы А - Task1
double* CreateNewArray(double* new_array, double* array1, double* array2, int array_size_row, int array_size_col)
{
    for (int p = 0; p < array_size_row; p++)
    {
        for (int q = 0; q < array_size_col; q++)
        {
            if (fabs(*(array1 + p * array_size_col + q)) > fabs(*(array2 + p * array_size_col + q)))
            {
                *(new_array + p * array_size_col + q) = *(array1 + p * array_size_col + q);
            }
            else
            {
                *(new_array + p * array_size_col + q) = *(array2 + p * array_size_col + q);
            }
        }
    }
    return new_array;
}


/* для Task3-Task5 дополнительные функции

// Определение количества элементов матрицы B - Task3
int NewSizeArray(int* array, int array_size_min, int array_size_col)
{
    int array_size_new = 0;

    for (int p = 0; p < array_size_min; p++)
    {
        if (*(array + p * array_size_col + p) % 2 == 0)
        {
            array_size_new = array_size_new + 1;
        }
    }
    return array_size_new;
}

// Определение элементов матрицы B - Task3
int* CreateNewArray(int* array, int array_size_min, int array_size_col, int* new_array)
{
    int l = 0;
    for (int p = 0; p < array_size_min; p++)
    {
        if (*(array + p * array_size_col + p) % 2 == 0)
        {
            *(new_array + l) = *(array + p * array_size_col + p);
            l = l + 1;
        }
    }
    return new_array;
}

// Произведение элементов массива B  - Task3
long long MultiplyElementArray(int* array, int array_size_col)
{
    long long m = 1;
    for (int p = 0; p < array_size_col; p++)
    {
        m = m * (*(array + p));
    }
    return m;
}
    
// Определение количества и индексов нулевых элементов матрицы А - Task4
int CountZeroArray(double* array, int array_size_row, int array_size_col)
{
    int array_size_new = 0;

    for (int p = 0; p < array_size_row; p++)
    {
        for (int q = 0; q < array_size_col; q++)

        if (*(array + p * array_size_col + q) == 0)
        {
            array_size_new = array_size_new + 1;
            std::cout << "Нулевой элемент в " << p << " строке в " << q << " столбце." << "\n";
        }
    }
    return array_size_new;
}

// Перестановка элементов матрицы А в обратном порядке  - Task4
double* ChangeElementsArray(double* array, int array_size)
{
    double change;
    for (int pp = 0; pp < array_size/2; pp++)
    {
        change = *(array + pp);
        *(array + pp) = *(array + array_size - 1 - pp);
        *(array + array_size - 1 - pp) = change;
    }
    return array;
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
*/