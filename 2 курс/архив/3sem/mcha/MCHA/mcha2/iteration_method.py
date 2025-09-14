from tools import *


def iteration_method(matrix_a, answers_b, error=0.0001, verbose=0):
    A, b = np.array(matrix_a, dtype=float), np.array(answers_b, dtype=float)
    ar_size = len(A)
    A, B = check_zeros_diag(A), np.empty(shape=A.shape)
    for i in range(ar_size):
        for j in range(ar_size):
            if i == j:
                B[i, j] = 0
            else:
                B[i, j] = (-1) * A[i, j] / A[i, i]
    c = np.empty(shape=b.shape[0])
    for i in range(len(c)):
        c[i] = b[i] / A[i, i]
    c = c.reshape((ar_size, 1))
    if check_convergence(B):
        if verbose == 1:
            print('X solution converges by spectrum')
    elif norm_convergence(B):
        if verbose == 1:
            print('X solution converges by its norm')
    else:
        raise Exception("Can't find roots, bcs not converges")
    errors_x = np.empty(shape=ar_size)
    e = 1
    x_current = c.copy()
    iteration = 0
    while e > error:
        iteration += 1
        x_prev = x_current.copy()
        for i in range(ar_size):
            x_current[i] = c[i]
            for j in range(ar_size):
                x_current[i][0] += B[i, j] * x_prev[j][0]
        for i in range(ar_size):         # calculate error
            errors_x[i] = abs(x_prev[i][0] - x_current[i][0])
        errors_y = abs(A.dot(x_current).reshape(ar_size, ) - b)
        e = np.amax(errors_x) + np.amax(errors_y)
    return x_current, iteration
