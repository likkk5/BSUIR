import numpy as np

def modify_inverse_matrix(A_inv, x, i):
    # ����������� x � ������� (���� ��� �� ���)
    x = x.reshape(-1, 1) if x.ndim == 1 else x
    
    # ��� 1: ��������� l(��������� ���������)
    l = np.dot(A_inv, x)
    
    # ���� i-�� ������� l ����� 0, ���������������� ������� �� ��������
    if l[i, 0] == 0:
        print("\nMatrix A with hat is not invertible")
        return None
    
    # ��� 2: ������� l_tilde (����� l � ������� i-�� �������� �� -1)
    l_tilde = l.copy()
    l_tilde[i, 0] = -1
    
    # ��� 3: ��������� l_hat
    l_hat = (-1 / l[i, 0]) * l_tilde
    
    # ��� 4: ������� ������� Q
    Q = np.eye(A_inv.shape[0])
    Q[:, i:i+1] = l_hat  # �������� i-�� ������� �� l_hat
    
    # ��� 5: ��������� A_inv_hat
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
