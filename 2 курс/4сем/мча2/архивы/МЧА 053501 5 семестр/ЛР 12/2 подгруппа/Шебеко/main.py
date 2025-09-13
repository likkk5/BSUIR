import math
import numpy as np
import sympy as sp
import matplotlib
from matplotlib import pyplot as plt


class Util:
    def build_coeffs_tridiag(x_start, x_end, h, p, g):
        x = sp.symbols('x')

        A, B, C, F = [], [], [], []
        for xi in np.arange(x_start, x_end + h, h):
            A.append(1)
            C.append(1)
            B.append(-h ** 2 * p.subs({x: xi}) - 2)
            F.append(h ** 2 * g(xi))

        return A, B, C, F
    def solve_diag(A, B, C, F):
        a = [0]
        b = [0]
        n = len(A)

        for i in range(n):
            a.append(-C[i] / (A[i] * a[i] + B[i]))
            b.append((F[i] - A[i] * b[i]) / (A[i] * a[i] + B[i]))

        y = np.zeros(n)
        y[n - 1] = (F[n - 1] - A[n - 1] * b[n - 1]) / (C[n - 1] + A[n - 1] * a[n - 1])
        for i in range(n - 2, -1, -1):
            y[i] = a[i + 2] * y[i + 1] + b[i + 2]

        return y

    def build_coeffs(x_start, x_end, h, p, q, g):
        x = sp.symbols('x')
        n = int((x_end - x_start) / h) + 1
        a = np.zeros((n, n))
        b = np.zeros(n)
        for i, xi in enumerate(np.arange(x_start + h, x_end, h)):
            j = i + 1
            a[j][j - 1] = 2
            a[j][j] = 2 * h ** 2 * q.subs({x: xi}) - h * p.subs({x: xi}) - 4
            a[j][j + 1] = 2 + h * p.subs({x: xi})
            b[j] = 2 * h ** 2 * g.subs({x: xi})
        a[0][0] = 2 * h ** 2 * q.subs({x: x_start}) - 3 * h * p.subs({x: x_start}) - 4
        a[0][1] = 2 + 4 * h * p.subs({x: x_start})
        a[0][2] = -h * p.subs({x: x_start})
        b[0] = 2 * h ** 2 * g.subs({x: x_start})
        a[n - 1][n - 1] = 2 * h ** 2 * q.subs({x: x_end}) - 3 * h * p.subs({x: x_end}) + 2
        a[n - 1][n - 2] = -4 - 4 * h * p.subs({x: x_end})
        a[n - 1][n - 3] = h * p.subs({x: x_end})
        b[n - 1] = 2 * h ** 2 * g.subs({x: x_end})
        return np.linalg.solve(a, b)
    def build_coeffs1(x_start, x_end, h, p, q, g):
        x = sp.symbols('x')
        n = int((x_end - x_start) / h) + 1

        a = np.zeros((n, n))
        b = np.zeros(n)
        for i, xi in enumerate(np.arange(x_start + h, x_end, h)):
            j = i + 1
            a[j][j - 1] = 2
            a[j][j] = 2 * h ** 2 * q.subs({x: xi}) - h * p.subs({x: xi}) - 4
            a[j][j + 1] = 2 + h * p.subs({x: xi})
            b[j] = 2 * h ** 2 * g.subs({x: xi})

        a[0][0] = -3
        a[0][1] = 4
        a[0][2] = -1
        b[0] = 0

        a[n - 1][n - 1] = 2 * h - 3
        a[n - 1][n - 2] = 12
        a[n - 1][n - 3] = -3
        b[n - 1] = 4 * h

        return np.linalg.solve(a, b)

    def build_coeffs_tridiag_task4(x_start, x_end, h, p, g):
        x = sp.symbols('x')

        A, B, C, F = [], [], [], []
        for xi in np.arange(x_start, x_end + h, h):
            A.append(1)
            C.append(1)
            B.append(-h ** 2 * p(xi) - 2)
            F.append(h ** 2 * g(xi))

        A[0] = 3.6 + h
        B[0] = -4.8
        C[0] = 1.2
        F[0] = F[-1] = 0
        C[-1] = h + 1.2
        B[-1] = -1.5
        A[-1] = 0.4

        return A, B, C, F


def solve_task1(e=0.001):
    a = math.sin(22)
    b = math.cos(22)
    p, x = sp.symbols("p x")
    p = -(1 + b * x ** 2) / a

    x_start = -1
    x_end = 1

    h = 0.1
    cur_precision = 1

    print('Начальный шаг = ' + str(h))

    A, B, C, F = Util.build_coeffs_tridiag(x_start, x_end, h * 2, p, f(a))
    y1 = Util.solve_diag(A, B, C, F)
    y = []
    iter_count = 0

    while cur_precision > e:
        y = np.copy(y1)
        h /= 2
        A, B, C, F = Util.build_coeffs_tridiag(x_start, x_end, h, p, f(a))
        y1 = Util.solve_diag(A, B, C, F)
        cur_precision = np.max(np.abs([y1[2 * i] - y[i] for i in range(len(y))]))
        iter_count += 1
        print('{}) Точность: {}, Начальный шаг: {}'.format(iter_count, cur_precision, h))

    x1 = np.arange(x_start, x_end + h, h)
    plt.plot(x1, y1)
    plt.show()




def f(a):
    def wrapped(x):
        return -1 / a

    return wrapped

def solve_task2(e=0.05):
    p, q, g, x = sp.symbols("p q g x")
    p = sp.sin(x)
    q = 6 * sp.sqrt(1+x**2)
    g = 7 * (1 + sp.sin(x)**2)
    x_start = 0
    x_end = 2
    h = 0.25
    cur_precision = 1
    y1 = Util.build_coeffs(x_start, x_end, h, p, q, g)
    y = []
    iter_count = 0

    while cur_precision > e:
        y = np.copy(y1)
        h /= 2
        y1 = Util.build_coeffs(x_start, x_end, h, p, q, g)
        cur_precision = np.max(np.abs([y1[2 * i] - y[i] for i in range(len(y))]))
        iter_count += 1
        print('{}) Точность: {}, Текущий шаг: {}'.format(iter_count, cur_precision, h))
    plt.plot(np.arange(x_start, x_end + h, h), y1)
    plt.show()




def solve_task3(e=0.01):
    p, q, g, x = sp.symbols("p q g x")
    p = -4 * x
    q = 5 + 0 * x
    g = 2 * x
    # p = 1 + 0*x
    # q = 2 * (x **2)
    # g = x + 1
    x_start = 2
    x_end = 4
    h = 0.1

    cur_precision = 1
    y1 = Util.build_coeffs1(x_start, x_end, h, p, q, g)
    y = []
    iter_count = 0

    while cur_precision > e:
        y = np.copy(y1)
        h /= 2
        y1 = Util.build_coeffs1(x_start, x_end, h, p, q, g)
        cur_precision = np.max(np.abs([y1[2 * i] - y[i] for i in range(len(y))]))
        iter_count += 1
        print('{}) Точность: {}, Текущий шаг: {}'.format(iter_count, cur_precision, h))

    plt.plot(np.arange(x_start, x_end + h, h), y1)
    plt.grid = True
    plt.show()




def solve_task4():
    p, x = sp.symbols("p x")

    k1 = 1.5
    k2 = 0.4
    q1 = 8.3
    q2 = 3.5
    g = 9 * sp.exp(-x)
    c = 1.725
    k = lambda xi: k1 if xi < c else k2
    q = lambda xi: q1 if xi < c else q2

    x_start = 0
    x_end = 2.8

    h = 0.25
    cur_precision = 1
    e = 0.05

    A, B, C, F = Util.build_coeffs_tridiag_task4(x_start,
                                            x_end,
                                            h * 2,
                                            lambda xi: -q(xi) / k(xi),
                                            lambda xi: -g.subs({x: xi}) / k(xi))

    y1 = Util.solve_diag(A, B, C, F)
    y = []
    iter_count = 0

    while cur_precision > e:
        y = np.copy(y1)
        h /= 2
        A, B, C, F = Util.build_coeffs_tridiag_task4(x_start,
                                                x_end,
                                                h,
                                                lambda xi: -q(xi / k(xi)),
                                                lambda xi: -g.subs({x: xi}) / k(xi))
        y1 = Util.solve_diag(A, B, C, F)
        cur_precision = np.max(np.abs([y1[2 * i] - y[i] for i in range(len(y) - 1)]))
        iter_count += 1
        print('{}) Точность: {}, Текущий шаг: {}'.format(iter_count, cur_precision, h))

    x1 = np.arange(x_start, x_end + h, h)
    plt.plot(x1, y1)
    plt.show()


if __name__ == '__main__':
    print("Задание 1:\nНеобходимая точность: 0.001")
    solve_task1()
    print("\nЗадание 2:\nНеобходимая точность: 0.05")
    solve_task2()
    print("\nЗадание 3:\nНеобходимая точность: 0.01")
    solve_task3()
    print("\nЗадание 4:\nНеобходимая точность: 0.05")
    solve_task4()