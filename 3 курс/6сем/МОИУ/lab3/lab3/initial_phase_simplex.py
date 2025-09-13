import numpy as np
from simplex_method import simplex_method

def initial_phase_simplex(c, A, b):
    rows, cols = A.shape  # Получаем размерности матрицы A
    
    # 1) Преобразуем ограничения с отрицательными правыми частями
    for i in range(rows):
        if b[i] < 0:  
            b[i] *= -1  
            A[i, :] *= -1 
    
    # 2) Формируем вспомогательную задачу
    # объединяет массивы вдоль горизонтальной оси (по столбцам).
    c_auxiliary = np.hstack([np.zeros(cols), -np.ones(rows)])  # Целевая функция для вспомогательной задачи: первые n элементов равны 0 (для исходных переменных), а последние m элементов равны -1 (для искусственных переменных)
    A_auxiliary = np.hstack([A, np.eye(rows)])  # добавляем единичную матрицу (для искусственных переменных)
    x_auxiliary = np.hstack([np.zeros(cols), b.flatten()])  # Вектор переменных для вспомогательной задачи(flatten-делает одномерным)
    basis_indices = list(range(cols, cols + rows))  # Индексы базисных переменных (искусственные переменные)

    # 3) Решаем вспомогательную задачу с помощью симплекс-метода и возвращает оптимальное решение и базиснве индексы
    x_cap, basis_indices = simplex_method(c_auxiliary, x_auxiliary, A_auxiliary, basis_indices)
    
    # 4) Проверка совместности задачи
    if np.any(x_cap[cols:] != 0):  # Если хотя бы одна искусственная переменная не равна нулю
        return None, None  # Задача несовместна
    
    # 5) Формируем допустимый план x для исходной задачи
    x_solution = x_cap[:cols]  # Переменные исходной задачи - это первые n значений из x_cap
    
    # 6) Корректировка множества basis_indices, чтобы исключить искусственные переменные. цикл идет пока в базисных индексах есть индексы=искусственным переменным
    while any(j >= cols for j in basis_indices): 
        max_index = max(j for j in basis_indices if j >= cols)  # Находим максимальный индекс среди искусственных переменных
        row_index = max_index - cols  # Вычисляем строку, которая соответствует этой искусственной переменной
        
        # 7) Вычисляем вектор ℓ(j) для каждого неосновного индекса j
        A_B_inv = np.linalg.inv(A_auxiliary[:, basis_indices])  # Обратная матрица для подматрицы A, составленной из базисных переменных
        
        for j in range(cols):  # Для каждого неосновного индекса j
            if j not in basis_indices: 
                ell_j = A_B_inv @ A_auxiliary[:, j]  # Вычисляем вектор
                if ell_j[row_index] != 0:  # Если ℓ(j) на позиции row_index не равна 0
                    basis_indices[basis_indices.index(max_index)] = j  # Заменяем искусственную переменную на переменную задачи
                    break
        else:
            # 9) Если не нашли подходящий индекс для замены, то удаляем избыточное ограничение
            A = np.delete(A, row_index, axis=0) 
            b = np.delete(b, row_index)  
            A_auxiliary = np.delete(A_auxiliary, row_index, axis=0) 
            basis_indices.remove(max_index) 
    
    return x_solution, basis_indices
