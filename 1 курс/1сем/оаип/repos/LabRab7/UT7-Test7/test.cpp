#include "pch.h"

bool CheckBinaryBit(std::string dec_str, int kk);
std::string CreateBiDecimal(int n);

TEST(TestCreateBiDecimal, TestCreateBiDecimal1)
{
    ASSERT_EQ(CreateBiDecimal(1), "1");
}

TEST(TestCreateBiDecimal, TestCreateBiDecimal2)
{
    ASSERT_EQ(CreateBiDecimal(2), "10");
}

TEST(TestCreateBiDecimal, TestCreateBiDecimal3)
{
    ASSERT_EQ(CreateBiDecimal(10), "1100");
}

TEST(TestCreateBiDecimal, TestCreateBiDecimal4)
{
    ASSERT_EQ(CreateBiDecimal(10000), "11001000000011100110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
}

TEST(TestCreateBiDecimal, TestCreateBiDecimal5)
{
    ASSERT_EQ(CreateBiDecimal(15), "10101");
}

TEST(TestCreateBiDecimal, TestCreateBiDecimal6)
{
    ASSERT_EQ(CreateBiDecimal(3000), "10110000000010111000100000001010110001111001000000000000000000000000");
}



#include <iostream>
#include <string>

// проверка: kk-ого бит в бинарном представлении дес€тичной строки = 0
bool CheckBinaryBit(std::string dec_str, int kk)
{
    bool check = false;
    std::string temp_str, bin_str = "";
    int i = 0, j = 0, q;
    int p = 0;

    for (q = 1;q <= kk;q++)
    {
        // деление на 2
        p = 0;
        j = 0;
        i = 0;
        while (i < dec_str.length() - 1)
        {
            p = p * 10 + (dec_str[i] - 48);
            if (p == 1)
            {
                p = p * 10 + (dec_str[i + 1] - 48);
                if (i != 0)
                {
                    j = j + 1;
                }
                i = i + 1;
            }

            if (j == 1)
            {
                temp_str += '0';
                j = 0;
            }

            temp_str += (p / 2 + 48);
            p = p % 2;


            i = i + 1;

        }

        if (i == dec_str.length() - 1)
        {
            p = p * 10 + (dec_str[i] - 48);
            temp_str += (p / 2 + 48);
            p = p % 2;
        }

        bin_str += (p + 48); // строка двоичного представлени€ в обратном пор€дке
        //std::cout << "bin_str =" << bin_str << "\n";

        dec_str = "";
        dec_str = temp_str;
        //std::cout << "dec_str =" << dec_str << "\n";
        temp_str = "";
        //std::cout << "temp_str =" << temp_str << "\n";
        if (dec_str == "")
        {
            break;
        }
    }

    //std::cout << "bin_str[" << bin_str.length() - 1 << "] = " << bin_str[bin_str.length() - 1] << "\n";

    if (bin_str.length() < kk)
    {
        for (q = 0;q < kk - bin_str.length();q++)
        {
            bin_str += '0';
        }
    }
    //std::cout << "bin_str =" << bin_str << "\n";
    //std::cout << "bin_str.length() = " << bin_str.length() << "\n";

    if (bin_str[bin_str.length() - 1] == '0')
    {
        check = true;
    }

    return check;
}

std::string CreateBiDecimal(int n)
{
    int i, j, l, k = 2, Num_A = 0, Num_C = 0, count = 1;
    bool check;
    std::string bi_dec_str;
    int Max_N = 10000;

    std::string* A = nullptr;
    A = new std::string[Max_N];

    std::string* B = nullptr;
    B = new std::string[Max_N];

    std::string* C = nullptr;
    C = new std::string[2 * Max_N];

    if ((n >= 1) && (n <= Max_N))
    {
        if (n == 1)
        {
            bi_dec_str = "1";
        }

        C[0] = '0';
        C[1] = '1';
        Num_C = 2;

        while (count < n)
        {
            // элементы ј = —(сформирован на предыдущем шаге), если k-ый бит в бинарном представлении j-го элемента = 0
            i = 0;
            for (j = 0; j < Num_C; j++)
            {
                //std::cout << "C[" << j << "] = " << C[j] << "\n";
                check = CheckBinaryBit(C[j], k); // проверка: kk-ого бит в бинарном представлении дес€тичной строки = 0
                if (check)
                {
                    //std::cout << "A[" << i << "] = " << A[i] << "\n";
                    A[i] = "";
                    if (C[j].length() < C[Num_C - 1].length())
                    {
                        for (l = 0;l < (C[Num_C - 1].length() - C[j].length());l++)
                        {
                            A[i] = A[i] + '0';
                        }
                    }
                    A[i] += C[j];
                    //std::cout << "A[" << i << "] = " << A[i] << "\n";
                    i++;
                }
            }
            //std::cout << "\n";
            Num_A = i;

            //формируем новый массив —: перва€ часть - элементы массива ј
            for (j = 0; j < Num_A; j++)
            {
                C[j] = "";
                C[j] = A[j];
            }

            // формируем новый массив —: втора€ часть - элементы массива B
            // элемент массива B - двудес€тичное число
            for (j = 0; j < Num_A; j++)
            {
                B[j] = '1' + A[j];
                C[Num_A + j] = "";
                C[Num_A + j] = B[j];
                //std::cout << "B[" << j << "] = " << B[j] << "\n";
                count++;
                //std::cout << count<< "\n";
                if (count == n)
                {
                    break;
                }
            }
            if (count == n)
            {
                bi_dec_str = B[j];
                break;
            }
            else
            {
                k++;
                Num_C = 2 * Num_A;
            }
        }
    }

    delete[] A;
    delete[] B;
    delete[] C;

    return bi_dec_str;
}