#include <iostream>
const int n = 5;
using namespace std;

bool check_norm(double B[n][n]) {                       //проверка на сходимость                             
    double norm = 0;                                    //норма 1
    for (int j = 0; j < n; j++) {
        norm += abs(B[0][j]);
    }
    for (int i = 1; i < n; i++) {
        double temp = 0;
        for (int j = 0; j < n; j++) {
            temp += abs(B[i][j]);
        }
        if (temp > norm)norm = temp;
    }
    if (norm < 1) { return true; }

    norm = 0;                                            //норма 2
    for (int j = 0; j < n; j++) {
        norm += abs(B[j][0]);
    }
    for (int i = 1; i < n; i++) {
        double temp = 0;
        for (int j = 0; j < n; j++) {
            temp += abs(B[j][i]);
        }
        if (temp > norm)norm = temp;
    }
    if (norm < 1) { return true; }

    norm = 0;                                            //норма 3
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            norm += B[j][i] * B[j][i];
        }
    }
    norm = sqrt(norm);
    if (norm < 1) { return true; }
    return false;
}

double* simple_iterations(double A[n][n], double b[n]) {
    double B[n][n];
    double c[n];
    for (int i = 0; i < n; i++) {                       //B = E-A
        for (int j = 0; j < n; j++) {
            B[i][j] = -A[i][j];
            if (i == j)B[i][j]++;
        }
    }
    for (int i = 0; i < n; i++)                          //c = b
        c[i] = b[i];



    if (check_norm(B) == false) {
        for (int i = 0; i < n; i++) {                    //альтернативный случай матрицы B
            for (int j = 0; j < n; j++) {
                B[i][j] = -A[i][j] / A[i][i];
                if (i == j)B[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++)                      //альтернативный случай вектора с
            c[i] = b[i] / A[i][i];
    }

    if (check_norm(B) == false) {
        std::cout << "Для рассматриваемых матриц B итерационный метод неприменим\n";
        double* x = new double[n];
        for (int i = 0; i < n; i++)
            x[i] = 0;
        return x;
    }

    double* x = new double[n];
    double* x2 = new double[n];
    for (int i = 0; i < n; i++)
        x2[i] = c[i];

    double iterationCount = 0; // Переменная для отслеживания количества итераций
    double maxE;
    do {
        for (int i = 0; i < n; i++) {
            x[i] = x2[i];
        }

        for (int i = 0; i < n; i++) {
            x2[i] = c[i];
            for (int j = 0; j < n; j++) {
                x2[i] += B[i][j] * x[j];
            }
        }

        for (int i = 0; i < n; i++) {
            cout << x2[i] << " ";
        }
        cout << "\n";

        maxE = abs(x2[0] - x[0]);        //максимальная разница между значениями итераций
        for (int i = 1; i < n; i++) {
            if (abs(x2[i] - x[i]) > maxE)maxE = abs(x2[0] - x[0]);
        }
        iterationCount++; 

    } while (maxE > 0.00001);

    cout << "Количество итераций метода простых итераций: " << iterationCount << endl;
    return x2;
}


double* zeidel(double A[n][n], double b[n]) {
    bool diagonal_dominance = 1;                  //проверка на диагональное преобладание
    for (int i = 0; i < n; i++) {
        double temp = 0;
        for (int j = 0; j < n; j++) {
            if (j != i)temp += abs(A[j][i]);
        }
        if (temp > abs(A[i][i]))diagonal_dominance = 0;
    }
    if (!diagonal_dominance) {
        diagonal_dominance = 1;
        for (int i = 0; i < n; i++) {
            double temp = 0;
            for (int j = 0; j < n; j++) {
                if (j != i)temp += abs(A[j][i]);
            }
            if (temp > abs(A[i][i]))diagonal_dominance = 0;
        }
        if (!diagonal_dominance) {
            std::cout << "У данной матрицы отсутствует диагональное преобладание, метод Зейделя может быть неприменим к данной матрице\n";
            double* x = new double[n];
            for (int i = 0; i < n; i++)
                x[i] = 0;
            return x;
        }
    }

    double B[n][n];
    double c[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = -A[i][j] / A[i][i];
            if (i == j)B[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
        c[i] = b[i] / A[i][i];

    double* x = new double[n];
    double* x2 = new double[n];
    for (int i = 0; i < n; i++)
        x[i] = c[i];

    double iterationCount = 0; // Переменная для отслеживания количества итераций

    double maxE;
    do {
        for (int i = 0; i < n; i++) {
            x2[i] = x[i];
        }

        for (int i = 0; i < n; i++) {
            double temp = c[i];
            for (int j = 0; j < n; j++) {
                temp += B[i][j] * x[j];
            }
            x[i] = temp;
        }

        for (int i = 0; i < n; i++) {
            cout << x2[i] << " ";
        }
        cout << "\n";

        maxE = abs(x2[0] - x[0]);        //максимальная разница между значениями итераций
        for (int i = 1; i < n; i++) {
            if (abs(x2[i] - x[i]) > maxE)maxE = abs(x2[0] - x[0]);
        }
        iterationCount++; 

    } while (maxE > 0.00001);

    bool hasInfiniteSolutions = true;
    for (int i = 0; i < n; i++) {
        double rowSum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                rowSum += abs(B[i][j]);
            }
        }
        if (rowSum >= abs(B[i][i])) {
            hasInfiniteSolutions = false;
            break;
        }
    }

    if (hasInfiniteSolutions) {
        std::cout << "Система имеет бесконечное множество решений." << std::endl;
    }
    else {
        std::cout << "Система имеет единственное решение." << std::endl;
    }

    cout << "Количество итераций метода Зейделя: " << iterationCount << endl;
    return x2;
}
void Inversion(double** A, int N) //получение обратной матрицы
{
    double temp;
    double** E = new double* [N];
    for (int i = 0; i < N; i++)
        E[i] = new double[N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            E[i][j] = 0.0;
            if (i == j) E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = A[k][k];
        for (int j = 0; j < N; j++)
        {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = A[i][k];
            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];

    for (int i = 0; i < N; i++)
        delete[] E[i];

    delete[] E;
}

double NormaSearch(double** matrix_X, int n) {
    long double normA = 0;
    for (int i = 0; i < n; i++) {
        long double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix_X[i][j];
        }
        normA = std::max(normA, sum);
    }
    return normA;
}

double Condition_Number(double** matrix_A, double** inversed_matrix, int n) {
    double normA = NormaSearch(matrix_A, n);
    double normI = NormaSearch(inversed_matrix, n);
    double nu = normA * normI;
    return nu;
}

int main()
{
    std::cout.precision(9);
    double C[n][n] = { {0.01, 0, -0.02, 0, 0},
                        {0.01, 0.01, -0.02, 0, 0},
                        {0, 0.01, 0.01, 0, -0.02},
                        {0, 0, 0.01, 0.01, 0},
                        {0, 0, 0, 0.01, 0.01} };

    double D[n][n] = { {1.33, 0.21, 0.17, 0.12, -0.13},
                            {-0.13, -1.33, 0.11, 0.17, 0.12},
                            {0.12, -0.13, -1.33, 0.11, 0.17},
                            {0.17, 0.12, -0.13, -1.33, 0.11},
                            {0.11, 0.67, 0.12, -0.13, -1.33} };
    double A[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = D[i][j] + 13 * C[i][j];

    double b[n] = { 1.2, 2.2, 4.0, 0, -1.2 };

    double A_non_diagonal[n][n] = {
        {2, 3, 1},
        {1, 2, 1},
        {0, 2, 2}
    };
    double b_non_diagonal[n] = { 6, 4, 4 };  

    double A_rank_deficient[n][n] = {
        {1, 2},
        {2, 4}
    };

    double b_rank_deficient[n] = { 3, 6 };

    double A3[n][n] = {
    {2, 0},
    {1, 1},
    };

    double b3[n] = {2,1};

    setlocale(0, "");
    int choice;
    while (true) {
        cout << "1. Метод простых итераций (матрица A)\n";
        cout << "2. Метод Зейделя (матрица A)\n";
        cout << "3. Метод простых итераций (матрица A_non_diagonal)\n";
        cout << "4. Метод Зейделя (матрица A_non_diagonal)\n";
        cout << "5. Метод простых итераций (матрица A_rank_deficient)\n";
        cout << "6. Метод Зейделя (матрица A_rank_deficient)\n";
        cout << "7. Метод простых итераций (матрица A3)\n";
        cout << "8. Метод Зейделя (матрица A3)\n";
        cout << "9. Высчитываем погрешность\n";
        cout << "10. Выход\n";
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1: {
            cout << "Промежуточные вычисления: \n";
            double* x = simple_iterations(A, b);
            cout << "Итоговый результат: \n";
            cout.precision(5);
            for (int i = 0; i < n; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 2: {
            cout << "Промежуточные вычисления: \n";
            double* x = zeidel(A, b);
            cout << "Итоговый результат: \n";
            cout.precision(5);
            for (int i = 0; i < n; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 3: {
            cout << "Промежуточные вычисления (матрица A_non_diagonal): \n";
            double* x = simple_iterations(A_non_diagonal, b_non_diagonal);
            cout << "Итоговый результат (матрица A_non_diagonal): \n";
            cout.precision(5);
            for (int i = 0; i < n; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 4: {
            cout << "Промежуточные вычисления (матрица A_non_diagonal): \n";
            double* x = zeidel(A_non_diagonal, b_non_diagonal);
            cout << "Итоговый результат (матрица A_non_diagonal): \n";
            cout.precision(5);
            for (int i = 0; i < n; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 5: {
            cout << "Промежуточные вычисления (матрица A_rank_deficient): \n";
            double* x = simple_iterations(A_rank_deficient, b_rank_deficient);
            cout << "Итоговый результат (матрица A_rank_deficient): Система имеет бесконечное множество решений \n";
            cout.precision(5);
            for (int i = 0; i < 2; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 6: {
            cout << "Промежуточные вычисления (матрица A_rank_deficient): Система имеет бесконечное множество решений \n";
            double* x = zeidel(A_rank_deficient, b_rank_deficient);
            cout << "Итоговый результат (матрица A_rank_deficient): \n";
            cout.precision(5);
            for (int i = 0; i < 2; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 7: {
            cout << "Промежуточные вычисления: \n";
            double* x = simple_iterations(A3, b3);
            cout << "Итоговый результат: \n";
            cout.precision(5);
            for (int i = 0; i < n; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 8: {
            cout << "Промежуточные вычисления: \n";
            double* x = zeidel(A3, b3);
            cout << "Итоговый результат: \n";
            cout.precision(5);
            for (int i = 0; i < n; i++) {
                cout << x[i] << "\n";
            }
            cout << "\n";
            return 0;
            break;
        }
        case 9: {
            double C[n][n] = { {0.01, 0, -0.02, 0, 0},
                     {0.01, 0.01, -0.02, 0, 0},
                     {0, 0.01, 0.01, 0, -0.02},
                     {0, 0, 0.01, 0.01, 0},
                     {0, 0, 0, 0.01, 0.01} };

            double D[n][n] = { {1.33, 0.21, 0.17, 0.12, -0.13},
                              {-0.13, -1.33, 0.11, 0.17, 0.12},
                              {0.12, -0.13, -1.33, 0.11, 0.17},
                              {0.17, 0.12, -0.13, -1.33, 0.11},
                              {0.11, 0.67, 0.12, -0.13, -1.33} };

            double A[n][n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    A[i][j] = D[i][j] + 13 * C[i][j];

            double b[n] = { 1.2, 2.2, 4.0, 0, -1.2 };

            double** inversed_matrix = new double* [n];
            for (int i = 0; i < n; i++) {
                inversed_matrix[i] = new double[n];
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    inversed_matrix[i][j] = A[i][j];
                }
            }

            // Преобразование статических массивов к указателям
            double* A_ptr[n];
            (double*) inversed_matrix[n];
            for (int i = 0; i < n; i++) {
                A_ptr[i] = A[i];
                inversed_matrix[i] = new double[n];
            }

            Inversion(A_ptr, n);
            std::cout << "Обратная матрица\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << inversed_matrix[i][j] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "Число обусловленности: " << Condition_Number(A_ptr, inversed_matrix, n) << "\n";

            std::cout << "Норма матрицы А: " << NormaSearch(A_ptr, n) << "\n";

            double approx = 0.001 / NormaSearch(A_ptr, n);
            std::cout << "approx: " << approx << "\n";
            double res = Condition_Number(A_ptr, inversed_matrix, n) * approx;
            std::cout << "res: " << res << "\n";

            // Освободите выделенную память для inversed_matrix
            for (int i = 0; i < n; i++) {
                delete[] inversed_matrix[i];
            }
            delete[] inversed_matrix;

            return 0;
            break;
        }
        case 10: {
            return 0;
        }
        }
    }
}
