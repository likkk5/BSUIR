import numpy as np
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
    
def plot(x, t, A):
    fig = plt.figure()
    ax = fig.gca(projection='3d')

    for i in range(len(t) - 1, -1, -2):
        y = [i * tau] * len(x)
        z = A[i]
        ax.plot(x, y, z, label=fr't={i}$\tau$')

    plt.legend()
    plt.show()


A = -1
B = 1
k = 0.5
phi = lambda x: 1 - x ** 2
g1 = lambda t: 0
g2 = lambda t: 0
f = lambda x, t: x

h = (B - A) / 10
tau = 0.2 * (h ** 2) / k 
T = 0.4

M = int(T / tau) + 1
N = int((B - A) / h) + 1

x_values = np.linspace(A, B, N)
t_values = np.linspace(0, T, M)
matrix = np.zeros((M, N))
matrix[0] = [phi(x) for x in x_values]
matrix[:, 0] = np.array([g1(ti) for ti in np.linspace(0, T, M)])
matrix[:, -1] = np.array([g2(ti) for ti in np.linspace(0, T, M)])

for i in range(M - 1):
    for j in range(1, N - 1):                    
        matrix[i + 1][j] = k * tau / h ** 2 * matrix[i][j - 1]
        matrix[i + 1][j] += (1 - 2 * k * tau / h ** 2) * matrix[i][j]
        matrix[i + 1][j] += k * tau / h ** 2 * matrix[i][j + 1]
        matrix[i + 1][j] += tau * f(x_values[j], t_values[i])


plot(x_values, t_values, matrix)
