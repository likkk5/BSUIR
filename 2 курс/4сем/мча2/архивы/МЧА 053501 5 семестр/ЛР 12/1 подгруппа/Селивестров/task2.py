import numpy as np
from numpy import linspace
from matplotlib import pyplot as plt
from utils import tridiag_solve, is_accurate, clone

# start data

n = 100
A = 1
B = 3
Ya = -1
Yb = 4
e = 5e-2

current = []
total_iterations = 0

while True:
    h = (B - A) / n
    points = list(linspace(A, B, n))

    a = [1 / (h ** 2) - (1 + (np.cos(x) ** 2)) / (2 * h) for x in points]
    b = [-2 / (h ** 2) + (1 + x ** 2) for x in points]
    c = [1 / (h ** 2) + (1 + (np.cos(x) ** 2)) / (2 * h) for x in points]
    d = [(1 + x ** 2) * np.cos(x) for x in points]

    d[0] = d[0] - a[0] * Ya
    d[-1] = d[-1] - c[-1] * Yb

    current = tridiag_solve(a, b, c, d)

    if total_iterations != 0 and is_accurate(current, previous, e):
        break

    previous = clone(current)
    total_iterations += 1
    n *= 2

plt.plot(points, current,  label=f'Numerical solution\nTotal iterations: {total_iterations}\nCurrent step: {h}')
plt.legend()
plt.show()