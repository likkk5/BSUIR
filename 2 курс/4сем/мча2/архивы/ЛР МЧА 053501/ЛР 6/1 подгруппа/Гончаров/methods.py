import numpy as np


def input():

    x = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
    k = 7
    m = 3.5
    y = [ (p[i] + ((-1) ** k) * m) for i in range(len(x))]
    dots = list(zip(x, y))

    return dots


def Lagrange(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))
    polynom = np.poly1d([0])
    for i in range(n):
        p = np.poly1d([1])
        for j in range(n):
            if j != i:
                p *= np.poly1d([ 1, -x[j] ]) / (x[i] - x[j])
        polynom += y[i] * p
    return polynom


def DividedDifferences(xs):
    n = len(xs)
    diffs = [[None for j in range(n - i)] for i in range(n)]
    for i in range(n):
        diffs[i][0] = y[i]
    for j in range(1, n):
        for i in range(n - j):
            diffs[i][j] = ((diffs[i][j - 1] - diffs[i + 1][j - 1]) / (xs[i] - xs[i + j]))
    return diffs