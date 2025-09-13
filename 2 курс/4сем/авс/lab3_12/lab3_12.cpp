#include <iostream>
#include "conio.h"

int main()
{
    // F[i] = (A[i] - B[i]) * (C[i] + D[i]), i = 1...8
    // Объявление и инициализация массивов
    __int8 A[8] = { 1, 2, 3, 4, 5, 6, 7, 16 };
    __int8 B[8] ={ 9, 10, 11, 12, 13, 14, 15, 8 };
    __int8 C[8] = { 17, 18, 19, 20, 21, 22, 23, 24 };
    __int16 D[8] = { 25, 2, 7, 8, 10, 6, 11, 12 };

    __int16 F[8] = { 0 }; // Инициализация массива F

    // Вставка ассемблерного кода
    __asm {
        // Загрузка данных из массивов в регистры MMX
        lea eax, A
        lea ebx, B
        lea ecx, C
        lea edx, D
        movq mm4, [eax]
        movq mm0, mm4
        movq mm5, [ebx]
        movq mm1, mm5
        movq mm6, [ecx]
        movq mm2, mm6
        movq mm7, [edx]
        movq mm3, mm7
        //movq mm0, [A] // Загрузка значений из массива A в mm0
        //movq mm1, [B] // Загрузка значений из массива B в mm1
        //movq mm2, [C] // Загрузка значений из массива C в mm2
        //movq mm3, [D] // Загрузка значений из массива D в mm3

        pxor mm4, mm4
        pxor mm5, mm5

        pcmpgtb mm4, mm0
        pcmpgtb mm5, mm1 //cmp with zero

        pxor mm4, mm4
        pxor mm5, mm5

        pcmpgtb mm4, mm2
        pcmpgtb mm5, mm3 //cmp with zero

        // Распаковка массивов 64 битный регистр 8 байт. групппировать данные с которыми хотим взаимодейстовать
        punpcklbw mm4, mm0; // Распаковка нижних 4 байт из A в mm4 младщие
        punpckhbw mm5, mm0; // Распаковка верхних 4 байт из A в mm5

        punpcklbw mm6, mm1; // Распаковка нижних 4 байт из B в mm6
        punpckhbw mm7, mm1; // Распаковка верхних 4 байт из B в mm7

        // Обнуление регистров
        pxor mm0, mm0 // Обнуление mm0
        pxor mm1, mm1 // Обнуление mm1                                            

        // Продолжение распаковки
        punpcklbw mm0, mm2; // Распаковка нижних 4 байт из C в mm0
        punpckhbw mm1, mm2; // Распаковка верхних 4 байт из C в mm1

        pxor mm2, mm2 // Обнуление mm2

        movq mm2, [D + 8] // Загрузка значений из массива D

            // Сдвиги
            psrlw mm0, 8 // Сдвиг вправо на 8 бит в mm0
            psrlw mm1, 8 // Сдвиг вправо на 8 бит в mm1
            psrlw mm6, 8 // Сдвиг вправо на 8 бит в mm6
            psrlw mm4, 8 // Сдвиг вправо на 8 бит в mm4
            psrlw mm7, 8 // Сдвиг вправо на 8 бит в mm4
            psrlw mm5, 8 // Сдвиг вправо на 8 бит в mm4

            // Вычисления
            psubw mm4, mm6
            paddsw mm0, mm3

            pmullw mm4, mm0

            movq[F], mm4 // Сохранение значений из mm6 в массив F

            // Продолжение вычислений   

            psubw mm5, mm7

            paddsw mm1, mm2

            pmullw mm1, mm5

            movq[F + 8], mm1 // Сохранение значений из mm1 в массив F
    }

    // Вывод результатов вычислений
    std::cout << "Result of expression F[i]: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << "F[" << i << "]: " << F[i] << '\n';
    }
    std::cout << std::endl;

    _getch(); // Ожидание нажатия клавиши
    return 0;
}