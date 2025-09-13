import numpy as np
import matplotlib.pyplot as plt

def main():
    f = lambda x : np.arctan(x)
    x = [(1 + 2/6*a) for a in range(6)]
    y =  [f(1 + 2/6*x) for x in range(6)]
    print(interpolate(x, y, 1.0))
    plt.scatter(x, y)
    plt.show()

    

def interpolate(x, y, point):
    nodes = np.array(x)
    y = np.array(y)
    if np.any(np.diff(nodes) < 0):
        dx_i = np.argsort(nodes)
        nodes = nodes[dx_i]
        y = y[dx_i]

    diff_x = np.diff(nodes)
    diff_y = np.diff(y)
    arr = np.zeros((len(nodes), len(nodes)))
    arr_b = np.zeros((len(nodes), 1))
    arr[0, 0] = 1
    arr[len(nodes) - 1][len(nodes) - 1] = 1
    lin_solution = solve(arr, arr_b, diff_x, diff_y, nodes)
    arr_d = np.zeros((len(nodes) - 1, 1))
    arr_b = np.zeros((len(nodes) - 1, 1))
    for i in range(0, len(arr_d)):
        arr_d[i] = (lin_solution[i + 1] - lin_solution[i]) / (3 * diff_x[i])
        arr_b[i] = (diff_y[i] / diff_x[i]) - (diff_x[i] / 3) * (2 * lin_solution[i] + lin_solution[i + 1])
    solution = 0
    solution = calculate_dxi(nodes, point, solution)
    return y[solution] + arr_b[solution] * (point - nodes[solution]) + lin_solution[solution] * (point - nodes[solution]) ** 2 + arr_d[solution] * (
            point - nodes[solution]) ** 3

def calculate_dxi(x, point, solution):
    for i in range(len(x) - 1):
        if x[i] <= point and point <= x[i + 1]:
            solution = i
            break
    return solution

def solve(arr, b, dx, dy, nodes):
    for i in range(1, len(nodes) - 1):
        arr[i, i - 1] = dx[i - 1]
        arr[i, i + 1] = dx[i]
        arr[i, i] = 2 * (dx[i - 1] + dx[i])
        b[i, 0] = 3 * (dy[i] / dx[i] - dy[i - 1] / dx[i - 1])
    c = np.linalg.solve(arr, b)
    return c


if __name__ == "__main__":
    main()