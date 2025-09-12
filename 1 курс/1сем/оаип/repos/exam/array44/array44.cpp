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

void EditArray(int**** array, int***& sizes, int m1, int m2, int m3)
{
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            for (int k = 0; k < m3; k++)
            {
                int x = 0;
                int size = sizes[i][j][k];
                for (int l = 0; l < size; l++)
                {
                    if (array[i][j][k][l] % 11 != 0)
                    {
                        array[i][j][k][x] = array[i][j][k][l];
                        x++;
                    }
                    else {
                        sizes[i][j][k]--;
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void OutputArray(int**** array, int*** sizes, int m1, int m2, int m3)
{
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < m2; j++) {

            for (int k = 0; k < m3; k++) {

                for (int l = 0; l < sizes[i][j][k]; l++) {
                    std::cout << array[i][j][k][l] << ' ';
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

int main()
{
    int n1, n2, n3, n4;
    std::cin >> n1 >> n2 >> n3 >> n4;
    int**** a; int*** sizes;
    a = new int*** [n1];
    sizes = new int** [n2];

    for (int i = 0; i < n1; i++)
    {
        a[i] = new int** [n2];
        sizes[i] = new int* [n3];

        for (int j = 0; j < n2; j++)
        {
            a[i][j] = new int* [n3];
            sizes[i][j] = new int[n4];

            for (int k = 0; k < n3; k++)
            {
                sizes[i][j][k] = n4;
                a[i][j][k] = new int[n4];
            }

        }
    }

    a = InputArray(a, n1, n2, n3, n4);
    // a = Edit2Array(a, n1, n2, n3, n4);

    EditArray(a, sizes, n1, n2, n3);

    OutputArray(a, sizes, n1, n2, n3);
    delete[] a;
}