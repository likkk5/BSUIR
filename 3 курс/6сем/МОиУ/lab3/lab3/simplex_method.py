import numpy as np
from custom_inversion import modify_inverse_matrix

def simplex_method(c, x, A, B):
    m, n = A.shape
    B = list(B)  # Упорядоченный список базисных индексов

    # Шаг 1: Формируем базисную матрицу A_B и находим A_B_inv
    A_B = A[:, B]
    A_B_inv = np.linalg.inv(A_B)
    
    while True:
        # Шаг 2: Формируем вектор c_B
        c_B = c[B]
        
        # Шаг 3: Находим вектор потенциалов u^T
        u_T = c_B @ A_B_inv
        
        # Шаг 4: Находим вектор оценок Δ^T
        delta_T = u_T @ A - c
        
        # Шаг 5: Проверяем условие оптимальности
        if np.all(delta_T >= 0):
            return x, B  # Оптимальный план найден
        
        # Шаг 6: Определяем индекс j0 первой отрицательной компоненты delta_T
        j0 = np.where(delta_T < 0)[0][0]
        
        # Шаг 7: Вычисляем вектор z
        A_j0 = A[:, j0]
        z = A_B_inv @ A_j0
        
        # Шаг 8: Вычисляем вектор θ
        theta = np.full_like(z, np.inf)  # Заполняем θ бесконечностями
        mask = z > 0  # Определяем элементы, для которых можно делить
        theta[mask] = x[B][mask] / z[mask]  # Делим только там, где z > 0
        
        # Шаг 9: Вычисляем θ0
        theta0 = np.min(theta)
        
        # Шаг 10: Проверяем неограниченность целевой функции
        if theta0 == np.inf:
            return "Целевая функция не ограничена сверху на множестве допустимых планов\n"
        
        # Шаг 11: Находим индекс j*, где достигается минимум θ0
        k = np.where(theta == theta0)[0][0]
        j_star = B[k]
        
        # Шаг 12: Обновляем базисный индекс
        B[k] = j0
        
        # Шаг 13: Обновляем x
        x[j0] = theta0
        for i in range(m):
            if i != k:
                x[B[i]] -= theta0 * z[i]
        x[j_star] = 0

        # Обновляем A_B_inv с помощью функции modify_inverse_matrix
        A_B_inv = modify_inverse_matrix(A_B_inv, A_j0, k)
        if A_B_inv is None:
            return "Целевая функция не ограничена сверху на множестве допустимых планов\n"