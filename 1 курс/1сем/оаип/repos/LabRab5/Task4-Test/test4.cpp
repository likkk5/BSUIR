#include "pch.h"

int CountZeroArray(double** array, int array_size_row, int array_size_col);
double** ChangeElementsArray(double** array, int array_size_row, int array_size_col);

TEST(TestCountZeroArrayValid, CountZeroArray1)
{
    double** array;
    array = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array[ii] = new double[3];
    }
    array[0][0] = 1;
    array[0][1] = 2;
    array[0][2] = 3;
    array[1][0] = 4;
    array[1][1] = 5;
    array[1][2] = 6;

    ASSERT_EQ(CountZeroArray (array,2,3), 0);
}

TEST(TestCountZeroArrayValid, CountZeroArray2)
{
    double** array;
    array = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array[ii] = new double[3];
    }
    array[0][0] = 0;
    array[0][1] = 0;
    array[0][2] = 0;
    array[1][0] = 0;
    array[1][1] = 0;
    array[1][2] = 0;

    ASSERT_EQ(CountZeroArray(array, 2, 3), 6);
}

TEST(TestCountZeroArrayValid, CountZeroArray3)
{
    double** array;
    array = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array[ii] = new double[3];
    }
    array[0][0] = 1;
    array[0][1] = 0;
    array[0][2] = 3;
    array[1][0] = 4;
    array[1][1] = 0;
    array[1][2] = 0;

    ASSERT_EQ(CountZeroArray(array, 2, 3), 3);
}

TEST(TestChangeElementsArrayValid, ChangeElementsArray1)
{
    double** array;
    array = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array[ii] = new double[3];
    }
    array[0][0] = 1.1;
    array[0][1] = 2.1;
    array[0][2] = 3.1;
    array[1][0] = 4.1;
    array[1][1] = 5.1;
    array[1][2] = 6.1;

    double** array_new;
    array_new = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array_new[ii] = new double[3];
    }
    array_new[0][0] = 6.1;
    array_new[0][1] = 5.1;
    array_new[0][2] = 4.1;
    array_new[1][0] = 3.1;
    array_new[1][1] = 2.1;
    array_new[1][2] = 1.1;

    double** array1 = nullptr;
    array1 = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array1[ii] = new double[3];
    }
    array1 = ChangeElementsArray(array, 2, 3);
    
    for (int p = 0; p < 2; p++)
    {
        for (int q = 0; q < 3; q++)

            ASSERT_DOUBLE_EQ(array1[p][q], array_new[p][q]);
    }
}

TEST(TestChangeElementsArrayValid, ChangeElementsArray2)
{
    double** array;
    array = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array[ii] = new double[2];
    }
    array[0][0] = 1;
    array[0][1] = 2;
    array[1][0] = 3;
    array[1][1] = 4;
   

    double** array_new;
    array_new = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array_new[ii] = new double[2];
    }
    array_new[0][0] = 4;
    array_new[0][1] = 3;
    array_new[1][0] = 2;
    array_new[1][1] = 1;
    
    double** array1 = nullptr;
    array1 = new double* [2];
    for (int ii = 0;ii < 2;ii++)
    {
        array1[ii] = new double[2];
    }
    array1 = ChangeElementsArray(array, 2, 2);

    for (int p = 0; p < 2; p++)
    {
        for (int q = 0; q < 3; q++)

            ASSERT_DOUBLE_EQ(array1[p][q], array_new[p][q]);
    }
}




int CountZeroArray(double** array, int array_size_row, int array_size_col)
{
    int array_size_new = 0;

    for (int p = 0; p < array_size_row; p++)
    {
        for (int q = 0; q < array_size_col; q++)

            if (array[p][q] == 0)
            {
                array_size_new = array_size_new + 1;
                std::cout << "Нулевой элемент в " << p << " строке в " << q << " столбце." << "\n";
            }
    }
    return array_size_new;
}

double** ChangeElementsArray(double** array, int array_size_row, int array_size_col)
{
    double change;
    int p, q;
    for (p = 0; p < array_size_row / 2; p++)
    {
        for (q = 0; q < array_size_col; q++)
        {
            change = array[p][q];
            array[p][q] = array[array_size_row - 1 - p][array_size_col - 1 - q];
            array[array_size_row - 1 - p][array_size_col - 1 - q] = change;
        }
    }

    if (array_size_row % 2 != 0)
    {
        p = array_size_row / 2;
        for (q = 0; q < array_size_col / 2; q++)
        {
            change = array[p][q];
            array[p][q] = array[p][array_size_col - 1 - q];
            array[p][array_size_col - 1 - q] = change;
        }
    }

    return array;
}
