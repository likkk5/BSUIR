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
    std::cout << "������� 2. ����� ������. ������ 253505" << '\n';
    std::cout << "������� 13. ��� ��������� ����������� ������� � �� N ���������" << '\n';
    std::cout << "            ���������, ��� ���������� �� �� ������� ���� ���� ������� a[i] <= i*i" << '\n';
    //std::cout << "����� ������. ������ 253505" << '\n' << '\n';

    int array_size_N, repeat = 1;
    int i = 0;
    bool k;
    std::string temp_input1;

    do
    {
        // ���� ����������� ����������� ������� � �������� �� ������������ ����� (����������� �����, �� 0, �� �������������, �� ������������, �� �������� �����, �� ��������� 2147483647)
        array_size_N = inputArraySize("������� ����������� ����������� ������� (����������� �����): ");

        // ��������� ������������ ������ ��� �������� A
        double* a = nullptr;
        a = new double[array_size_N];

        // ���� ��������� ������� A � �������� �� ������������ ����� (����� �����, �� �������� �����)
        std::cout << "������� �������� ������� A (������������ �����)" << "\n";
        a = inputArray(a, 1, array_size_N);

        // �����������, ������� A[i] <= i^2
        k = rec(a, 0, array_size_N - 1);
    
        std::cout << "\n" << "������� ��������� ������:" << "\n";

        std::cout << "����������� ����������� ������a: " << array_size_N << "\n" << "\n";

        std::cout << "�������� ������� A: " << "\n ";
        outputArray(a, 1, array_size_N);

        if (k == true)
        {
            std::cout << "���������� �� ������� ���� ���� ������� A[i] <= i^2." << "\n ";
        }
        else
        {
            std::cout << "�� ���������� �������� A[i] <= i^2." << "\n ";
        }

        delete[] a;
        a = nullptr;


        // ��������� ������ ���������
        std::cout << '\n' << "��� ���������� ����� ������ ������� 1 � ������ ENTER; ��� ��������� ������ - ����� ������ ������ � ������ ENTER: ";
        std::cin >> temp_input1;

        if ((temp_input1[0] == '1') && (temp_input1.length() == 1))
        {
            repeat = 1;
            while (std::cin.get() != '\n');
        }
        else
        {
            std::cout << "��������� ��������� ������." << "\n";
            repeat = 0;
        }

    } while (repeat == 1);

    FreeLibrary(load);

    return 0;
}

