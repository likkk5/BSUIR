#include <iostream>

void MaxSumSubArray(int array[], int n)
{
    long long max_sum = 0;
    long long cur_sum = 0;
    long long begin = 0;
    long long cur_begin = 0;
    long long end = 0;

    // подсчет отрицательных элементов массива
    for (int j = 0; j < n;j++)
    {
        if (array[j] < 0)
        {
            cur_sum = cur_sum + 1;
        }
    }
    //если все элементы отрицательные, то подмассив максимальной суммы - это наибольший элемент массива
    if (cur_sum == n)
    {
        max_sum = array[0];

        for (int j = 1; j < n;j++)
        {
            if (array[j] > max_sum)
            {
                max_sum = array[j];
            }
        }
        std::cout << max_sum << "\n";
    }
    else
    {
        cur_sum = 0;
        for (int j = 0; j < n;j++)
        {
            cur_sum = cur_sum + array[j];
            if (cur_sum > max_sum)
            {
                begin = cur_begin;
                end = end + 1;
                max_sum = cur_sum;
            }
            if (cur_sum < 0)
            {
                cur_sum = 0;
                cur_begin = j + 1;
                end = j + 1;
            }
        }

        if (end == n)
        {
            end = n - 1;
        }
        
        // максимальная сумма и элементы подмассива
        std::cout << max_sum << "\n";
        for (int j = begin;j <= end;j++)
        {
            std::cout << array[j] << "  ";
        }
    }
}

int main()
{
    int n, i;
    std::cin >> n;

    int* a = nullptr;
    a = new int[n];

    for (i = 0; i < n;i++)
    {
        std::cin >> a[i];
    }

    MaxSumSubArray(a, n);

    delete[] a;
    a = nullptr;

    return 0;
}


typedef int(*name)(arr, size);
name* arr = (name*)malloc(sizeof(name) * size);

void Name(int a[], int n)
{
    int n, i;
    std::cin >> n;
    int a[100];
    for (int i = 0; i < n;i++)
    {
        i *= i;
        std::cout << a[i];
    }
}

typedef int(*name)(*arr, size);


typedef void (*funct)()

int* mas = new int mas[7];

int (**name)(arr, size) = (int (**)(arr, size))malloc(sizeofint(*)(arr, size)*)

free(name);