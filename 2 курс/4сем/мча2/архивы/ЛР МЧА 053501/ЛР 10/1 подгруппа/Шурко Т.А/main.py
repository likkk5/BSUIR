import math

import numpy as np
import matplotlib.pyplot as plt


eps = 0.001
m, a = 2.0, 0.9


def funct(x, y):
    return (a * (1 - y**2)) / ((1 + m) * x**2 + y**2 + 1)


def f(x, y):
    return -y


x0, y0 = 0, 0
LEFT, RIGHT = 0, 1


def main():
    print("Euler method: ", find_number_of_dots(euler_method, funct))
    print("Euler modified method: ", find_number_of_dots(method_euler_better, funct))
    print("Runge-Kutta method: ", find_number_of_dots(method_runge_kutta, funct))
    print("Adams method: ", find_number_of_dots(adams_method, funct))
    example()


def example():
    n = 10

    global y0
    y0 = 1

    x, y_euler = euler_method(n, f)
    x, y_better_euler = method_euler_better(n, f)
    x, y_runge_kutta = method_runge_kutta(n, f)
    x, y_adams = adams_method(n, f)

    res = []
    h = (RIGHT - LEFT) / n
    x_dots = []

    for i in range(n+1):
        x_k = LEFT + i * h
        x_dots.append(x_k)
        res.append(round(math.exp(-x_k), 4))

    plt.plot(x_dots, y_euler, color='red', label='euler')
    plt.plot(x_dots, y_better_euler, color='yellow', label='improved_euler')
    plt.plot(x_dots, y_runge_kutta, color='blue', label='runge-knutta')
    plt.plot(x_dots, y_adams, color='black', label='adams')
    plt.plot(x_dots, res, color='green', label='funct')
    plt.legend(loc='best')
    plt.show()


def find_number_of_dots(method, funct):
    n = 1
    eps_ = 1
    while eps_ > eps:
        x_dots, y_dots = method(n, funct)
        x_dots1, y_dots1 = method(n * 2, funct)
        eps_ = max(abs(y_dots1[2 * i] - y_dots[i]) for i in range(n + 1))
        if eps_ > eps:
            n *= 2
    return n


def adams_method(n, f):
    global RIGHT

    h = (RIGHT - LEFT) / n

    RIGHT = -h
    x, y = euler_method(n, f)
    RIGHT = 1

    f_prev = f(-h, y[0])

    y_k = [y0]
    x_k = []
    for i in range(n):
        x_k.append(LEFT + i * h)
        f_last = f(x_k[-1], y_k[-1])
        y_k.append(y_k[-1] + h * (1.5 * f_last - 0.5 * f_prev))
        f_prev = f_last
    return x_k, y_k


def euler_method(n, f):
    y_k = [y0]
    x_k = []
    h = (RIGHT - LEFT) / n
    for i in range(n):
        x_k.append(LEFT + i * h)
        y = y_k[-1]
        y_k.append(y + h * f(x_k[-1], y))
    return x_k, y_k


def method_euler_better(n, f):
    y_dots = [y0]
    h = (RIGHT - LEFT) / n
    x_k = []
    for i in range(n):
        x_k.append(LEFT + i * h)
        y_k = y_dots[-1]
        y_dots += [y_k + h * f(x_k[-1] + h/2, y_k + h/2 * f(x_k[-1], y_k))]
    return x_k, y_dots


def method_runge_kutta(n, f):
    y_dots = [y0]
    x_dots = []
    h = (RIGHT - LEFT) / n
    for i in range(n):
        x_dots.append(LEFT + i * h)
        y = y_dots[-1]
        k_1 = h * f(x_dots[-1], y)
        k_2 = h * f(x_dots[-1] + h/2, y + k_1/2)
        k_3 = h * f(x_dots[-1] + h/2, y + k_2/2)
        k_4 = h * f(x_dots[-1] + h, y + k_3)
        y_dots += [y + 1/6 * (k_1 + 2*k_2 + 2*k_3 + k_4)]
    return x_dots, y_dots


if __name__ == "__main__":
    main()
