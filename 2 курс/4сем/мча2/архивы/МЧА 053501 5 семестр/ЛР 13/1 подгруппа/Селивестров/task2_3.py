import numpy as np
from numpy import linspace
from matplotlib import pyplot as plt
from utils import tridiag_solve
from scipy import integrate

def get_c(x1, x2, k_x):
    return (integrate.quad(lambda x: 1 / k_x, x1, x2)[0]) ** (-1)

def get_phi(x, x0, c):
    if abs(x - x0) - h / 2 < 1e-5:
        return c / 2
    elif abs(x - x0) < h/2:
        return c

    return 0    

n = 150
A = 0.1
B = 0.8
Ua = 6
Ub = 0.6

k_x = lambda x: x

f_args_variants = [
    [[(1, A + (B - A) / 2)], 'a'],
    [[(2, A + (B - A) / 4), (2, A + 3 * (B - A) / 4)], 'б'],
    [[(2, A + (B - A) / 4), (4, A + 3 * (B - A) / 4)], 'в'],
    [[(5, A + (B - A) / 2), (5, (3 * A + B) / 4)], 'г']
]

f = lambda x: x + x ** (1 / 3)

for f_args_variant, name in f_args_variants: 
    result = []
    h = (B - A) / n
    points = list(linspace(A, B, n))

    a = []
    b = []
    c = []
    d = []

    for i in range(1, n - 1):
        a.append(get_c(points[i - 1], points[i], k_x(points[i])))
        b.append(-get_c(points[i - 1], points[i], k_x(points[i])) - get_c(points[i], points[i + 1], k_x(points[i + 1])))
        c.append(get_c(points[i], points[i + 1], k_x(points[i + 1])))
        d.append(-sum(get_phi(points[i], x0, c) for c, x0 in f_args_variant))

    d[0] = d[0] - a[0] * Ua
    d[-1] = d[-1] - c[-1] * Ub
    a[0] = 0
    c[-1] = 0

    result = tridiag_solve(a, b, c, d)
    result.insert(0, Ua)
    result.append(Ub)

    plt.plot(points, result, label=f'Set {name}')

plt.legend()
plt.show()