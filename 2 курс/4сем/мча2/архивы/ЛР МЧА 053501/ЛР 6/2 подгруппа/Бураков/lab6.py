import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
variants = [0.0, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 1.8, 2.53, 3.96, 5.33, 1.96]
k = 2
m = variants[k - 1]
x = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
y = [p[i] + ((-1) ** k) * m for i in range(len(p))]
x1 = np.array(x)
y1 = np.array(y)


def main():
    global x
    global y
    print("x =", x)
    print("y =", y)
    x = np.array(x, dtype=float)
    y = np.array(y, dtype=float)
    x_new = np.linspace(0, 1)
    print('\n\033[94mРезультат в точке 0.47 по полиному Лагранжа:\n',
    lagrange(x, y, 0.47))
    print('\n\033[96mРезультат в точке 0.47 по полиному Ньютона:\n',
    newton(x, y, 0.47))
    y_new = [lagrange(x, y, i) for i in x_new]
    plt.plot(x, y, 'o', x_new, y_new)
    plt.title(r'$Лагранж$')
    plt.grid(True)
    plt.show()
    y_new = [newton(x, y, i) for i in x_new]
    plt.plot(x, y, 'o', x_new, y_new)
    plt.title(r'$Ньютон$')
    plt.grid(True)
    plt.show()
    popt, pcov = curve_fit(sq_polynom, x1, y1, (1e3, 1e-2, -1e1), maxfev=10 ** 6)
    print('\n\033[95mКвадратный многочлен наилучшего приближения:')
    print("A*x**2 + B*x + C = 0")
    print('A = {0}\nB = {1}\nC = {2}'.format(*tuple(popt)))
    A = popt[0]
    B = popt[1]
    C = popt[2]
    plt.scatter(x1, y1, s=30, color='orange')
    plt.plot(x1, sq_polynom(x1, *popt))
    plt.title(r'$КвадратныйМногочлен$')
    plt.grid(True)
    plt.show()
    print("Результат в точке", 0.47)
    print(A * 0.47 ** 2 + B * 0.47 + C)


def fin_diff(x, y, nodes):
    diff = list(range(nodes))
    diff[0] = y
    for i in range(1, nodes):
        r = list(range(nodes - i))
        for j in range(nodes - i):
            r[j] = (diff[i - 1][j + 1] - diff[i - 1][j]) / (x[j + i] - x[j])
        diff[i] = r
    return diff


def lagrange(x, y, t):
    result = 0
    for i in range(len(y)):
        poly = y[i]
        for j in range(len(x)):
            if i == j:
                continue
            poly *= (t - x[j]) / (x[i] - x[j])
        result += poly
    return result


def newton(x, y, t):
    diff = fin_diff(x, y, len(x))
    result = 0
    for i in range(len(y)):
        poly = diff[i][0]
        for j in range(i):
            poly *= (t - x[j])
        result += poly
    return result


def sq_polynom(x1, a, b, c):
    return a * x1 ** 2 + b * x1 + c



if __name__ == '__main__':
    main()