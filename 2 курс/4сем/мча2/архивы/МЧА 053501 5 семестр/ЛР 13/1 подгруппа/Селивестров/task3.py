import numpy as np
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
    
def plot(x, t, A):
    fig = plt.figure()
    ax = fig.gca(projection='3d')

    i_arr = [0, 5, 20, 50, 100, 200]

    for i in i_arr:
        y = [i * tau] * len(x)
        z = matrix[i]
        ax.plot(x, y, z, label=fr't={i}$\tau$')

    plt.legend()
    plt.show()

A = 0.1
B = 0.8
Ua = 6
Ub = 0.6
k = lambda x: x
f = lambda x: x + x ** (1 / 3)

h = 0.1
tau = 0.001
T = 200 * tau

phi_variants = [
    lambda x: 1 - x ** 2,
    lambda x: x ** 3,
    lambda x: np.sin(x)
]

for phi in phi_variants:
    M = int(T / tau) + 1
    N = int((B - A) / h) + 1

    x_values = np.linspace(A, B, N)
    t_values = np.linspace(0, T, M)
    matrix = np.zeros((M, N))
    matrix[:, 0] = Ua
    matrix[:, -1] = Ub
    matrix[0] = [phi(x) for x in x_values]

    for i in range(M - 1):
        for j in range(1, N - 1):                        
            matrix[i + 1][j] = tau * k(x_values[j] - h / 2) / (h ** 2) * matrix[i][j - 1]
            matrix[i + 1][j] += (1 - tau * (k(x_values[j] - h / 2) + k(x_values[j] + h / 2)) / (h ** 2)) * matrix[i][j]
            matrix[i + 1][j] += tau * k(x_values[j] + h / 2) / (h ** 2) * matrix[i][j + 1]
            matrix[i + 1][j] += tau * f(x_values[j]) * (1 - math.exp(-t_values[i]))


    plot(x_values, t_values, A)
