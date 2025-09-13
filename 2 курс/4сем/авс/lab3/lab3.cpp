#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int size = 8;
    __int8 A[8] = { 1,2,3,4,5,6,7,8 };
    __int8 B[8] = { 7, 2, 3, 9, 1, 2, 3, 3 };
    __int8 C[8] = { 7, 3, 5, 9, 4, 6, 7, 1 };
    __int16 D[8] = { 21, 13, 4, 2, 5, 8, 2, 2 };
    __int16 F[8] = { 0 };
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

        // C * D
        lea eax, C

        movq mm2, [eax]
        movq mm3, mm2

        pxor mm6, mm6
        pxor mm7, mm7

        pcmpgtb mm6, mm3 //сравниваем с 0

        punpcklbw mm2, mm6 //младший C
        punpckhbw mm3, mm7 //старший C

        lea ebx, D

        movq mm4, [ebx] //младшая D
        movq mm5, [ebx + 8] // старшая D
        pxor mm6, mm6
        pxor mm7, mm7

        pcmpgtw mm6, mm4
        pcmpgtw mm7, mm5



        //psrlw mm2, 8
        //psrlw mm3, 8



        movq mm6, mm2 //младшая C
        pmullw mm6, mm4 //нижняя C * нижняя D
        pmulhw mm2, mm4

        //psllw mm2, 12
        //psrlw mm6, 4

        paddsw mm2, mm6

        /*psrlw mm2, 4*/
        pxor mm6, mm6

        //старшие
        movq mm4, mm3
        pmullw mm3, mm5
        pmulhw mm4, mm5

        //psllw mm4, 12
        //psrlw mm3, 4

        paddsw mm4, mm3
        /*       psrlw mm4, 4*/

               //movq[F], mm2
               //movq[F+8], mm4

               paddsw mm0, mm2
               paddsw mm1, mm4
               movq[F], mm0
               movq[F + 8], mm1


               //lea ecx, C
               //lea edx, D
               //movq mm2, [ecx]
               //movq mm3, [edx]
               //movq mm4, mm2
               //movq mm5, mm3
               //pxor mm6, mm6
               //pxor mm7, mm7

               //pcmpgtb mm6, mm4
               //pcmpgtb mm7, mm5 //cmp with zero

               //punpcklbw mm2, mm6 //младшие
               //punpcklbw mm3, mm7
               //punpckhbw mm4, mm6 //старшие
               //punpckhbw mm5, mm7

               //pmullw mm2, mm3 //умножение младших
               //pmullw mm4, mm5
               //movq mm3, mm4 //результаты в mm2 и mm3  C*D

               ////F = A-B + C*D
               //paddw mm1, mm3 //сложение A-B и C*D
               //paddw mm0, mm2
               //movq F, mm0 //сохранение результата в массив F
               //movq F + 8, mm1

               //emms //очистка MMX-регистров

    }
    std::cout << "Результаты:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << "F[" << i << "]: " << F[i] << '\n';
    }
}


