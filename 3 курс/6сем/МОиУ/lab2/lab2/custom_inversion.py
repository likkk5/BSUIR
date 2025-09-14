import numpy as np

def modify_inverse_matrix(A_inv, x, i):
    # Преобразуем x в столбец (если это не так)
    x = x.reshape(-1, 1) if x.ndim == 1 else x
    
    # Шаг 1: Вычисляем l(матричное умножение)
    l = np.dot(A_inv, x)
    
    # Если i-ый элемент l равен 0, модифицированная матрица не обратима
    if l[i, 0] == 0:
        print("\nMatrix A with hat is not invertible")
        return None
    
    # Шаг 2: Создаем l_tilde (копия l с заменой i-го элемента на -1)
    l_tilde = l.copy()
    l_tilde[i, 0] = -1
    
    # Шаг 3: Вычисляем l_hat
    l_hat = (-1 / l[i, 0]) * l_tilde
    
    # Шаг 4: Создаем матрицу Q
    Q = np.eye(A_inv.shape[0])
    Q[:, i:i+1] = l_hat  # Заменяем i-ый столбец на l_hat
    
    # Шаг 5: Вычисляем A_inv_hat
    A_inv_hat = A_inv.astype(float).copy()
    rows, cols = A_inv.shape
    for row in range(rows):
        for col in range(cols):
            if row == i:
                el_row = Q[row][row] * A_inv[row][col]
            else:
                el_row = Q[row][row] * A_inv[row][col] + Q[row][i] * A_inv[i][col]
            A_inv_hat[row][col] = el_row
    
    return A_inv_hat
