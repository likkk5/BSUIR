from tools import *


def zeidels_method(matrix_a, answers_b, error=0.0001, verbose=0):
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
    x_current, e = np.zeros(shape=c.shape, dtype=float), 1
    x_current[0, 0] = c[0, 0]
    iteration = 0
    while e > error:
        iteration += 1
        error_x = 0  # set big value for error
        for i in range(ar_size):
            x_prev = x_current[i, 0]  # save prev to calc error
            x_current[i, 0] = c[i, 0]
            for j in range(ar_size):
                x_current[i][0] += B[i, j] * x_current[j][0]
            if abs(x_prev - x_current[i, 0]) > error_x:
                error_x = abs(x_prev - x_current[i, 0])
        errors_y = abs(A.dot(x_current).reshape((ar_size,)) - b)
        e = (np.amax(errors_y) + error_x) / 2
    return x_current, iteration
