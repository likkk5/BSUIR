import numpy as np
from numpy import linspace
from matplotlib import pyplot as plt
from utils import tridiag_solve, is_accurate, clone

# start data

n = 100
A = 1.2
B = 2.2
e = 7e-2

current = []
total_iterations = 0

while True:
    h = (B - A) / n
    points = list(linspace(A, B, n))

    a = [1 / (h ** 2) + x / (2 * h) for x in points]
    b = [-2 / (h ** 2) + 2 * x for x in points]
    c = [1 / (h ** 2) - x / (2 * h) for x in points]
    d = [2.8 for x in points]

    b[0] = b[0] + a[0] * 4 / (10 * h + 3)
    c[0] = c[0] - a[0] / (10 * h + 3)
    d[0] = d[0] - a[0] * 2 * h / (10 * h + 3)
    a[0] = 0

    a[-1] = a[-1] - c[-1] / 3
    b[-1] = b[-1] + 4 * c[-1] / 3
    d[-1] = d[-1] - c[-1] * 8 * h / 3
    c[-1] = 0

    current = tridiag_solve(a, b, c, d)

    if total_iterations != 0 and is_accurate(current, previous, e):
        break

    previous = clone(current)
    total_iterations += 1
    n *= 2

plt.plot(points, current,  label=f'Numerical solution\nTotal iterations: {total_iterations}\nCurrent step: {h}')
plt.legend()
plt.show()