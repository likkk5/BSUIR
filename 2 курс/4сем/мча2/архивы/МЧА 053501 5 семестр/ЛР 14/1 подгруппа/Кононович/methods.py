import numpy as np
import math
from matplotlib import pyplot as plt
from scipy import integrate
from mpl_toolkits.mplot3d import Axes3D

A = -1
B = 1
k = 0.5
phi = lambda x: 1 - x ** 2
g1 = lambda t: 0
g2 = lambda t: 0
f = lambda x, t: x
T = 0.4

def explicit_method_1(h, tau, build_plot=False):
    M = int(T / tau) + 1
    N = int((B - A) / h) + 1

    x_values = np.linspace(A, B, N)
    t_values = np.linspace(0, tau, M)
    matrix = np.zeros((M, N))
    matrix[0] = [phi(x) for x in x_values]
    matrix[:, 0] = [g1(t) for t in t_values]

    for i in range(M - 1):
        for j in range(1, N - 1):            
            matrix[i + 1][j] = k * tau / h ** 2 * matrix[i][j - 1]
            matrix[i + 1][j] += (1 - 2 * k * tau / h ** 2) * matrix[i][j]
            matrix[i + 1][j] += k * tau / h ** 2 * matrix[i][j + 1]
            matrix[i + 1][j] += tau * f(x_values[j], t_values[i])
            
        matrix[i + 1][-1] = matrix[i + 1][-2] + h * g2(t_values[i])

    if build_plot:
        fig = plt.figure()
        ax = fig.gca(projection='3d')

        for i in range(len(t_values) - 1, -2, -1000):
            x = x_values
            y = [i * tau] * len(x)
            z = matrix[i]
            ax.plot(x, y, z)

        plt.show()

    return matrix

def explicit_method_2(h, tau, build_plot=False):
    M = int(T / tau) + 1
    N = int((B - A) / h) + 1

    x_values = np.linspace(A, B, N)
    t_values = np.linspace(0, tau, M)
    matrix = np.zeros((M, N))
    matrix[0] = [phi(x) for x in x_values]
    matrix[:, 0] = [g1(t) for t in t_values]

    for i in range(M - 1):
        for j in range(1, N - 1):            
            matrix[i + 1][j] = k * tau / h ** 2 * matrix[i][j - 1]
            matrix[i + 1][j] += (1 - 2 * k * tau / h ** 2) * matrix[i][j]
            matrix[i + 1][j] +=  k * tau / h ** 2 * matrix[i][j + 1]
            matrix[i + 1][j] += tau * f(x_values[j], t_values[i])

        matrix[i + 1][-1] = k * tau / h ** 2 * matrix[i][-2]
        matrix[i + 1][-1] += (1 - 2 * k * tau / h ** 2) * matrix[i][-1]
        matrix[i + 1][-1] +=  k * tau / h ** 2 * (2 * h * g2(t_values[i]) + matrix[i + 1][-2])
        matrix[i + 1][-1] += tau * f(x_values[j], t_values[i])

    if build_plot:
        fig = plt.figure()
        ax = fig.gca(projection='3d')

        for i in range(len(t_values) - 1, -2, -1000):
            x = x_values
            y = [i * tau] * len(x)
            z = matrix[i]
            ax.plot(x, y, z)

        plt.show()

    return matrix

def implicit_method_1(h, tau, build_plot=False):
    M = int(T / tau) + 1
    N = int((B - A) / h) + 1

    x_values = np.linspace(A, B, N)
    t_values = np.linspace(0, tau, M)
    result = np.zeros((M, N))
    result[0] = [phi(x) for x in x_values]
    result[:, 0] = [g1(t) for t in t_values]

    matrix = np.zeros((N, N))

    for j in range(1, N - 1):
            matrix[j][j - 1] = - k * tau / h ** 2 
            matrix[j][j] = 1 + 2 * k * tau / h ** 2
            matrix[j][j + 1] = - k * tau / h ** 2
            
    matrix[0][0] = 1
    matrix[-1][-1] = 1
    matrix[-1][-2] = - 1

    for i in range(1, M):
        b = np.array([tau * f(x, t_values[i] + tau) for x in x_values]) + result[i - 1]
        b[0] = g1(t_values[i])
        b[-1] = h * g2(t_values[i])
        result[i] = np.linalg.solve(matrix, b)

    if build_plot:
        fig = plt.figure()
        ax = fig.gca(projection='3d')

        for i in range(len(t_values) - 1, -2, -1000):
            x = x_values
            y = [i * tau] * len(x)
            z = result[i]
            ax.plot(x, y, z)

        plt.show()

    return result

def implicit_method_2(h, tau, build_plot=False):
    M = int(T / tau) + 1
    N = int((B - A) / h) + 1

    x_values = np.linspace(A, B, N)
    t_values = np.linspace(0, tau, M)
    result = np.zeros((M, N))
    result[0] = [phi(x) for x in x_values]
    result[:, 0] = [g1(t) for t in t_values]

    matrix = np.zeros((N + 1, N + 1))

    for j in range(1, N):
            matrix[j][j - 1] = - k * tau / h ** 2 
            matrix[j][j] = 1 + 2 * k * tau / h ** 2
            matrix[j][j + 1] = - k * tau / h ** 2
            
    matrix[0][0] = 1
    matrix[-1][-1] = 1
    matrix[-1][-3] = -1

    for i in range(1, M):
        b = np.zeros(N + 1)
        b[1:-1] = np.array([tau * f(x, t_values[i] + tau) for x in x_values[1:]]) + result[i - 1][1:]
        b[0] = g1(t_values[i])
        b[-1] = 2 * h * g2(t_values[i])
        result[i] = np.linalg.solve(matrix, b)[:-1]

    if build_plot:
        fig = plt.figure()
        ax = fig.gca(projection='3d')

        for i in range(len(t_values) - 1, -2, -1000):
            x = x_values
            y = [i * tau] * len(x)
            z = result[i]
            ax.plot(x, y, z)
        
        plt.show()

    return result