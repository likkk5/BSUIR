import numpy as np
from matplotlib import pyplot as plt
import plotly.graph_objs as graph_objs
import plotly

A = 150
B = 90
R = 45
h = 6
P = 65
E = 140
v = 0.28
eps = 0.001
D = 10 * E * h ** 3 / (12 * (1 - v ** 2))

def solve(eps, step, build_plot=False):
    x_values = np.arange(0, A + step, step)
    y_values = np.arange(0, B + step, step)

    N = len(x_values)
    M = len(y_values)

    matrix = np.zeros((M, N))
    current_err = 1
    iterations = 0

    while current_err > eps:
        current_err = 0
        iterations += 1

        for i in range(1, M - 1):
            for j in range(1, N - 1):
                if np.sqrt((A / 2 - step * j) ** 2 + (i * step) ** 2) > R:
                    prev = matrix[i][j]
                    matrix[i][j] = (matrix[i][j + 1] + matrix[i + 1][j] + matrix[i - 1][j] + matrix[i][j - 1] - step ** 2 * P / D) / 4
                    current_err = max(abs(prev - matrix[i][j]), current_err)

    if build_plot:
        x_grid, y_grid = np.meshgrid(y_values, x_values)
        surface = graph_objs.Surface(x=y_grid, y=x_grid, z=matrix.T)
        
        fig = graph_objs.Figure([surface])
        plotly.offline.plot(fig, auto_open=True)

    return iterations

solve(eps, step=1, build_plot=True)

steps = [1, 2, 4, 6, 8, 10]
epsilons = np.arange(0.001, 0.1, 0.001)

for step in steps:
    iterations = []

    for eps in epsilons:
        iterations.append(solve(eps, step=step))

    plt.xlabel('eps')
    plt.ylabel('iterations')
    plt.yscale('log')
    plt.plot(epsilons, iterations, label=f'step={step}')

plt.legend()
plt.show()