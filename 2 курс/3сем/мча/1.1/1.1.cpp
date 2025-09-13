#include <iostream>
#include <iomanip>
using namespace std;

const int n = 5;
const int ACCURACY = 4;

double* gauss(double A[n][n], double* b, int n) {
    double* x = new double[n];
    double** A_copy = new double* [n];
    double* b_copy = new double[n];

    // Выделение памяти и копирование данных
    for (int i = 0; i < n; i++) {
        A_copy[i] = new double[n];
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
        b_copy[i] = b[i];
    }

    for (int i = 0; i < n; i++) {
        if (A_copy[i][i] != 0) {
            for (int j = i + 1; j < n; j++) {
                double q = A_copy[j][i] / A_copy[i][i];
                for (int k = i; k < n; k++) {
                    if (k == i) A_copy[j][k] = 0;
                    else A_copy[j][k] -= q * A_copy[i][k];
                }
                b_copy[j] -= q * b_copy[i];
            }
        }
        else {
            std::cout << "Нельзя решить систему данным методом: ведущий элемент стал равен 0\n";
            return x;
        }
    }

    // Проверка на множество решений
    for (int i = 0; i < n; i++) {
        bool allZeros = true;
        for (int j = 0; j < n; j++) {
            if (A_copy[i][j] != 0) {
                allZeros = false;
                break;
            }
        }
        if (allZeros && b_copy[i] != 0) {
            std::cout << "Система не имеет решений\n";
            return x;
        }
    }

    // Обратный ход и вычисление решений
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            b_copy[i] -= x[j] * A_copy[i][j];
        }
        if (A_copy[i][i] == 0) {
            std::cout << "Система имеет множество решений\n";
            return x;
        }
        x[i] = b_copy[i] / A_copy[i][i];
    }

    // Освобождение памяти для A_copy
    for (int i = 0; i < n; i++) {
        delete[] A_copy[i];
    }
    delete[] A_copy;

    return x;
}

double* gauss2(double A[n][n], double* b, int n) {
    double* x = new double[n];
    double** A_copy = new double* [n];
    double* b_copy = new double[n];

    // Выделение памяти и копирование данных
    for (int i = 0; i < n; i++) {
        A_copy[i] = new double[n];
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
        b_copy[i] = b[i];
    }

    for (int i = 0; i < n; i++) {
        int max = std::abs(A_copy[i][i]);
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (std::abs(A_copy[j][i]) > max) {
                maxIndex = j;
                max = std::abs(A_copy[j][i]);
            }
        }
        for (int j = 0; j < n; j++) {
            std::swap(A_copy[i][j], A_copy[maxIndex][j]);
        }
        std::swap(b_copy[i], b_copy[maxIndex]);

        if (A_copy[i][i] != 0) {
            for (int j = i + 1; j < n; j++) {
                double q = A_copy[j][i] / A_copy[i][i];
                for (int k = i; k < n; k++) {
                    if (k == i) A_copy[j][k] = 0;
                    else A_copy[j][k] -= q * A_copy[i][k];
                }
                b_copy[j] -= q * b_copy[i];
            }
        }
        else {
            std::cout << "Нельзя решить систему данным методом: столбец возможных ведущих элементов стал равен 0\n";
            return x;
        }
    }

    // Проверка на множество решений
    for (int i = 0; i < n; i++) {
        bool allZeros = true;
        for (int j = 0; j < n; j++) {
            if (A_copy[i][j] != 0) {
                allZeros = false;
                break;
            }
        }
        if (allZeros && b_copy[i] != 0) {
            std::cout << "Система не имеет решений\n";
            return x;
        }
    }

    // Обратный ход и вычисление решений
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            b_copy[i] -= x[j] * A_copy[i][j];
        }
        if (A_copy[i][i] == 0) {
            std::cout << "Система имеет множество решений\n";
            return x;
        }
        x[i] = b_copy[i] / A_copy[i][i];
    }

    // Освобождение памяти для A_copy
    for (int i = 0; i < n; i++) {
        delete[] A_copy[i];
    }
    delete[] A_copy;

    return x;
}

double* gauss3(double A[n][n], double* b, int n) {
    double* x = new double[n];
    double** A_copy = new double* [n];
    double* b_copy = new double[n];

    // Выделение памяти и копирование данных
    for (int i = 0; i < n; i++) {
        A_copy[i] = new double[n];
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
        b_copy[i] = b[i];
    }

    for (int i = 0; i < n; i++) {
        double max = std::abs(A_copy[i][0]);
        int maxIndexX = i;
        int maxIndexY = 0;
        for (int j = i; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (std::abs(A_copy[j][k]) > max) {
                    maxIndexX = j;
                    maxIndexY = k;
                    max = std::abs(A_copy[j][k]);
                }
            }
        }
        for (int j = 0; j < n; j++) {
            std::swap(A_copy[i][j], A_copy[maxIndexX][j]);
        }
        std::swap(b_copy[i], b_copy[maxIndexX]);

        if (A_copy[i][maxIndexY] != 0) {
            for (int j = i + 1; j < n; j++) {
                double q = A_copy[j][maxIndexY] / A_copy[i][maxIndexY];
                for (int k = 0; k < n; k++) {
                    if (k == maxIndexY) A_copy[j][k] = 0;
                    else A_copy[j][k] -= q * A_copy[i][k];
                }
                b_copy[j] -= q * b_copy[i];
            }
        }
        else {
            std::cout << "Нельзя решить систему данным методом: элементы в оставшихся строках стали нулевыми (система не имеет единственное решение)\n";
            return x;
        }
    }

    // Проверка на множество решений
    for (int i = 0; i < n; i++) {
        bool allZeros = true;
        for (int j = 0; j < n; j++) {
            if (A_copy[i][j] != 0) {
                allZeros = false;
                break;
            }
        }
        if (allZeros && b_copy[i] != 0) {
            std::cout << "Система не имеет решений\n";
            return x;
        }
    }

    bool* xFound = new bool[n];
    for (int i = 0; i < n; i++) {
        xFound[i] = false;
    }

    // Обратный ход и вычисление решений
    for (int i = n - 1; i >= 0; i--) {
        int curX;
        for (int j = 0; j < n; j++) {
            if (A_copy[i][j] != 0 && !xFound[j]) {
                curX = j;
            }
            if (A_copy[i][j] != 0 && xFound[j]) {
                b_copy[i] -= x[j] * A_copy[i][j];
            }
        }
        x[curX] = b_copy[i] / A_copy[i][curX];
        xFound[curX] = true;
    }

    // Освобождение памяти для A_copy
    for (int i = 0; i < n; i++) {
        delete[] A_copy[i];
    }
    delete[] A_copy;

    delete[] xFound;
    return x;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout.precision(ACCURACY);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    //double b[n] = { 4.2, 4.2, 4.2, 4.2, 4.2 };
    double b[n];
    for (int i = 0; i < n; i++) {
        b[i] = 4.2;
    }

    double C[n][n] = { {0.2,0,0.2,0,0},
                        {0,0.2,0,0.2,0},
                        {0.2,0,0.2,0,0.2},
                        {0,0.2,0,0.2,0},
                        {0,0,0.2,0,0.2} };

    double D[n][n] = { {2.33,0.81,0.67,0.92,-0.53},
                        {-0.53,2.33,0.81,0.67,0.92},
                        {0.92,-0.53,2.33,0.81,0.67},
                        {0.67,0.92,-0.53,2.33,0.81},
                        {0.81,0.67,0.92,-0.53,2.33} };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] *= 5;


    double A[n][n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = 13 * C[i][j] + D[i][j];

    setlocale(0, "");

    // Создайте массивы для хранения результатов
    double* result1 = new double[n];
    double* result2 = new double[n];
    double* result3 = new double[n];

    // Выполните метод Гаусса (схема единственного деления)
    double* x1 = gauss(A, b, n);
    for (int i = 0; i < n; i++) {
        result1[i] = x1[i];
    }

    // Выполните метод Гаусса (схема частичного выбора)
    double* x2 = gauss2(A, b, n);
    for (int i = 0; i < n; i++) {
        result2[i] = x2[i];
    }

    // Выполните метод Гаусса (схема полного выбора)
    double* x3 = gauss3(A, b, n);
    for (int i = 0; i < n; i++) {
        result3[i] = x3[i];
    }

    // Выведите результаты
    cout << "Метод Гаусса (схема единственного деления):\n";
    for (int i = 0; i < n; i++) {
        cout << result1[i] << "\n";
    }

    cout << "Метод Гаусса (схема частичного выбора):\n";
    for (int i = 0; i < n; i++) {
        cout << result2[i] << "\n";
    }

    cout << "Метод Гаусса (схема полного выбора):\n";
    for (int i = 0; i < n; i++) {
        cout << result3[i] << "\n";
    }

    // Освободите выделенную память
    delete[] x1;
    delete[] x2;
    delete[] x3;
    delete[] result1;
    delete[] result2;
    delete[] result3;

    // Матрица A1 и вектор b1
    double A1[n][n] = {
        {2.0, 1.0, 1.0, 0.0, 0.0},
        {1.0, 2.0, 0.0, 1.0, 0.0},
        {0.0, 1.0, 3.0, 0.0, 1.0},
        {1.0, 0.0, 0.0, 2.0, 1.0},
        {0.0, 0.0, 1.0, 1.0, 4.0}
    };
    double b1[n] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    // Создайте массивы для хранения результатов для A1
    double* result1_A1 = new double[n];
    double* result2_A1 = new double[n];
    double* result3_A1 = new double[n];

    // Примените метод Гаусса (схема единственного деления) к A1
    double* x1_A1 = gauss(A1, b1, n);
    for (int i = 0; i < n; i++) {
        result1_A1[i] = x1_A1[i];
    }

    // Примените метод Гаусса (схема частичного выбора) к A1
    double* x2_A1 = gauss2(A1, b1, n);
    for (int i = 0; i < n; i++) {
        result2_A1[i] = x2_A1[i];
    }

    // Примените метод Гаусса (схема полного выбора) к A1
    double* x3_A1 = gauss3(A1, b1, n);
    for (int i = 0; i < n; i++) {
        result3_A1[i] = x3_A1[i];
    }

    // Выведите результаты для матрицы A1
    std::cout << "Результаты для матрицы A1:\n";
    std::cout << "Метод Гаусса (схема единственного деления):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result1_A1[i] << "\n";
    }

    std::cout << "Метод Гаусса (схема частичного выбора):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result2_A1[i] << "\n";
    }

    std::cout << "Метод Гаусса (схема полного выбора):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result3_A1[i] << "\n";
    }

    // Освободите выделенную память для матрицы A1
    delete[] x1_A1;
    delete[] x2_A1;
    delete[] x3_A1;
    delete[] result1_A1;
    delete[] result2_A1;
    delete[] result3_A1;


    // Матрица A2 и вектор b2
    double A2[n][n] = {
{1.0, 2.0, 3.0, 4.0, 5.0},
    {2.0, 4.0, 6.0, 8.0, 10.0},
    {1.0, 2.0, 3.0, 4.0, 5.0},
    {2.0, 4.0, 6.0, 8.0, 10.0},
    {0.0, 0.0, 0.0, 0.0, 0.0}
    };
    double b2[n] = { 10.0, 20.0, 10.0, 20.0, 0.0 };

    // Создайте массивы для хранения результатов для A2
    double* result1_A2 = new double[n];
    double* result2_A2 = new double[n];
    double* result3_A2 = new double[n];

    // Примените метод Гаусса (схема единственного деления) к A2
    double* x1_A2 = gauss(A2, b2, n);
    for (int i = 0; i < n; i++) {
        result1_A2[i] = x1_A2[i];
    }

    // Примените метод Гаусса (схема частичного выбора) к A2
    double* x2_A2 = gauss2(A2, b2, n);
    for (int i = 0; i < n; i++) {
        result2_A2[i] = x2_A2[i];
    }

    // Примените метод Гаусса (схема полного выбора) к A2
    double* x3_A2 = gauss3(A2, b2, n);
    for (int i = 0; i < n; i++) {
        result3_A2[i] = x3_A2[i];
    }

    // Выведите результаты для матрицы A2
    std::cout << "Результаты для матрицы A2:\n";
    std::cout << "Метод Гаусса (схема единственного деления):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result1_A2[i] << "\n";
    }

    std::cout << "Метод Гаусса (схема частичного выбора):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result2_A2[i] << "\n";
    }

    std::cout << "Метод Гаусса (схема полного выбора):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result3_A2[i] << "\n";
    }

    // Освободите выделенную память для матрицы A2
    delete[] x1_A2;
    delete[] x2_A2;
    delete[] x3_A2;
    delete[] result1_A2;
    delete[] result2_A2;
    delete[] result3_A2;

    // Матрица A3 и вектор b3
    double A3[n][n] = {
        {1.0, 2.0, 3.0, 4.0, 5.0},
    {2.0, 4.0, 6.0, 8.0, 10.0},
    {3.0, 6.0, 9.0, 12.0, 15.0},
    {4.0, 8.0, 12.0, 16.0, 20.0},
    {5.0, 10.0, 15.0, 20.0, 25.0}
    };
    double b3[n] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    // Создайте массивы для хранения результатов для A3
    double* result1_A3 = new double[n];
    double* result2_A3 = new double[n];
    double* result3_A3 = new double[n];

    // Примените метод Гаусса (схема единственного деления) к A3
    double* x1_A3 = gauss(A3, b3, n);
    for (int i = 0; i < n; i++) {
        result1_A3[i] = x1_A3[i];
    }

    // Примените метод Гаусса (схема частичного выбора) к A3
    double* x2_A3 = gauss2(A3, b3, n);
    for (int i = 0; i < n; i++) {
        result2_A3[i] = x2_A3[i];
    }

    // Примените метод Гаусса (схема полного выбора) к A3
    double* x3_A3 = gauss3(A3, b3, n);
    for (int i = 0; i < n; i++) {
        result3_A3[i] = x3_A3[i];
    }

    // Выведите результаты для матрицы A3
    std::cout << "Результаты для матрицы A3:\n";
    std::cout << "Метод Гаусса (схема единственного деления):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result1_A3[i] << "\n";
    }

    std::cout << "Метод Гаусса (схема частичного выбора):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result2_A3[i] << "\n";
    }

    std::cout << "Метод Гаусса (схема полного выбора):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << result3_A3[i] << "\n";
    }

    // Освободите выделенную память для матрицы A3
    delete[] x1_A3;
    delete[] x2_A3;
    delete[] x3_A3;
    delete[] result1_A3;
    delete[] result2_A3;
    delete[] result3_A3;

    return 0;

}