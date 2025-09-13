#include <iostream>
#include <iomanip>
using namespace std;

const int n = 5;
const int ACCURACY = 8;

// Выполните метод Гаусса (схема единственного деления)
double* gauss(double A[n][n], double* b, int n) {
    double* x = nullptr; 

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

    //for (int i = 0; i < n; i++) {
    //    if (A_copy[i][i] != 0) {
    //        for (int j = i + 1; j < n; j++) {
    //            double q = A_copy[j][i] / A_copy[i][i];
    //            for (int k = i; k < n; k++) {
    //                if (k == i) A_copy[j][k] = 0;
    //                else A_copy[j][k] -= q * A_copy[i][k];
    //            }
    //            b_copy[j] -= q * b_copy[i];
    //        }
    //    }
    //    else {
    //        std::cout << "Нельзя решить систему данным методом: ведущий элемент стал равен 0\n";
    //        delete[] x;
    //        return nullptr; 
    //    }
    //}

    //// Проверка на множество решений
    //for (int i = 0; i < n; i++) {
    //    bool allZeros = true;
    //    for (int j = 0; j < n; j++) {
    //        if (A_copy[i][j] != 0) {
    //            allZeros = false;
    //            break;
    //        }
    //    }
    //    if (allZeros && b_copy[i] != 0) {
    //        std::cout << "Система не имеет решений\n";
    //        delete[] x;
    //        return nullptr; 
    //    }
    //}

    //// Выделение памяти для x
    //x = new double[n];

    //// Обратный ход и вычисление решений
    //for (int i = n - 1; i >= 0; i--) {
    //    for (int j = n - 1; j > i; j--) {
    //        b_copy[i] -= x[j] * A_copy[i][j];
    //    }
    //    if (A_copy[i][i] == 0) {
    //        std::cout << "Система имеет множество решений\n";
    //        delete[] x;
    //        return nullptr; 
    //    }
    //    x[i] = b_copy[i] / A_copy[i][i];
    //}

    bool hasNoSolution = false;
    bool hasInfiniteSolutions = false;

    for (int i = 0; i < n; i++) { //выбор первого ненулевого элемента
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
            // Check for rows with all coefficients zero
            bool allZeros = true;
            for (int j = 0; j < n; j++) {
                if (A_copy[i][j] != 0) {
                    allZeros = false;
                    break;
                }
            }
            if (allZeros && b_copy[i] != 0) {
                hasNoSolution = true;
                break;
            }
            else if (allZeros && b_copy[i] == 0) {
                hasInfiniteSolutions = true;
            }
        }
    }

    if (hasNoSolution) {
        std::cout << "Система не имеет решений\n";
        delete[] x;
        return nullptr;
    }

    if (hasInfiniteSolutions) {
        std::cout << "Система имеет множество решений\n";
        delete[] x;
        return nullptr;
    }

    // Освобождение памяти для A_copy
    for (int i = 0; i < n; i++) {
        delete[] A_copy[i];
    }
    delete[] A_copy;

    return x;
}

// Выполните метод Гаусса (схема частичного выбора)
double* gauss2(double A[n][n], double* b, int n) {
    double* x = nullptr; 

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

    for (int i = 0; i < n; i++) { //выбор максимального элемента
        int maxIndex = i;
        double max = std::abs(A_copy[i][i]); 

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
            delete[] x;
            return nullptr; 
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
            delete[] x;
            return nullptr; 
        }
    }

    // Выделение памяти для x
    x = new double[n];

    // Обратный ход и вычисление решений
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            b_copy[i] -= x[j] * A_copy[i][j];
        }
        if (A_copy[i][i] == 0) {
            std::cout << "Система имеет множество решений\n";
            delete[] x;
            return nullptr; 
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

// Выполните метод Гаусса (схема полного выбора)
double* gauss3(double A[n][n], double* b, int n) {
    double* x = nullptr; 

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

    for (int i = 0; i < n; i++) {//выбор максимального по модулю элемента в текущем столбце
        int maxIndexX = i;
        int maxIndexY = i;
        double max = std::abs(A_copy[i][i]); 

        for (int j = i; j < n; j++) {
            for (int k = i; k < n; k++) {
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

        for (int j = 0; j < n; j++) {
            std::swap(A_copy[j][i], A_copy[j][maxIndexY]);
        }

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
            delete[] x;
            return nullptr; 
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
            delete[] x;
            return nullptr; 
        }
    }

    // Выделение памяти для x
    x = new double[n];

    // Обратный ход и вычисление решений
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            b_copy[i] -= x[j] * A_copy[i][j];
        }
        if (A_copy[i][i] == 0) {
            std::cout << "Система имеет множество решений\n";
            delete[] x;
            return nullptr; 
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


    double A[n][n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = 14 * C[i][j] + D[i][j];


    // Выполните метод Гаусса (схема единственного деления)
    double* x1 = gauss(A, b, n);
    if (x1 != nullptr) {
        cout << "Решение методом Гаусса (схема единственного деления):" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x1[i] << endl;
            //cout << x1[i] << endl;
        }
        delete[] x1;
    }

    // Выполните метод Гаусса (схема частичного выбора)
    double* x2 = gauss2(A, b, n);
    if (x2 != nullptr) {
        cout << "Решение методом Гаусса (схема частичного выбора):" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x2[i] << endl;
            //cout << x2[i] << endl;

        }
        delete[] x2;
    }

    // Выполните метод Гаусса (схема полного выбора)
    double* x3 = gauss3(A, b, n);
    if (x3 != nullptr) {
        cout << "Решение методом Гаусса (схема полного выбора):" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x3[i] << endl;
            //cout << x3[i] << endl;

        }
        delete[] x3;
    }

    // Матрица A1 и вектор b1
    double A1[n][n] = {
        {2.0, 1.0, 1.0, 0.0, 0.0},
        {1.0, 2.0, 0.0, 1.0, 0.0},
        {0.0, 1.0, 3.0, 0.0, 1.0},
        {1.0, 0.0, 0.0, 2.0, 1.0},
        {0.0, 0.0, 1.0, 1.0, 4.0}
    };
    double b1[n] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    // Примените метод Гаусса (схема единственного деления) к A1
    double* x1_A1 = gauss(A1, b1, n);
    if (x1_A1 != nullptr) {
        cout << "Решение методом Гаусса (схема единственного деления) к A1:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x1_A1[i] << endl;
        }
        delete[] x1_A1;
    }

    // Примените метод Гаусса (схема частичного выбора) к A1
    double* x2_A1 = gauss2(A1, b1, n);
    if (x2_A1 != nullptr) {
        cout << "Решение методом Гаусса (схема частичного выбора) к A1:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x2_A1[i] << endl;
        }
        delete[] x2_A1;
    }

    // Примените метод Гаусса (схема полного выбора) к A1
    double* x3_A1 = gauss3(A1, b1, n);
    if (x3_A1 != nullptr) {
        cout << "Решение методом Гаусса (схема полного выбора) к A1:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x3_A1[i] << endl;
        }
        delete[] x3_A1;
    }

    // Матрица A2 и вектор b2
    double A2[n][n] = {
    {1.0, 2.0, 3.0, 4.0, 5.0},
    {2.0, 4.0, 6.0, 8.0, 10.0},
    {3.0, 6.0, 9.0, 12.0, 15.0},
    {4.0, 8.0, 12.0, 16.0, 20.0},
    {5.0, 10.0, 15.0, 20.0, 25.0}
    };
    double b2[n] = { 15.0, 30.0, 45.0, 60.0, 75.0 };

    cout << "Примените метод Гаусса к A2:"<< endl;
    // Примените метод Гаусса к A2
    double* x1_A2 = gauss(A2, b2, n);
    if (x1_A2 != nullptr) {
        cout << "Решение методом Гаусса (схема единственного деления) к A2:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x1_A2[i] << endl;
        }
        delete[] x1_A2;
    }

    // Примените метод Гаусса (схема частичного выбора) к A2
    double* x2_A2 = gauss2(A2, b2, n);
    if (x2_A2 != nullptr) {
        cout << "Решение методом Гаусса (схема частичного выбора) к A2:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x2_A2[i] << endl;
        }
        delete[] x2_A2;
    }

    // Примените метод Гаусса (схема полного выбора) к A2
    double* x3_A2 = gauss3(A2, b2, n);
    if (x3_A2 != nullptr) {
        cout << "Решение методом Гаусса (схема полного выбора) к A2:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x3_A2[i] << endl;
        }
        delete[] x3_A2;
    }

    // Матрица A3 и вектор b3
    double A3[n][n] = {
        {1.0, 2.0, 3.0, 4.0, 5.0},
    {2.0, 4.0, 6.0, 8.0, 10.0},
    {3.0, 6.0, 9.0, 12.0, 15.0},
    {4.0, 8.0, 12.0, 16.0, 20.0},
    {5.0, 10.0, 15.0, 20.0, 25.0}
    };
    double b3[n] = { 1.0, 2.0, 3.0, 4.0, 6.0 };

    cout << "Примените метод Гаусса к A3:" << endl;

    // Примените метод Гаусса к A3
    double* x1_A3 = gauss(A3, b3, n);
    if (x1_A3 != nullptr) {
        cout << "Решение методом Гаусса (схема единственного деления) к A3:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x1_A3[i] << endl;
        }
        delete[] x1_A3;
    }

    // Примените метод Гаусса (схема частичного выбора) к A3
    double* x2_A3 = gauss2(A3, b3, n);
    if (x2_A3 != nullptr) {
        cout << "Решение методом Гаусса (схема частичного выбора) к A3:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x2_A3[i] << endl;
        }
        delete[] x2_A3;
    }

    // Примените метод Гаусса (схема полного выбора) к A3
    double* x3_A3 = gauss3(A3, b3, n);
    if (x3_A3 != nullptr) {
        cout << "Решение методом Гаусса (схема полного выбора) к A3:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << setprecision(ACCURACY) << x3_A3[i] << endl;
        }
        delete[] x3_A3;
    }

    return 0;

}