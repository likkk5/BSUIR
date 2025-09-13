import numpy as np
import chart_studio.plotly as py
import plotly.graph_objs as graph_objs
import plotly
import time
import matplotlib as plt
from matplotlib import pyplot as pl
from matplotlib import cm
from matplotlib.animation import FuncAnimation

# var (5)
plt.use('TkAgg')


def main():
    N = 100
    M = 10000
    A = task1(N, M, build_plot=True, count=15)

    task2(100, 100, 4000, build_plot=True)


def task1(N, M, build_plot=False, count=0):
    L = 0.25
    du = 0.002
    E = 120e9
    rho = 74e2
    T = 0.001

    f = lambda x: (-4 * du / L ** 2) * x ** 2 + (4 * du / L) * x

    tau = T / M
    h = L / N
    C = np.sqrt(E / rho) * tau / h

    x_values = np.linspace(0, L, N)
    y_values = np.linspace(0, T, M)
    matrix = np.zeros((M, N))

    matrix[0] = [f(x) for x in x_values]
    matrix[1][1:-1] = [f(x_values[i]) * (1 - tau ** 2 / 2) for i in range(1, N - 1)]

    for i in range(1, M - 1):
        matrix[i + 1][1:-1] = C ** 2 * (matrix[i][2:] - 2 * matrix[i][1:-1] + matrix[i][:-2])
        matrix[i + 1][1:-1] += 2 * matrix[i][1:-1] - matrix[i - 1][1:-1]

    if build_plot:
        def plot_3d():
            fig = pl.figure()
            ax = fig.add_subplot(projection='3d')

            X, Y = np.meshgrid(x_values, y_values)
            surf = ax.plot_surface(X, Y, matrix, cmap=cm.coolwarm,
                                   linewidth=0, antialiased=False)
            pl.show()

        plot_3d()


def task2(NX, NY, M, build_plot=False):
    a = 3
    b = 1
    T = 10
    p = lambda x, y: 2 * np.cos(np.pi * x / a)
    q = lambda x, y: np.tan(np.sin(2 * np.pi * x / a)) * np.sin(np.pi * y / b)
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

    pl.ion()

    fig = pl.figure()
    ax = fig.add_subplot(projection='3d')
    X, Y = np.meshgrid(x_values, y_values)
    surf = ax.plot_surface(X, Y, matrix[0],
                           rstride=5,
                           cstride=5,
                           cmap='seismic',
                           alpha=1,
                           linewidth=0,
                           antialiased=True,
                           vmin=np.min(matrix[0]),
                           vmax=np.max(matrix[0]))
    print('change')

    for i in range(0, M, 100):
        # pl.clf()
        X, Y = np.meshgrid(x_values, y_values)
        surf = ax.plot_surface(X, Y, matrix[i])
        print('changed', i)
        pl.draw()
        pl.gcf().canvas.flush_events()

    pl.ioff()
    pl.show()


if __name__ == "__main__":
    main()
