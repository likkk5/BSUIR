import numpy as np
import matplotlib.pyplot as plt

def main():
    x = np.array(
        [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])
    p = np.array(
        [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01])
    k = 6
    m = 3
    y = np.zeros(len(x))
    for i in range(len(x)):
        y[i] = p[i] + ((-1) ** 9) * 4.5

    lagrange_poly = lagrange(x, y)
    newton_poly = newton(x, y)
    best_poly = np.poly1d(np.polyfit(x, y, 10))
    print_res(lagrange_poly, newton_poly, best_poly, x, y)

    print("Test 1")
    x = np.array(
        [-1.5, -0.75, 0, 0.75, 1.5]
    )
    y = np.array(
        [-14.1014, -0.931596, 0, 0.931596, 14.1014]
    )
    lagrange_poly = lagrange(x, y)
    newton_poly = newton(x, y)
    best_poly = np.poly1d(np.polyfit(x, y, 3))
    print_res(lagrange_poly, newton_poly, best_poly, x, y)

    print("Test 2")
    x = np.arange(0.1, 2.1, 0.1)
    y = np.zeros(len(x))
    for i in range(len(x)):
        y[i] = 1 / x[i]
    lagrange_poly = lagrange(x, y)
    newton_poly = newton(x, y)
    print_res(lagrange_poly, newton_poly, best_poly, x, y)

    print("Test 3")
    x3 = np.arange(0.0, 9.1, 0.5)
    y3 = np.zeros(len(x3))
    for i in range(len(x3)):
        y3[i] = x3[i] ** (1/2)
    lagrange_poly = lagrange(x3, y3)
    newton_poly = newton(x3, y3)
    print_res(lagrange_poly, newton_poly, best_poly, x3, y3)


def print_res(lagrange_poly, newton_poly, best_poly, x, y):
    print("Многочлен Лагранжа")
    print(lagrange_poly)
    print("\nМногочлен Ньютона")
    print(newton_poly)
    print("\nМногочлен наилучшего приближения")
    print(best_poly)
    print("\nЗначение в точке 0.47(многочлен Ньютона):")
    print(lagrange_poly(0.47))
    print("Значение в точке 0.47(многочлен Лагранжа):")
    print(newton_poly(0.47))
    print("Значение в точке 0.47(многочлен наилучшего приближения):")
    print(best_poly(0.47))
    y_plot = lagrange_poly(x)
    plt.plot(x, y, 'o', x, y_plot)
    plt.grid(True)
    plt.show()


def lagrange(x_values, y_values):
    res_poly = np.poly1d(0)

    for j in range(len(y_values)):
        poly = np.poly1d(1)
        for i in range(len(x_values)):
            if i != j:
                poly = np.polymul(poly, np.poly1d([x_values[i]], True) / (
                x_values[j] - x_values[i]))
        res_poly = np.polyadd(res_poly, y_values[j] * poly)
    return res_poly

def newton(x_values, y_values):
    res_poly = np.poly1d(0)
    x = x_values.copy()
    y = y_values.copy()
    for i in range(1, len(x)):
        y[i:len(x)] = (y[i:len(x)] - y[i - 1]) / (x[i:len(x)] - x[i - 1])
    for i in range(len(y)):
        poly = np.poly1d(1)
        for j in range(i):
            poly *= np.poly1d([x[j]], True)
        poly *= y[i]
        res_poly += poly
    return res_poly

if __name__ == '__main__':
    main()