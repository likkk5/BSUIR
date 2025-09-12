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

// Ввод элемента массива (вещественное число) и проверка на корректность ввода (вещественное число, не содержит буквы)
double InputElementArray(int p, int q, int size_row, int size_col)
{
    double ElementArray;
    std::string temp_input="";
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

// Определение количества и индексов нулевых элементов матрицы А - Task4
int CountZeroArray(double** array, int array_size_row, int array_size_col)
{
    int array_size_new = 0;

    for (int p = 0; p < array_size_row; p++)
    {
        for (int q = 0; q < array_size_col; q++)

            if (array[p][q] == 0)
            {
                array_size_new = array_size_new + 1;
                std::cout << "Нулевой элемент в " << p << " строке в " << q << " столбце." << "\n";
            }
    }
    return array_size_new;
}

// Перестановка элементов матрицы А в обратном порядке  - Task4
double** ChangeElementsArray(double** array, int array_size_row, int array_size_col)
{
    double change;
    int p, q;
    for (p = 0; p < array_size_row/2; p++)
    {
        for (q = 0; q < array_size_col; q++)
        { 
            change = array[p][q];
            array[p][q] = array[array_size_row - 1 - p][array_size_col - 1 - q];
            array[array_size_row - 1 - p][array_size_col - 1 - q] = change;
        }
    }

    if (array_size_row % 2 != 0)
    {
        p = array_size_row / 2;
        for (q = 0; q < array_size_col/2; q++)
        {
            change = array[p][q];
            array[p][q] = array[p][array_size_col - 1 - q];
            array[p][array_size_col - 1 - q] = change;
        }
    }

    return array;
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 4. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Дан двумерный динамический массив вещественных чисел А." << "\n";
    std::cout << "Определить, встречаются ли среди них элементы с нулевым значением." << "\n";
    std::cout << "Если встречаются такие элементы, то определить их индексы и общее количество." << "\n";
    std::cout << "Переставить элементы этого массива в обратном порядке и вывести на экран." << "\n" << "\n";
    //std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    int array_size_N = 0, array_size_K = 0, ii, array_size_M = 0, repeat = 1;
    std::string temp_input1;

    do
    {
        array_size_M = 0;

        // Ввод размерность двумерного массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        array_size_N = InputArraySize("Введите количество строк массива (натуральное число): ");
        array_size_K = InputArraySize("Введите количество столбцов массива (натуральное число): ");

        // Выделение динамической памяти для массива A
        double** a=nullptr;
        a = new double* [array_size_N];
        for (ii = 0;ii < array_size_N;ii++)
        {
            a[ii] = new double[array_size_K];
        }

        // Ввод элементов массива A и проверка на корректность ввода (вещественные числа, не содержит буквы)
        std::cout << "Введите элементы матрицы A (вещественные числа)" << "\n";
        a = InputArray(a, array_size_N, array_size_K);

        std::cout << "\n" << "Введены следующие данные:" << "\n";

        std::cout << "Размерность массива А: " << array_size_N << "x" << array_size_K << "\n" << "\n";

        std::cout << "Элементы массива A: " << "\n ";
        OutputArray(a, array_size_N, array_size_K);

        // Определение количества и индексов нулевых элементов матрицы А
        array_size_M = CountZeroArray(a, array_size_N, array_size_K);

        if (array_size_M != 0)
        {
            std::cout << "Всего нулевых элементов в матрице А: " << array_size_M << "\n" << "\n";
        }
        else 
        {
            std::cout << "В матрице А нет нулевых элементов." << "\n" << "\n";
        }

        // Перестановка элементов матрицы А в обратном порядке
        a = ChangeElementsArray(a, array_size_N, array_size_K);
      
        std::cout << "Элементы массива А в обратном порядке: " << "\n ";
        OutputArray(a, array_size_N, array_size_K);
                  
        
        // Освобождение памяти
        /*for (ii = 0;ii < array_size_K;ii++)
        {
            delete a[ii];
        }*/
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
