// змейка - начинаем справа налево
#include <iostream>

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

void PrintSnake(int** ar, int nn, int mm)
{
    for (int i = 0; i < nn; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = mm-1; j >=0;j--) // четные строки печатаем справа налево
            {
                std::cout << ar[i][j] << " ";
            }
             std::cout << "\n";
        }
        else
        {
            for (int j = 0; j < mm; j ++) // нечетные строки печатаем слева направо
            {
                std::cout << ar[i][j] << " ";
            }
            // std::cout << "\n";
        }
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

    PrintSnake(array, n, m);

    delete[] array;
    return 0;
}
    
    
    /*
    int x = 4, y = 5;

    int** mas = new int* [x];
    for (int i = 0; i < x; i++) {
        mas[i] = new int[y];
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            std::cin >> mas[i][j];
        }
    }

    std::cout << std::endl;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            std::cout << mas[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << std::endl;

    int r = x * y;
    int nia = -1;
    int right = y - 1;
    int left = 0;
    int i = 0;
    int yy = y - 1;
    for (int j = yy; r > 0; j = j + nia) {
        if (j < left) {
            i++;
            nia = -nia;
            yy = 0;

        }
        else if (j > right) {
            i++;
            nia = -nia;
            yy = y - 1;
        }
        else {
            std::cout << mas[i][j] << " ";
            r--;
        }
    }


    //1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

    delete[] mas;
    mas = nullptr;

    return 0;*/
//}