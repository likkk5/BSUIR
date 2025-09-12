#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

int main()
{
    HINSTANCE load;
    load = LoadLibrary(L"Dll1.dll");

    setlocale(LC_ALL, "rus");
    typedef int(__stdcall* inputArraySizeFn)(std::string);
   // inputArraySizeFn inputArraySize;
    inputArraySizeFn inputArraySize  = (inputArraySizeFn)GetProcAddress(load, "inputArraySize");

    
    typedef double(__stdcall *inputElementArrayFn)(int, int, int, int);
    inputElementArrayFn inputElementArray;
    inputElementArray = (inputElementArrayFn)GetProcAddress(load, "inputElementArray");

    typedef double* (__stdcall *inputArrayFn)(double*, int , int);
    inputArrayFn inputArray;
    inputArray = (inputArrayFn)GetProcAddress(load, "inputArray");

    typedef void (__stdcall *outputArrayFn)(double* , int , int);
    outputArrayFn outputArray;
    outputArray = (outputArrayFn)GetProcAddress(load, "outputArray");

   typedef bool(__stdcall* recFn)(double*, int, int);
    recFn rec;
    rec = (recFn)GetProcAddress(load, "rec");

   /* typedef bool (*RecursiveSin)(std::string);
    RecursiveSin rec;
    rec = (RecursiveSin)GetProcAddress(load, "rec");
    */
    //int n;
    /*typedef int(*inputArraySize)(std::string);
    inputArraySize* arr = (inputArraySize*)malloc(sizeof(std::string)*10);*/
    std::cout << "Задание 2. Лишик Ксения. Группа 253505" << '\n';
    std::cout << "Вариант 13. Для заданного одномерного массива А из N элементов" << '\n';
    std::cout << "            проверить, что существует ли по крайней мере один элемент a[i] <= i*i" << '\n';
    //std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    int array_size_N, repeat = 1;
    int i = 0;
    bool k;
    std::string temp_input1;

    do
    {
        // Ввод размерность одномерного массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        array_size_N = inputArraySize("Введите размерность одномерного массива (натуральное число): ");

        // Выделение динамической памяти для массивов A
        double* a = nullptr;
        a = new double[array_size_N];

        // Ввод элементов массива A и проверка на корректность ввода (целые числа, не содержит буквы)
        std::cout << "Введите элементы матрицы A (вещественные числа)" << "\n";
        a = inputArray(a, 1, array_size_N);

        // Определение, сколько A[i] <= i^2
        k = rec(a, 0, array_size_N - 1);
    
        std::cout << "\n" << "Введены следующие данные:" << "\n";

        std::cout << "Размерность одномерного массивa: " << array_size_N << "\n" << "\n";

        std::cout << "Элементы массива A: " << "\n ";
        outputArray(a, 1, array_size_N);

        if (k == true)
        {
            std::cout << "Существует по крайней мере один элемент A[i] <= i^2." << "\n ";
        }
        else
        {
            std::cout << "Не существуют элементы A[i] <= i^2." << "\n ";
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

    FreeLibrary(load);

    return 0;
}

