#include <iostream>

//Если элементы строки находятся в убывающем порядке,то порядок элементов в строке меняется на возрастающий. если все элементы убывают.

int** Input(int** a, int nn, int mm)
{
    for (int i = 0; i < nn; i++)
    {
        for (int j = 0; j < mm;j++)
        {
            std::cin >> a[i][j];
        }
    }
    return a;
}

void Print(int** a, int nn, int mm)
{
    for (int i = 0; i < nn; i++)
    {
        for (int j = 0; j < mm;j++)
        {
            std::cout << a[i][j];
        }
        std::cout << "\n";
    }
}


int main()
{
    int n, m;
    std::cin >> n >> m;

    int** array;
    array = new int* [n];
    for (int i = 0; i < n; i++)
        array[i] = new int[m];

    array = Input(array, n, m);

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            if (array[i][j] >= array[i][j + 1])
            {
                count++;
            }
        }
        if (count == m - 1)
        {
            for (int j = 0; j < m / 2;j++)
            {
                std::swap(array[i][j], array[i][m - 1 - j]);
            }
        }
        count = 0;
    }


    Print(array, n, m);
    //std::cout << a[i][j];

    delete[] array;
    return 0;
}