#include <iostream>
#include <string>

int InputArraySize(std::string);
double InputElementArray(int, int, int, int);
double** InputArray(double**, int, int);
int InputIntElementArray(int, int, int, int);
void OutputArray(double**, int, int);
double** CreateNewArray(double**, double**, double**, int, int);

int main()
    {
        setlocale(LC_ALL, "rus");
        std::cout << "Задание 1. Лишик Ксения. Группа 253505" << '\n';
        std::cout << "Вариант 13. Составить программу вычисления элементов двумерного динамического массива-матрицы А размерности nxn: " << "\n";
        std::cout << "            a[i][j] = b[i][j], если |b[i][j]| > |c[i][j]|;" << "\n";
        std::cout << "            a[i][j] = c[i][j], если |b[i][j]| <= |c[i][j]|," << "\n";
        std::cout << "            где i = 0, 1, ..., n - 1; j = 0, 1, ..., n - 1." << "\n" << "\n";
        //std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

        int array_size_N = 0, ii, repeat = 1;
        std::string temp_input1;
        
        do
        {
            // Ввод размерность двумерного массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
            array_size_N = InputArraySize("Введите размерность двумерного массива (натуральное число): ");

            // Выделение динамической памяти для массивов A, B и C
            double** a = nullptr;
            a = new double* [array_size_N];
            for (ii = 0;ii < array_size_N;ii++)
            {
                a[ii] = new double[array_size_N];
            }

            double** b = nullptr;
            b = new double* [array_size_N];
            for (ii = 0;ii < array_size_N;ii++)
            {
                b[ii] = new double[array_size_N];
            }

            double** c = nullptr;
            c = new double* [array_size_N];
            for (ii = 0;ii < array_size_N;ii++)
            {
                c[ii] = new double[array_size_N];
            }

            // Ввод элементов массива B и проверка на корректность ввода (вещественные числа, не содержит буквы)
            std::cout << "Введите элементы матрицы B (вещественные числа)" << "\n";
            b = InputArray(b, array_size_N, array_size_N);

            // Ввод элементов массива C и проверка на корректность ввода (вещественные числа, не содержит буквы)
            std::cout << "Введите элементы матрицы C (вещественные числа)" << "\n";
            c = InputArray(c, array_size_N, array_size_N);

            // Определение элементов матрицы А
            a = CreateNewArray(a, b, c, array_size_N, array_size_N);

            std::cout << "\n" << "Введены следующие данные:" << "\n";

            std::cout << "Размерность массивов " << array_size_N << "x" << array_size_N << "\n" << "\n";

            std::cout << "Элементы массива B: " << "\n ";
            OutputArray(b, array_size_N, array_size_N);

            std::cout << "Элементы массива C: " << "\n ";
            OutputArray(c, array_size_N, array_size_N);

            std::cout << "Полученные элементы массива A: " << "\n ";
            OutputArray(a, array_size_N, array_size_N);

            delete[] a;
            a = nullptr;

            delete[] b;
            b = nullptr;

            delete[] c;
            c = nullptr;

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

