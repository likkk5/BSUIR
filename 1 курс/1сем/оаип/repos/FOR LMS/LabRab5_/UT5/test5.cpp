#include "pch.h"

double AverageElementArray(int* array, int array_size_col);

TEST(TestAverageElementArrayValid, AverageElementArray1)
{
    int array[5]{ 1,1,1,1,1 };
    ASSERT_DOUBLE_EQ(AverageElementArray(array, 5), 1);
}

TEST(TestAverageElementArrayValid, AverageElementArray2)
{
    int array[5]{1,11,13,3,9};
    ASSERT_DOUBLE_EQ(AverageElementArray(array, 5),7.4);
}

TEST(TestAverageElementArrayValid, AverageElementArray3)
{
    int array[5]{0,2,-3,4,5};
    ASSERT_DOUBLE_EQ(AverageElementArray(array, 5), 1.6 );
}

double AverageElementArray(int* array, int array_size_col)
{
    double sum = 0;
    for (int p = 0; p < array_size_col; p++)
    {
        sum = sum + (*(array + p));
    }
    return sum / array_size_col;
}
