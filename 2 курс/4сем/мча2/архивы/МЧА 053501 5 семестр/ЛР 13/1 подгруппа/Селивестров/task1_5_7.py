import numpy as np
from numpy import linspace
from matplotlib import pyplot as plt
from utils import tridiag_solve
from scipy import integrate

def get_c(x1, x2, k_x):
    return (integrate.quad(lambda x: 1 / k_x(x), x1, x2)[0]) ** (-1)

def get_phi(x1, x2):
    return integrate.quad(f, x1, x2)[0]

n = 100
A = 0.1
B = 0.8
Ua = 6
Ub = 0.6

u_variants = [
    [-6, 0.6, 5],
    [6, -0.6, 6],
    [-6, -0.6, 7]
]

k_x = lambda x: x
f = lambda x: x + x ** (1 / 3)

for Ua, Ub, number in u_variants:
    result = []

    h = (B - A) / n
    points = list(linspace(A, B, n))

    a = []
    b = []
    c = []
    d = []
    
    for i in range(1, n - 1):
        a.append(get_c(points[i - 1], points[i], k_x))
        b.append(-get_c(points[i - 1], points[i], k_x) - get_c(points[i], points[i + 1], k_x))
        c.append(get_c(points[i], points[i + 1], k_x))
        d.append(-get_phi(points[i] - h / 2, points[i] + h / 2))

    d[0] = d[0] - a[0] * Ua
    d[-1] = d[-1] - c[-1] * Ub
    a[0] = 0
    c[-1] = 0

    result = tridiag_solve(a, b, c, d)
    result.insert(0, Ua)
    result.append(Ub)

    plt.plot(points, result, label=f'Set #{number}')

plt.legend()
plt.show()