import numpy as np
from numpy import linspace
from matplotlib import pyplot as plt
from utils import tridiag_solve, is_accurate, clone

# start data

n = 100
A = -1
B = 1
Ya = 0
Yb = 0
e = 1e-3

current = []
total_iterations = 0

while True:
    h = (B - A) / n
    points = list(linspace(A, B, n))

    a = [1 for x in points]
    b = [(h ** 2 * (1 + np.cos(8) * x ** 2) - 2 * np.sin(8)) / np.sin(8) for x in points]
    c = [1 for x in points]
    d = [-(h ** 2) for x in points]

    d[0] = d[0] - a[0] * Ya
    d[-1] = d[-1] - c[-1] * Yb

    current = tridiag_solve(a, b, c, d)

    if total_iterations != 0 and is_accurate(current, previous, e):
        break

    previous = clone(current)
    total_iterations += 1
    n *= 2

plt.plot(points, current,  label=f'Total iterations: {total_iterations}\nCurrent step: {h}')
plt.legend()
plt.show()

