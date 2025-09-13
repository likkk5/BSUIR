import math

from sympy import integrate, sqrt, Symbol, Eq, symbols, Function, exp, sin

import matplotlib.pyplot as plt
import matplotlib
import numpy as np

from matplotlib import cm
from numpy import linspace

matplotlib.use('TkAgg')


# variant 29
def sweep_method(a, b, c, d):
    AlphaS = [-c[0] / b[0]]
    BetaS = [d[0] / b[0]]
    GammaS = [b[0]]
    n = len(d)
    result = [0 for i in range(n)]

    for i in range(1, n - 1):
        GammaS.append(b[i] + a[i] * AlphaS[i - 1])
        AlphaS.append(-c[i] / GammaS[i])
        BetaS.append((d[i] - a[i] * BetaS[i - 1]) / GammaS[i])

    GammaS.append(b[n - 1] + a[n - 1] * AlphaS[n - 2])
    BetaS.append((d[n - 1] - a[n - 1] * BetaS[n - 2]) / GammaS[n - 1])

    result[n - 1] = BetaS[n - 1]
    for i in reversed(range(n - 1)):
        result[i] = AlphaS[i] * result[i + 1] + BetaS[i]

    return result


def task_1():
    def specified(a, b, t_0, t_n, h, tetta, fi, g1, g2, k, f, func_for_partition):
        # iteration count
        columns = int((b - a) / h) + 1
        rows = int((t_n - t_0) / tetta) + 2
        solving = np.zeros((rows, columns))

        # boundary conditions initialization
        for index, value in enumerate(j for j in np.arange(a, b + h, h)):
            solving[0][index] = fi(value)
        for index, value in enumerate(j for j in np.arange(t_0, t_n, tetta)):
            solving[index][0] = g1(value)
        alfa = tetta / (h ** 2)
        a_k = [k * alfa] * columns
        b_k = [-(1 + 2 * k * alfa)] * columns
        c_k = [k * alfa] * columns
        x_points = linspace(a+h, b, columns-1).tolist()

        for index_t, time in enumerate((j for j in np.arange(t_0, t_n, tetta)), 1):
            d_k = []
            for index_x, coord in enumerate((j for j in x_points)):
                d_k.append(-tetta * f(coord, time) - solving[index_t][index_x])

            d_k[0] = d_k[0] - a_k[0] * g1(time)
            d_k[-1] = d_k[-1] - c_k[-1] * g2(time)

            res = sweep_method(a_k, b_k, c_k, d_k)
            for i in range(len(res)):
                solving[index_t][i] = res[i]
            solving[index_t][len(res)] = g2(time) * 2 * h + solving[index_t][len(res)-1]
        return solving

    a = 0
    b = 1
    k = 0.5
    ua = lambda t: 0
    ub = lambda t: exp(10 * t) - 1
    u = lambda x: 0
    T = 0.1
    h = 0.1
    tetta = (h ** 2) / 4
    f = lambda x, t: 1
    fi = lambda x: 0
    T1 = 0

    def func_for_partition(coord, time, T_prev, T_cur, T_next, h, tetta, f):
        return T_cur + tetta / (h ** 2) * (T_next - 2 * T_cur + T_prev) + tetta * f(
            coord, time)

    solving = specified(a, b, T1, T, h, tetta, fi, ua, ub, k, f, func_for_partition)
    points = np.arange(a, b + h, h)
    plt.figure()
    plt.plot(points, solving[0], color='black', label='t=0')
    tet = enumerate(np.arange(0, T, tetta * 5))

    for index, value in enumerate(np.arange(0, T, tetta * 2)):
        plt.plot(points, solving[index * 2], label='t={}t'.format(index * 2))
    plt.plot(points, solving[-1], color='green', label='t=T')
    plt.title('Неявный: t = (h^2)/4')
    plt.legend()
    plt.grid(True)
    plt.show()

    def plot_3d():
        fig = plt.figure()
        ax = fig.add_subplot(projection='3d')

        X = np.arange(a, b + h, h)
        Y = np.arange(T1, T + tetta, tetta)
        print(len(X), len(Y))
        X, Y = np.meshgrid(X, Y)
        surf = ax.plot_surface(X, Y, solving, cmap=cm.coolwarm,
                               linewidth=0, antialiased=False)
        plt.show()

    plot_3d()


def task():
    def specified(a, b, t_0, t_n, h, tetta, fi, g1, g2, k, f, func_for_partition):
        # iteration count
        columns = int((b - a) / h) + 1
        rows = int((t_n - t_0) / tetta) + 2
        solving = np.zeros((rows, columns))

        print(f"Rows(temp): {rows}; Columns(x): {columns}")

        # boundary conditions initialization
        for index_x, coord in enumerate(j for j in np.arange(a, b + h, h)):
            solving[0][index_x] = fi(coord)

        for index_t, time in enumerate(j for j in np.arange(t_0, t_n, tetta)):
            solving[index_t][0] = g1(time)

        for index_t, time in enumerate((j for j in np.arange(t_0 + tetta, t_n, tetta)), 1):
            for index_x, coord in enumerate((j for j in np.arange(a + h, b+h, h)), 1):
                if coord == b:
                    solving[index_t][index_x] = g2(time) * 2 * h + solving[index_t][index_x - 1]
                else:
                    solving[index_t][index_x] = func_for_partition(coord,
                                                                   time,
                                                                   solving[index_t - 1][index_x - 1],
                                                                   solving[index_t - 1][index_x],
                                                                   solving[index_t - 1][index_x + 1],
                                                                   h,
                                                                   tetta,
                                                                   f)

        return solving

    a = 0
    b = 1
    k = 0.5
    ua = lambda t: 0
    ub = lambda t: exp(10 * t) - 1
    T = 0.1
    h = 0.1
    tetta = (h ** 2) / 4
    f = lambda x, t: 1
    fi = lambda x: 0
    T1 = 0

    def func_for_partition(coord, time, T_prev, T_cur, T_next, h, tetta, f):
        return T_cur + tetta / (h ** 2) * (T_next - 2 * T_cur + T_prev) + tetta * f(
            coord, time)

    solving = specified(a, b, T1, T, h, tetta, fi, ua,  ub, k, f, func_for_partition)
    points = np.arange(a, b + h, h)
    plt.figure()
    plt.plot(points, solving[0], color='black', label='t=0')
    tet = enumerate(np.arange(0, T, tetta * 5))

    for index, value in enumerate(np.arange(0, T, tetta*2)):
        plt.plot(points, solving[index*2], label='t={}t'.format(index * 2))
    plt.plot(points, solving[-1], color='green', label='t=T')
    plt.title('Явный t = (h^2)/4')
    plt.legend()
    plt.grid(True)
    plt.show()

    def plot_3d():
        fig = plt.figure()
        ax = fig.add_subplot(projection='3d')

        X = np.arange(a, b + h, h)
        Y = np.arange(T1, T + tetta, tetta)
        print(len(X), len(Y))
        X, Y = np.meshgrid(X, Y)
        surf = ax.plot_surface(X, Y, solving, cmap=cm.coolwarm,
                               linewidth=0, antialiased=False)
        plt.show()

    plot_3d()


def example():
    def specified(a, b, t_0, t_n, h, tetta, fi, g1, g2, k, f, func_for_partition):
        # iteration count
        columns = int((b - a) / h) + 1
        rows = int((t_n - t_0) / tetta) + 2
        solving = np.zeros((rows, columns))

        print(f"Rows(temp): {rows}; Columns(x): {columns}")

        # boundary conditions initialization
        for index_x, coord in enumerate(j for j in np.arange(a, b + h, h)):
            solving[0][index_x] = fi(coord)

        for index_t, time in enumerate(j for j in np.arange(t_0, t_n, tetta)):
            solving[index_t][0] = g1(time)

        for index_t, time in enumerate((j for j in np.arange(t_0 + tetta, t_n, tetta)), 1):
            for index_x, coord in enumerate((j for j in np.arange(a + h, b+h, h)), 1):
                if coord == b:
                    solving[index_t][index_x] = g2(time) * h + solving[index_t][index_x - 1]
                else:
                    solving[index_t][index_x] = func_for_partition(coord-h,
                                                               time,
                                                               solving[index_t - 1][index_x - 1],
                                                               solving[index_t - 1][index_x],
                                                               solving[index_t - 1][index_x + 1],
                                                               h,
                                                               tetta,
                                                               f)

        return solving

    a = 0
    b = 1
    k = 1
    ua = lambda t: 0
    ub = lambda t: t

    T = 1
    h = 0.1
    tetta = (h ** 2) / 4
    f = lambda x, t: x
    fi = lambda x: sin((3*math.pi*x)/2)
    T1 = 0

    def func_for_partition(coord, time, T_prev, T_cur, T_next, h, tetta, f):
        return T_cur + (tetta / (h ** 2)) * (T_next - 2 * T_cur + T_prev) + tetta * f(
            coord, time)

    solving = specified(a, b, T1, T, h, tetta, fi, ua,  ub, k, f, func_for_partition)
    points = np.arange(a, b + h, h)
    plt.figure()
    plt.plot(points, solving[0], color='black', label='t=0')
    tet = enumerate(np.arange(0, T, tetta * 5))

    for index, value in enumerate(np.arange(0, T, tetta*2)):
        plt.plot(points, solving[index*2], label='t={}t'.format(index * 2))
    plt.plot(points, solving[-1], color='green', label='t=T')
    plt.title('task 4: ')
    plt.legend()
    plt.grid(True)
    plt.show()

    def plot_3d(solving):
        fig = plt.figure()
        ax = fig.add_subplot(projection='3d')

        X = np.arange(a, b + h, h)
        Y = np.arange(T1, T + tetta, tetta)
        print(len(X), len(Y))
        X, Y = np.meshgrid(X, Y)
        surf = ax.plot_surface(X, Y, solving, cmap=cm.gist_rainbow,
                               linewidth=0, antialiased=False)
        plt.show()

    def plot_3d2():
        fig = plt.figure()
        ax = fig.add_subplot(projection='3d')

        X = np.arange(a, b + h, h)
        Y = np.arange(T1, T + tetta, tetta)

        solving = np.zeros((len(Y), len(X)))

        for i in range(len(Y)):
            for j in range(len(X)):
                time = Y[i]
                point = X[j]
                solving[i][j] = (point*time + math.exp((-(1.5*math.pi)**2)*time)*math.sin(1.5*math.pi*point))
        print(solving[1], solving[2])
        X, Y = np.meshgrid(X, Y)
        surf = ax.plot_surface(X, Y, solving, cmap=cm.gist_rainbow,
                               linewidth=0, antialiased=False)
        plt.show()

    # plot_3d()
    # plot_3d2()
    h = 0.02
    tetta = 0.1

    def specified2(a, b, t_0, t_n, h, tetta, fi, g1, g2, k, f, func_for_partition):
        # iteration count
        columns = int((b - a) / h) + 1
        rows = int((t_n - t_0) / tetta) + 1
        solving = np.zeros((rows, columns))

        # boundary conditions initialization
        for index, value in enumerate(j for j in np.arange(a, b + h, h)):
            solving[0][index] = fi(value)
        for index, value in enumerate(j for j in np.arange(t_0, t_n, tetta)):
            solving[index][0] = g1(value)
        alfa = tetta / (h ** 2)
        a_k = [k * alfa] * (columns-2)
        b_k = [-(1 + 2 * k * alfa)] * (columns-2)
        c_k = [k*alfa] * (columns-2)
        x_points = linspace(a + h, b - h, columns - 2).tolist()
        print()
        print(len(x_points))
        print()
        for index_t, time in enumerate((j for j in np.arange(t_0, t_n, tetta)), 1):
            d_k = []
            for index_x, coord in enumerate((j for j in x_points)):
                d_k.append(tetta * f(coord, time) + solving[index_t][index_x])

            d_k[0] = d_k[0] - a_k[0] * g1(time)
            d_k[-1] = d_k[-1] - c_k[-1] * g2(time)

            res = sweep_method(a_k, b_k, c_k, d_k)
            for i in range(len(res)):
                solving[index_t][i] = res[i]
            solving[index_t][len(res)+1] = g2(time) * h + solving[index_t][len(res)]
        return solving

    solving2 = specified2(a, b, T1, T, h, tetta, fi, ua, ub, k, f, func_for_partition)
    plot_3d(solving2)


# example()
# task()
task_1()
