from custom_inversion import modify_inverse_matrix
import numpy as np

def simplex_method(cost_vector, solution, constraint_matrix, basis_indices):
    num_constraints, num_vars = constraint_matrix.shape # возвращаются в виде (количество ограничений (количество строк в A), количество переменных (количество столбцов в A))
    basis_indices = list(basis_indices)  # Упорядоченный список индексов базисных переменных

    # Шаг 1: Формирование базисной матрицы A_B (матрица ограничений для базисных переменных) и ее обратной A_B_inv
    basis_matrix = constraint_matrix[:, basis_indices]
    basis_matrix_inv = np.linalg.inv(basis_matrix)
    
    while True:
        # Шаг 2: Вычисляем вектор коэффициентов для базисных переменных
        basis_costs = cost_vector[basis_indices] # Из cost_vector выбираем только базисные переменные
        
        # Шаг 3: Вычисляем вектор потенциалов (u^T = c_B^T * A_B_inv)
        potentials = basis_costs @ basis_matrix_inv #@ для умножения матриц и векторов
        
        # Шаг 4: Находим вектор относительных оценок Δ (Δ = u^T * A - c)
        reduced_costs = potentials @ constraint_matrix - cost_vector
        
        # Шаг 5: Проверяем все условия, достигнуто ли оптимальное решение (все Δ >= 0)
        if np.all(reduced_costs >= 0):
            return solution  # Оптимальный план найден
        
        # Шаг 6: Определяем индекс входящей переменной (первая отрицательная оценка в Δ)
        entering_index = np.where(reduced_costs < 0)[0][0]
        
        # Шаг 7: Вычисляем вектор направления (столбец A_j0 из матрицы A_B_inv * A)
        direction_vector = basis_matrix_inv @ constraint_matrix[:, entering_index]
        
        # Шаг 8: Рассчитываем значения θ (для проверки выхода из базиса)
        # Создает массив той же формы, что и direction_vector, но заполняет его ∞.
        theta_values = np.full_like(direction_vector, np.inf, dtype=float) # Изначально все значения θ = ∞
        positive_mask = direction_vector > 0
        theta_values[positive_mask] = solution[basis_indices][positive_mask] / direction_vector[positive_mask]  # Вычисляем θ только там, где direction_vector > 0 (чтобы избежать деления на 0 или отрицательное число)
        
        # Шаг 9: Определяем и возвращаем минимальное θ(θ0)
        min_theta = np.min(theta_values)
        
        # Шаг 10: Проверяем на неограниченность функции (если min_theta остался ∞). inf представление бесконечности
        if min_theta == np.inf:
            return "Целевая функция не ограничена сверху на множестве допустимых планов\n"
        
        # Шаг 11: Определяем индекс выходящей переменной (переменная, у которой θ минимально)
        leaving_index_position = np.where(theta_values == min_theta)[0][0] # Берем первый индекс, где θ = min_theta
        leaving_index = basis_indices[leaving_index_position]
        
        # Шаг 12: Обновляем базисные индексы: заменяем переменную, которая выходит, на входящую переменную
        basis_indices[leaving_index_position] = entering_index
        
        # Шаг 13: Обновляем вектор решения х
        solution[entering_index] = min_theta
        for i in range(num_constraints):
            if i != leaving_index_position:
                solution[basis_indices[i]] -= min_theta * direction_vector[i]
        solution[leaving_index] = 0

        # Обновляем обратную матрицу базиса с помощью метода из ЛР1
        basis_matrix_inv = modify_inverse_matrix(basis_matrix_inv, constraint_matrix[:, entering_index], leaving_index_position)
        if basis_matrix_inv is None:  # Если модификация не удалась
            return "Целевая функция не ограничена сверху на множестве допустимых планов\n"

if __name__ == "__main__":
    # Исходные данные
    cost_vector = np.array([1, 1, 0, 0, 0], dtype=float) # Коэффициенты целевой функции
    initial_solution = np.array([0, 0, 1, 3, 2], dtype=float) # Начальное базисное решение
    constraint_matrix = np.array([
        [-1, 1, 1, 0, 0],
        [1, 0, 0, 1, 0],
        [0, 1, 0, 0, 1]
    ], dtype=float)
    basis_indices = np.array([2, 3, 4])  # Индексы базисных переменных

    # Запуск симплекс-метода
    optimal_solution = simplex_method(cost_vector, initial_solution, constraint_matrix, basis_indices)
    print("Результат симплекс-метода:", optimal_solution)

    # Второй тест (случай, когда функция неограничена сверху)
    cost_vector_unbounded = np.array([1, 0], dtype=float) # Коэффициенты целевой функции
    initial_solution_unbounded = np.array([1, 0], dtype=float) # Начальное базисное решение
    constraint_matrix_unbounded = np.array([[1, -1]], dtype=float) # Единственное ограничение
    basis_indices_unbounded = np.array([1])  # Базисный индекс

    # Запуск симплекс-метода
    result_unbounded = simplex_method(cost_vector_unbounded, initial_solution_unbounded, constraint_matrix_unbounded, basis_indices_unbounded)
    print("\nРезультат симплекс-метода:", result_unbounded)
