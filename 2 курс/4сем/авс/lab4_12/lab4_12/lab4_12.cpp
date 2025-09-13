#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int size = 8;
    //объявление и инициализация массивов
    // F[i] = (A[i] - B[i]) * (C[i] + D[i]), i = 1...8
    __int8 A[8] = { 9, 10, 11, 12, 13, 15, 16, 8 };
    __int8 B[8] = { 1, 2, 3, 4, 5, 6, 7, 16 };
    __int8 C[8] = { 17, 18, 19, 20, 21, 22, 23, 24 };
    __int16 D[8] = { 25, 2, 7, 8, 10, 6, 11, 12 };
    __int16 F[8] = { 0 };

    __asm
    {
        //инициализируем восемь регистров XMM0-XMM7 нулями
        xorpd xmm0, xmm0
        xorpd xmm1, xmm1
        xorpd xmm2, xmm2
        xorpd xmm3, xmm3
        xorpd xmm4, xmm4
        xorpd xmm5, xmm5
        xorpd xmm6, xmm6
        xorpd xmm7, xmm7

        //занестли данные массивов в регистры SSE/SSE2
        movupd xmm3, [A]
        movupd xmm4, [B]
        movupd xmm5, [C]
        movupd xmm6, [D]

        //распаковка байт регистров SSE/SSE2, в которых хранятся массивы, для работы с группой данных, для приведения массивов к 16ти битнымы
        punpcklbw xmm0, xmm3
        punpcklbw xmm1, xmm4
        punpcklbw xmm2, xmm5

        //команды сдвига, для реализации правильных вычислений 
        psrl xmm0, 8
        psrl xmm1, 8
        psrl xmm2, 8

        //арифметические операции
        psubq xmm0, xmm1 //A - B
        paddq xmm2, xmm6 //C + D
        pmullw xmm0, xmm2 //(A - B) * (C + D)
        movupd[F], xmm0 //сохраняем результат в массив F

    }
    std::cout << "Результаты:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << "F[" << i << "]: " << F[i] << '\n';
    }
    //проверена с использованием аналогичных операций на языке С++
    std::cout << "Верные результаты:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << (A[i] - B[i]) * (C[i] + D[i]) << '\n';
    }

}
