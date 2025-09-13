import numpy as np

def find_value():
    A = np.array([
        [ 3.93,  0.81,  2.27,  0.92, -0.53],
        [ 0.81,  3.93,  0.81,  2.27,  0.92],
        [ 2.27,  0.81,  3.93,  0.81,  2.52],
        [ 0.92,  2.27,  0.81,  3.93, -0.53],
        [-0.53,  0.92,  2.52, -0.53,  3.93]
    ])
    V2 = np.eye(len(A)) 
    while True:
        max = (0, 1)
        for i in range(len(A)):
            for j in range(i + 1, len(A)):
                if abs(A[i][j]) > abs(A[max]):
                    max = (i, j) 
        (i, j) = max
        if A[i][i] == A[j][j]: 
            p = np.pi / 4
        else:
            p = 2 * A[i][j] / (A[i][i] - A[j][j]) 
        V = np.eye(len(A))
        V[i][i] = np.cos(1 / 2 * np.arctan(p))
        V[i][j] = -np.sin(1 / 2 * np.arctan(p))
        V[j][i] = np.sin(1 / 2 * np.arctan(p))
        V[j][j] = np.cos(1 / 2 * np.arctan(p))
        A = V.T @ A @ V
        V2 = V2 @ V
        if (A ** 2).sum() - (np.diag(A) ** 2).sum() < 10.0 ** -9: 
            W2 = np.diag(A)
            break
    np.set_printoptions(precision=4) 
    return V2, W2

if __name__ == "__main__":  
    print("A:")
    A = np.array([
        [ 3.93,  0.81,  2.27,  0.92, -0.53],
        [ 0.81,  3.93,  0.81,  2.27,  0.92],
        [ 2.27,  0.81,  3.93,  0.81,  2.52],
        [ 0.92,  2.27,  0.81,  3.93, -0.53],
        [-0.53,  0.92,  2.52, -0.53,  3.93]
    ])
    print(A)
    (W, V) = find_value()
    print("Столбцы - собственные векторы:") 
    print(W)
    print("Вектор собственных значений:") 
    print(V)