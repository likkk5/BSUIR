#include <iostream>

int**** InputArray(int**** array, int m1, int m2, int m3, int m4)
{
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < m2; j++)

            for (int k = 0; k < m3; k++)

                for (int l = 0; l < m4; l++)
                    std::cin >> array[i][j][k][l];

    }

    return array;
}

int* EditArray(int**** array, int m1, int m2, int m3, int m4, int* newarray)
{
    int x = 0;
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < m2; j++)

            for (int k = 0; k < m3; k++)

                for (int l = 0; l < m4; l++)
                {
                    if (array[i][j][k][l] % 11 != 0)
                    {
                        newarray[x] = array[i][j][k][l];
                        std::cout << newarray[x] << "\n";
                        x++;
                    }
                }
    }

    return newarray;
}



void OutputArray(int**** array, int m1, int m2, int m3, int m4)
{
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < m2; j++)

            for (int k = 0; k < m3; k++)

                for (int l = 0; l < m4; l++)
                    std::cout << array[i][j][k][l] << "\n";
    }
}

int main()
{
    int n1, n2, n3, n4;
    std::cin >> n1 >> n2 >> n3 >> n4;
    int**** a;
    a = new int*** [n1];
    for (int i = 0; i < n1; i++)
    {
        a[i] = new int** [n2];
        for (int j = 0; j < n2; j++)
        {
            a[i][j] = new int* [n3];
            for (int k = 0; k < n3; k++)
            {
                a[i][j][k] = new int[n4];
            }

        }
    }

    a = InputArray(a, n1, n2, n3, n4);
   // a = Edit2Array(a, n1, n2, n3, n4);

    int* b = new int[n1 * n2 * n3 * n4];
    b = EditArray(a, n1, n2, n3, n4, b);

    //OutputArray(a, n1, n2, n3, n4);

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            for (int k = 0; k < n3; ++k) {
                delete[] a[i][j][k];
            }
            delete[] a[i][j];
        }
        delete[] a[i];
    }
    delete[] a;

   delete[] b;
}