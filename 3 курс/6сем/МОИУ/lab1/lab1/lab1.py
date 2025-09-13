# -*- coding: utf-8 -*-

import numpy as np 

def modify_inverse_matrix(A_inv, x, i):
    """
    Обновляет обратную матрицу A_inv после модификации i-й строки исходной матрицы A.
    
    :param A_inv: np.array, обратная матрица A^-1
    :param x: np.array, новый столбец x, заменяющий i-ю строку
    :param i: int, индекс строки, которая изменяется
    :return: np.array, обновленная обратная матрица A^-1 с шапкой
    """
    # Шаг 1: Вычисляем вспомогательный вектор l
    l = np.dot(A_inv, x)  
    
    # Если i-й элемент l равен 0, матрица необратима
    if l[i, 0] == 0:
        print(f"\nПример {idx + 1}: Матрица A с модификацией необратима")
        return None
    
    # Шаг 2: Создаем l_tilde (копируем l и заменяем i-й элемент на -1)
    l_tilde = l.copy()
    l_tilde[i, 0] = -1  
    
    # Шаг 3: Вычисляем l_hat
    l_hat = (-1 / l[i, 0]) * l_tilde  
    
    # Шаг 4: Создаем вспомогательную матрицу Q
    Q = np.eye(A_inv.shape[0])
    Q[:, i:i+1] = l_hat  # Заменяем i-й столбец на l_hat
    
    # Шаг 5: Вычисляем обновленную обратную матрицу A_inv_hat
    A_inv_hat = A_inv.astype(float).copy()
    rows, cols = A_inv.shape
    for row in range(rows):
        for col in range(cols):
            if row == i:
                A_inv_hat[row, col] = Q[row, row] * A_inv[row, col]
            else:
                A_inv_hat[row, col] = Q[row, row] * A_inv[row, col] + Q[row, i] * A_inv[i, col]
    
    return A_inv_hat

# Примеры использования
examples = [
    (np.array([[1, 1, 0], [0, 1, 0], [0, 0, 1]]), np.array([[1], [0], [1]]), 2),
    (np.array([[-24, 20, -5], [18, -15, 4], [5, -4, 1]]), np.array([[2], [2], [2]]), 1),
    (np.array([[1, 1, 0], [0, 1, 0], [0, 0, 1]]), np.array([[1], [0], [1]]), 1)
]

for idx, (A_inv, x, i) in enumerate(examples):
    result = modify_inverse_matrix(A_inv, x, i)
    if result is not None:
        print(f"\nПример {idx + 1}: Обновленная обратная матрица A^-1 с шапкой:")
        print(" -                            -")
        for row in result:
            print("|", "  ".join(f"{elem:8.4f}" for elem in row), "|")
        print(" -                            -")
