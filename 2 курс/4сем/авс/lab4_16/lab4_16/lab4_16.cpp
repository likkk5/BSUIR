
#include <iostream>

int main()
{
    const int size = 8;
    __int8 B[8] = { -9, 10, 11, 12, 13, 5, 6, 8 };
    __int8 A[8] = { 1, 2, 3, 4, 5, 6, 7, 16 };
    __int8 C[8] = { 17,  1, 19, 20, 21, 22, 23, 24 };
    __int16 D[8] = { 25, 2, 7, 8, 10, 6, 11, 12 };
    __int16 F[8] = { 0 };

    __asm
    {
        xorpd xmm0, xmm0
        xorpd xmm1, xmm1
        xorpd xmm2, xmm2
        xorpd xmm3, xmm3
        xorpd xmm4, xmm4
        xorpd xmm5, xmm5
        xorpd xmm6, xmm6
        xorpd xmm7, xmm7

        movupd xmm3, [A]
        movupd xmm4, [B]
        movupd xmm5, [C]
        movupd xmm6, [D]

        //распаковка
        punpcklbw xmm0, xmm3
        punpcklbw xmm1, xmm4
        punpcklbw xmm2, xmm5

        psrl xmm0, 8
        psrl xmm1, 8
        psrl xmm2, 8

        pmullw xmm0, xmm1
        psubq xmm2, xmm6
        paddq xmm0, xmm2

        //psubq xmm0, xmm1 //A - B
        //pmullw xmm2, xmm6 //C * D
        //paddq xmm0, xmm2 //(A - B) + (C * D)
        movupd[F], xmm0

    }
    std::cout << "Результаты:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << "F[" << i << "]: " << F[i] << '\n';
    }
    std::cout << "Верные результаты:" << '\n';
    for (int i = 0; i < size; i++)
    {
        std::cout << (A[i] * B[i]) + C[i] - D[i] << '\n';
    }

}
