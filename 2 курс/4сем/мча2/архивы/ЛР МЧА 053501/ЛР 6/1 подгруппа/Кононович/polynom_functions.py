import numpy as np


def get_error(x, y):
    func = lagrange(x, y) - best(x, y)
    der = np.polyder(func)

    max_error = 0.0
    for root in np.roots(der):
        if x[0] <= root <= x[-1]:
            max_error = max(max_error, np.polyval(func, root))

    return max_error


def lagrange(x_values, y_values):
    res = np.poly1d([0])
    for i in range(len(x_values)):
        l_i = np.poly1d([1])
        for j in range(len(x_values)):
            if i == j:
                continue
            l_i *= (np.poly1d([1, -x_values[j]]) / (x_values[i] - x_values[j]))
        res += (l_i * y_values[i])

    return res


def newton(x_values, y_values, x):
    divided_diffs = get_divided_differences(x_values, y_values, x)
    res = np.poly1d([0])
    for i in range(len(x_values)):
        f = np.poly1d([1])
        for j in range(i):
            f *= np.poly1d([1, -x_values[j]])
        res += (f * divided_diffs[0][i])

    return res


def get_divided_differences(x_values, y_values, x):
    div_diffs = [[0 for i in range(len(x_values) - j)] for j in range(len(x_values))]

    for i in range(len(div_diffs)):
        div_diffs[i][0] = y_values[i]

    for j in range(1, len(x_values)):
        for i in range(len(x_values) - j):
            div_diffs[i][j] = (div_diffs[i + 1][j - 1] - div_diffs[i][j - 1]) / (x_values[i + j] - x[i])

    return div_diffs


def best(x_values, y_values):
    return np.poly1d(np.polyfit(x_values, y_values, min(8, len(x_values) - 1)))
