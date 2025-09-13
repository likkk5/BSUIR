import numpy as np
from numpy import linspace
from matplotlib import pyplot as plt
from utils import tridiag_solve, is_accurate, clone

# start data

n = 100
A = 0
B = 3
C = 1.875
k1 = 1.5
k2 = 0.6
q1 = 8.3
q2 = 12

e = 1e-3

current = []
total_iterations = 0

while True:
    h = (B - A) / n
    points = list(linspace(A, B, n))

    a = [1 / (h ** 2) for x in points[1:-1]]
    b = [-2 / (h ** 2) - q1 / k1 if x < C else -2 / (h ** 2) - q2 / k2 for x in points[1:-1]]
    c = [1 / (h ** 2) for x in points[1:-1]]
    d = [7 * np.exp(-0.5 * x) / k1 if x < C else 7 * np.exp(-0.5 * x) / k2 for x in points[1:-1]]

    a.insert(0, 0)
    b.insert(0, k1 / h + 0.5)
    c.insert(0, -k1 / h)
    d.insert(0, 0)

    a.append(-k2 / h)
    b.append(k2 / h + 0.5)
    c.append(0)
    d.append(0)

    current = tridiag_solve(a, b, c, d)

    if total_iterations != 0 and is_accurate(current, previous, e):
        break

    previous = clone(current)
    total_iterations += 1
    n *= 2

plt.plot(points, current,  label=f'Numerical solution\nTotal iterations: {total_iterations}\nCurrent step: {h}')
plt.legend()
plt.show()