#include "pch.h"

long long MultiplyElementArray(int* array, int array_size_col);

TEST(TestMultiplyValid, Multiply1)
{
    int array[5]{2,4,6,8,10};
    ASSERT_EQ(MultiplyElementArray(array, 5), 3840);
}

TEST(TestMultiplyValid, MultiplyZero)
{
    int array[5]{ 2,4,6,8,0 };
    ASSERT_EQ(MultiplyElementArray(array, 5), 0);
}

TEST(TestMultiplyValid, MultiplyNegative)
{
    int array[5]{ 1,1,-10,2,3 };
    ASSERT_EQ(MultiplyElementArray(array, 5), -60);
}

long long MultiplyElementArray(int* array, int array_size_col)
{
    long long m = 1;
    for (int p = 0; p < array_size_col; p++)
    {
        m = m * (*(array + p));
    }
    return m;
}
