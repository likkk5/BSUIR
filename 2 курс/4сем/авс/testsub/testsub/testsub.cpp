#include <iostream>
#include <windows.h>

int main()
{
    // F[i] = (A[i] - B[i]) * (C[i] + D[i]), i = 1...8
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int size = 8;
    __int8 A[8] = { 1,2,3,4,5,6,7,8 };
    __int8 B[8] = { 7, 2, 3, 9, 1, 2, 3, 3 };
    __int8 C[8] = { 7, 3, 5, 9, 4, 6, 7, 1 };
    __int16 D[8] = { 21, 13, 4, 2, 5, 8, 2, 2 };
    __int16 F[8] = { 0 };
    __int16 result[8] = { 0 };
    __int16 sum_result[8] = { 0 };

    __asm
    {
        //A-B
        lea eax, A
        lea ebx, B
        movq mm0, [eax]
        movq mm1, [ebx]
        movq mm2, mm0
        movq mm3, mm1
        pxor mm4, mm4
        pxor mm5, mm5

        pcmpgtb mm4, mm2
        pcmpgtb mm5, mm3 //cmp with zero

        punpcklbw mm0, mm4 //младшие
        punpcklbw mm1, mm5
        punpckhbw mm2, mm4 //старшие
        punpckhbw mm3, mm5

        psubw mm0, mm1 //вычитание младших
        psubw mm2, mm3
        movq mm1, mm2 //результаты в mm0 и mm1  A-B

        // Сохранение результатов в памяти
        movq[result], mm0
        movq[result + 8], mm1

    }

    std::cout << "Результаты A - B:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << "A-B[" << i << "]: " << result[i] << '\n';
    }

    std::cout << "\nРезультаты C + D:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << "C+D[" << i << "]: " << sum_result[i] << '\n';
    }

    std::cout << "Результаты:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << "F[" << i << "]: " << F[i] << '\n';
    }

    return 0;
}

