#include <iostream>

//делит на два столбец с номером строки которая вся нули.
//если 0 строка состоит из нулей то все элементы нулевого столбца делятся на два.

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
            std::cout << a[i][j] << " ";
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
 
    int first, count=0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (array[i][j] == 0)
            {
                count++;
            }
        }
       
        if (count == m)
        {
            first = i;
            break;
        }
    }
    
    for (i = 0; i < n;i++)
    {
      array[i][first] = array[i][first] / 2;
    }
    

   Print(array, n, m);

    delete[] array;
    return 0;

}