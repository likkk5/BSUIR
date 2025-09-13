import numpy as np
from numpy import linalg
import math

def main():
    epsilon = 0.0001
    matrix_a = get_matrix_a()
    print(f"Matrix a\n{matrix_a}\n")
    (value_matrix, vector_matrix) = eigen(matrix_a, epsilon)
    print_result(value_matrix, vector_matrix)
    numpy_eig(matrix_a)

    test1 = np.array([
            [2.2, 1.0, 0.5, 2.0],
            [1.0, 1.3, 2.0, 1.0],
            [0.5, 2.0, 0.5, 1.6],
            [2.0, 1.0, 1.6, 2.0]
    ])
    print(f"Test1\n{test1}\n")
    (value_matrix, vector_matrix) = eigen(test1, epsilon)
    print_result(value_matrix, vector_matrix)
    numpy_eig(test1)

    test2 = np.array([
            [2, 1, -2],
            [1, 0, 3],
            [-2, 3, -4]
    ], dtype = float)
    print(f"Test2\n{test2}\n")
    (value_matrix, vector_matrix) = eigen(test2, epsilon)
    print_result(value_matrix, vector_matrix)
    numpy_eig(test2)

    test3 = np.array([
            [1, 2, -1],
            [2, 5, -4],
            [-1, -4, -7]
    ], dtype = float)
    print(f"Test3\n{test3}\n")
    (value_matrix, vector_matrix) = eigen(test3, epsilon)
    print_result(value_matrix, vector_matrix)
    numpy_eig(test3)


def get_matrix_a():
    k = 6
    matrix_c = np.array([
            [0.2, 0, 0.2, 0, 0],
            [0, 0.2, 0, 0.2, 0],
            [0.2, 0, 0.2, 0, 0.2],
            [0, 0.2, 0, 0.2, 0],
            [0, 0, 0.2, 0, 0.2]
    ])
    matrix_d = np.array([
            [2.33, 0.81, 0.67, 0.92, -0.53],
            [0.81, 2.33, 0.81, 0.67, 0.92],
            [0.67, 0.81, 2.33, 0.81, 0.92],
            [0.92, 0.67, 0.81, 2.33, -0.53],
            [-0.53, 0.92, 0.92, -0.53, 2.33]
    ])
    return k*matrix_c + matrix_d

def numpy_eig(matrix):
    eigen = linalg.eig(matrix)
    print("\nПроверка средствами numpy")
    print(f"Собственные значения\n{eigen[0]}")
    print(f"Собственные векторы\n{eigen[1]}")

def print_result(value_matrix, vector_matrix):
    n = len(value_matrix)
    values = [value_matrix[i][i] for i in range(n)]
    print(f"Собственные значения\n{values}")
    print(f"Собственные векторы\n{vector_matrix}")

def eigen(matrix, eps):
    A = matrix.copy()
    n = len(matrix)
    vector_matrix = np.eye(n)
    if n < 2:
        return
    iter = 0
    while True:
        max_i = 0
        max_j = 1
        for i in range(n):
            for j in range(i+1, n):
                if (abs(A[i][j]) > abs(A[max_i][max_j])):
                    max_i = i
                    max_j = j
        if A[max_i][max_i] - A[max_j][max_j] == 0:
            angle = np.pi / 4
        else:
            angle = 0.5 * math.atan(2 * A[max_i][max_j] / (A[max_j][max_j]-A[max_i][max_i]))
        s = np.sin(angle)
        c = np.cos(angle)

        U = np.eye(n)
        U[max_i][max_i] = U[max_j][max_j] = c
        U[max_i][max_j] = s
        U[max_j][max_i] = -s
        A = U.T @ A @ U
        vector_matrix = vector_matrix @ U
        if get_sum(A) < eps:
            break
    return (A, vector_matrix)

def get_sum(matrix):
    n = len(matrix)
    sum = 0
    for i in range(n):
        for j in range(n):
            if i != j:
                sum += matrix[i][j]**2
    return sum


if __name__ == '__main__':
    main()