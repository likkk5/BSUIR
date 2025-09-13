#Task 1
# import numpy as np
# from matplotlib import pyplot as plt
#
# L = 0.32
# du = 0.0015
# E = 97e9
# rho = 67e2
# T = 0.001
#
#
# def solve(N, M, count=0):
#     f = lambda x: (-4 * du / L ** 2) * x ** 2 + (4 * du / L) * x
#
#     tau = T / M
#     h = L / N
#     C = np.sqrt(E / rho) * tau / h
#
#     x_values = np.linspace(0, L, N)
#     matrix = np.zeros((M, N))
#
#     matrix[0] = [f(x) for x in x_values]
#     matrix[1][1:-1] = [f(x_values[i]) * (1 - tau ** 2 / 2) for i in range(1, N - 1)]
#
#     for i in range(1, M - 1):
#         matrix[i + 1][1:-1] = C ** 2 * (matrix[i][2:] - 2 * matrix[i][1:-1] + matrix[i][:-2])
#         matrix[i + 1][1:-1] += 2 * matrix[i][1:-1] - matrix[i - 1][1:-1]
#
#     for i in range(0, M, int(M / count)):
#         plt.plot(x_values, matrix[i])
#         plt.xlabel('x')
#         plt.ylabel('u(x, t)')
#
#     plt.grid()
#     plt.show()
#
#
#
# if __name__ == '__main__':
#     N = 100
#     M = 10000
#     A = solve(N, M, count=25)

import numpy as np
import matplotlib.pyplot as plt

a = 3
b = 2
T = 4

p = lambda x, y: np.tan(np.cos(np.pi * y / a))
q = lambda x, y: np.exp(np.sin(np.pi * x / a)) * np.sin(2 * np.pi * y / b)


def solve(NX, NY, M):
    tau = T / M
    hx = a / NX
    hy = b / NY
    C = tau / hx + tau / hy

    x_values = np.linspace(-a / 2, a / 2, NX)
    y_values = np.linspace(-b / 2, b / 2, NY)
    matrix = np.zeros((M, NX, NY))

    for i in range(NX):
        for j in range(NY):
            matrix[0][i][j] = p(x_values[i], y_values[j])

    for i in range(1, NX - 1):
        for j in range(1, NY - 1):
            matrix[1][i][j] = p(x_values[i], y_values[j]) + q(x_values[i], y_values[j]) * tau
            matrix[1][i][j] += tau ** 2 / (2 * hx ** 2) * (
                        matrix[0][i + 1][j] - 2 * matrix[0][i][j] + matrix[0][i - 1][j])
            matrix[1][i][j] += tau ** 2 / (2 * hy ** 2) * (
                        matrix[0][i][j + 1] - 2 * matrix[0][i][j] + matrix[0][i][j - 1])

    matrix[1, 1:-1, 0] = matrix[1, 1:-1, 1]
    matrix[1, 1:-1, -1] = matrix[1, 1:-1, -2]

    for t in range(1, M - 1):
        matrix[t + 1, 1:-1, 1:-1] = 2 * matrix[t, 1:-1, 1:-1] - matrix[t - 1, 1:-1, 1:-1]
        matrix[t + 1, 1:-1, 1:-1] += tau ** 2 / hx ** 2 * (
                    matrix[t, :-2, 1:-1] - 2 * matrix[t, 1:-1, 1:-1] + matrix[t, 2:, 1:-1])
        matrix[t + 1, 1:-1, 1:-1] += tau ** 2 / hy ** 2 * (
                    matrix[t, 1:-1, :-2] - 2 * matrix[t, 1:-1, 1:-1] + matrix[t, 1:-1, 2:])
        matrix[t + 1, 1:-1, 0] = matrix[t + 1, 1:-1, 1]
        matrix[t + 1, 1:-1, -1] = matrix[t + 1, 1:-1, -2]

    for i in range(0, M, 999):
        x_grid, y_grid = np.meshgrid(x_values, y_values)
        fig = plt.figure(figsize=(10,10))
        ax = plt.axes(projection='3d')
        ax.plot_surface(x_grid, y_grid, matrix[i])
        plt.show()


if __name__ == '__main__':
    solve(100, 100, 4000)