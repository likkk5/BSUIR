import math

import numpy as np
import matplotlib.pyplot as plt

plotdots = 10**3
eps = 10**-3

m, a = 2.0, 0.9


def func(x, y):
    return (a * (1 - y**2)) / ((1 + m) * x**2 + y**2 + 1)


def f(x, y):
    return x * (y**2)


y0 = 1
LEFT, RIGHT = 0, 1


def main():
    print("Euler method and Runge-Kutta method \n")
    print("Adams' method \n")
    n = 5
    y_euler = euler_method(n)
    y_better_euler = method_euler_better(n)
    y_runge_kutta = method_runge_kutta(n)
    res = []
    h = (RIGHT - LEFT) / n
    x_dots = []
    for i in range(n+1):
        x_k = LEFT + i * h
        x_dots.append(x_k)
        res.append(round(2/(2-x_k**2), 4))
    print(res)
    plt.plot(x_dots, y_euler, color='red', label='euler')
    plt.plot(x_dots, y_better_euler, color='yellow', label='improved_euler')
    plt.plot(x_dots, y_runge_kutta, color='blue', label='runge-knutta')
    plt.plot(x_dots, res, color='green', label='funct')
    plt.legend(loc='best')
    plt.show()



def euler_method(n):
    y_k = [y0]
    h = (RIGHT - LEFT) / n
    for i in range(n):
        x_k = LEFT + i * h
        y = y_k[-1]
        y_k += [round(y + h * f(x_k, y), 4)]
    print(y_k)
    return y_k


def method_euler_better(n):
    y_dots = [y0]
    h = (RIGHT - LEFT) / n
    for i in range(n):
        x_k = LEFT + i * h
        y_k = y_dots[-1]
        y_dots += [round(y_k + h * f(x_k + h/2, y_k + h/2 * f(x_k, y_k)), 4)]
    print(y_dots)
    return y_dots


def method_runge_kutta(n):
    y_dots = [y0]
    h = (RIGHT - LEFT) / n
    for i in range(n):
        x = LEFT + i * h
        y = y_dots[-1]
        k_1 = h * f(x, y)
        k_2 = h * f(x + h/2, y + k_1/2)
        k_3 = h * f(x + h/2, y + k_2/2)
        k_4 = h * f(x + h, y + k_3)
        y_dots += [round(y + 1/6 * (k_1 + 2*k_2 + 2*k_3 + k_4), 4)]
    print(y_dots)
    return y_dots


if __name__ == "__main__":
    main()
