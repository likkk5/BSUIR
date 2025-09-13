import numpy as np
import math
import methods
k = 7

EPS = 10.0 ** -4

A = methods.input(12)
n = len(A)

ansV = np.eye(n)
while True:
    max_el = (0, 1) # upper main diag.
    for i in range(n):
        for j in range(i + 1, n):
            if (abs(A[i][j]) > abs(A[max_el])):
                max_el = (i, j)
    (i, j) = max_el
    if (A[i][i] == A[j][j]):
        p = np.pi / 4       # aii == ajj
    else:
        p = 2 * A[i][j] / (A[i][i] - A[j][j])
    c = math.cos(1/2 * math.atan(p))
    s = math.sin(1/2 * math.atan(p))
    V = np.eye(n)
    V[i][i] = c
    V[i][j] = -s
    V[j][i] = s
    V[j][j] = c
    A = V.T @ A @ V
    ansV = ansV @ V
    if ((A ** 2).sum() - (np.diag(A) ** 2).sum() < EPS):
        ansW = np.diag(A)
        break


def main():
    np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")

    A = methods.input(12)
    print("A = {0}\n".format(A))

    print("Answer:")
    (W, V) = (ansW, ansV)
    print("Eigenvalue: {0}".format(W))
    print("Columns - eigenvectors:\n {0}\n".format(V))

    print("Check:")
    (W, V) = np.linalg.eig(A)
    print(W)
    print(V)


if __name__ == '__main__':
    main()