import numpy
import numpy as np
import scipy as sp
from scipy.misc import derivative
from scipy import sparse
from scipy import integrate
import matplotlib
import matplotlib.pyplot as plt
import sympy
from sympy.solvers import solve
from numpy import linspace
from collections import namedtuple


POWER = 5
POWER5 = 25
POWER_1 = 35
POWER_2 = 15
POWER_3 = 10
POWER_4 = 30
ITER_COUNT = 150
LINSPACE_SIZE = 100

x = sympy.Symbol('x')

a = 0.2
b = 1.2
u_a = 4
u_b = 1
my_k = 1



class Util:
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

    def k_1(x, c):
        return x ** 3


    def function_1(x):
        return 1.0 + x ** (1 / 3)


    def build_final_equation(f, k, c, c1, c2):
        first_iter = (-(sympy.integrate(f(x), x) + c1) / k(x, c)).expand()
        second_iter = sympy.integrate(first_iter, x) + c2
        return second_iter


    def func_for_partition_2(yk_m1, yk, yk_p1, h, k=1, func=None):
        if not func:
            func = Util.function_1

        func = -k * (yk_p1 - 2 * yk + yk_m1) / h ** 2 - func(x)
        return func


    def solve_thermal_conductivity_equation(f, k, c, a, b, u_a, u_b):
        c1, c2 = sympy.Symbol('c1'), sympy.Symbol('c2')
        true_eq = Util.build_final_equation(f, k, c, c1, c2)
        c2_val = solve(true_eq.subs(x, b) - u_b, c2)[0]
        true_eq = true_eq.subs(c2, c2_val)

        c1_val = solve(true_eq.subs(x, a) - u_a, c1)[0]
        true_eq = true_eq.subs(c1, c1_val)
        print(true_eq)
        return true_eq
    def differences_method(start_variables_count,
                           a,
                           b,
                           y_a,
                           y_b,
                           func_for_partition,
                           points_k,
                           func=None):
        h = (b - a) / start_variables_count
        points = linspace(a + h, b - h, start_variables_count).tolist()

        a_k = []
        b_k = []
        c = []
        d = []
        if func is None:
            func = Util.function_1
        # print(func)
        selected_k = 0
        for i in range(start_variables_count):
            if points[i] > points_k[selected_k][0]:
                selected_k += 1
            a_k.append(-points_k[selected_k][1] / (h ** 2))
            b_k.append(2 * points_k[selected_k][1] / h ** 2)
            c.append(-points_k[selected_k][1] / h ** 2)
            d.append(func(points[i]))
        d[0] = d[0] - a_k[0] * y_a
        d[-1] = d[-1] - c[-1] * y_b
        answer = Util.sweep_method(a_k, b_k, c, d)
        data_type = namedtuple('data',
                               ('points', 'answer', 'step'))
        points.insert(0, a)
        points.append(b)

        answer.insert(0, y_a)
        answer.append(y_b)
        return data_type(points, answer, h)
    def func_for_partition_2(yk_m1, yk, yk_p1, h, k=1, func=None):
        if not func:
            func = Util.function_1

        func = -k * (yk_p1 - 2 * yk + yk_m1) / h ** 2 - func(x)
        return func


# a = 0
# b = 1
# h = (b - a) / 150
# ua = 0
# ub = 0

def task1():

    print('Набор 1:')
    var_1 = Util.solve_thermal_conductivity_equation(Util.function_1, Util.k_1, 1, a, b, u_a, u_b)
    print('\nНабор 2:')
    var_2 = Util.solve_thermal_conductivity_equation(Util.function_1,
                                                lambda x, c: c * Util.k_1(x, c),
                                                2, a, b, u_a, u_b)
    print('\nНабор 3:')
    var_3 = Util.solve_thermal_conductivity_equation(Util.function_1,
                                                lambda x, c: c * Util.k_1(x, c),
                                                0.1, a, b, u_a, u_b)

    D = linspace(a, b, LINSPACE_SIZE)
    func_y1, func_y2, func_y3, func_y4 = [], [], [], []
    for i in range(len(D)):
        func_y1.append(var_1.subs(x, D[i]))
        func_y2.append(var_2.subs(x, D[i]))
        func_y3.append(var_3.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y1, c='red', label='c=1 (набор 1)')
    plt.plot(D, func_y2, c='green', label='c=2 (набор 2)')
    plt.plot(D, func_y3, c='blue', label='c=0.1 (набор 3)')

    plt.legend()
    plt.show()

    print('\nНабор 4:')
    var_4 = Util.solve_thermal_conductivity_equation(Util.function_1,
                                                lambda x, c: 1 / Util.k_1(x, c),
                                                1, a, b, u_a, u_b)

    for i in range(len(D)):
        func_y4.append(var_4.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y1, c='red', label='набор 1')
    plt.plot(D, func_y4, c='green', label='набор 4')

    plt.legend()
    plt.show()

    print('\nНабор 5:')
    var_5 = Util.solve_thermal_conductivity_equation(Util.function_1, Util.k_1, 1, a, b, -u_a,
                                                u_b)
    print('\nНабор 6:')
    var_6 = Util.solve_thermal_conductivity_equation(Util.function_1, Util.k_1, 1, a, b, u_a,
                                                -u_b)
    print('\nНабор 7:')
    var_7 = Util.solve_thermal_conductivity_equation(Util.function_1, Util.k_1, 1, a, b, -u_a,
                                                -u_b)

    func_y5, func_y6, func_y7 = [], [], []
    for i in range(len(D)):
        func_y5.append(var_5.subs(x, D[i]))
        func_y6.append(var_6.subs(x, D[i]))
        func_y7.append(var_7.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y5, c='red', label='набор 5')
    plt.plot(D, func_y6, c='green', label='набор 6')
    plt.plot(D, func_y7, c='blue', label='набор 7')

    plt.legend()
    plt.show()

def A(x, k1, k2, k3, xr1, xr2):
    if x < xr1:
        return k1
    elif x-h < xr1 < x:
        return h / ((xr1 - x + h) / k1 + (x - xr1) / k2)
    elif x <= xr2:
        return k2
    elif x-h < xr2 < x:
        return h / ((xr2 - x + h) / k2 + (x - xr2) / k3)
    else:
        return k3
def B(x, k1, k2, k3, xr1, xr2):
    if x < xr1:
        return k1
    elif x < xr1 < x+h:
        return h / ((xr1 - x) / k1 + (x+h - xr1) / k2)
    elif x+h <= xr2:
        return k2
    elif x < xr2 < x+h:
        return h / ((xr2 - x) / k2 + (x+h - xr2) / k3)
    else:
        return k3
def phi(x, x0, C):
    if abs(x - x0) - h/2 < 1e-5:
        return C/2
    elif x - h/2 < x0 < x + h/2:
        return C
    else:
        return 0
def solve2(a, b, ua, ub, h, k1, k2, k3, xr1, xr2, phi_conds):
    n = int((b - a) / h) + 1
    M = np.zeros(shape=(n, n))
    Y = np.zeros(n)
    M[0, 0] = 1
    M[-1, -1] = 1
    Y[0] = ua
    Y[-1] = ub
    for i in range(1, n - 1):
        xi = a + h * i
        M[i, i - 1] = A(xi, k1, k2, k3, xr1, xr2)
        M[i, i] = -(A(xi, k1, k2, k3, xr1, xr2) + B(xi, k1, k2, k3, xr1, xr2))
        M[i, i + 1] = B(xi, k1, k2, k3, xr1, xr2)
        Y[i] = - h * sum(phi(xi, x0, C) for x0, C in phi_conds)

    return np.linspace(a, b, n), np.linalg.solve(M, Y)


def task2():
    POWER = 200
    POWER_1 = 100
    POWER_2 = 150
    POWER_3 = 100
    POWER_4 = 300

    a = 0.2
    b = 1.2
    u_a = 4
    u_b = 1
    my_k = 1
    eps = 0.007

    # 4а
    data_a1 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(0.5 * (b + a), 0.01), (b, 150)])
    print('h=', data_a1.step)
    data_a2 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(0.5 * (b + a), 150), (b, 0.01)])

    D1, y1 = data_a1.points, data_a1.answer
    D2, y2 = data_a2.points, data_a2.answer

    plt.figure()
    plt.plot(D1, y1, color='red', label='k1 << k2')
    plt.plot(D2, y2, label='k1 >> k2')
    plt.title('Задание 2 пункт 4а')
    plt.grid(True)
    plt.legend()
    plt.show()

    # 4б
    data_b1 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), 0.2),
                                  (a + (2 / 3) * (b - a), 0.6),
                                  (b, 0.9)])
    data_b2 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), 0.9),
                                  (a + (2 / 3) * (b - a), 0.6),
                                  (b, 0.2)])
    data_b3 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), my_k),
                                  (a + (2 / 3) * (b - a), 2 * my_k),
                                  (b, my_k)])
    data_b4 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), 20 * my_k),
                                  (a + (2 / 3) * (b - a), my_k),
                                  (b, 20 * my_k)])

    D1, y1 = data_b1.points, data_b1.answer
    D2, y2 = data_b2.points, data_b2.answer
    D3, y3 = data_b3.points, data_b3.answer
    D4, y4 = data_b4.points, data_b4.answer
    plt.figure()
    plt.plot(D1, y1, color='red', label='k1<k2<k3')
    plt.plot(D2, y2, color='green', label='k1>k2>k3')
    plt.plot(D3, y3, color='blue', label='k1=k, k2=2k, k3=k')
    plt.plot(D4, y4, color='yellow', label='k1=20k, k2=k, k3=20k')
    plt.title('Задание 2 пункт 4б')
    plt.grid(True)
    plt.legend()
    plt.show()

    # 5
    def delta_1(x):
        if x > (a + (b - a) * 0.5):
            return POWER
        return 0

    def delta_2(x):
        p = 0
        if x > (a + (b - a) / 3):
            p = POWER5
        if x > (a + 2 * (b - a) / 3):
            p += POWER5
        if p != 0:
            return p
        return 0

    def delta_3(x):

        p = 0
        if x > (a + (b - a) / 3):
            p += POWER_1
        if x > (a + 2 * (b - a) / 3):
            p += POWER_2
        if p != 0:
            return p
        return 0

    def delta_4(x):
        p = 0
        if x > (a + (b - a) * 0.2):
            p = POWER_3
        if x > (a + (b - a) * 0.8):
            p += POWER_4
        if p != 0:
            return p
        return 0

    data_c1 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(b, my_k)], delta_1)

    data_c2 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(b, my_k)], delta_2)
    data_c3 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(b, my_k)], delta_3)
    data_c4 = Util.differences_method(ITER_COUNT, a, b, u_a, u_b, Util.func_for_partition_2,
                                 [(b, my_k)], delta_4)

    D1, y1 = data_c1.points, data_c1.answer
    D2, y2 = data_c2.points, data_c2.answer
    D3, y3 = data_c3.points, data_c3.answer
    D4, y4 = data_c4.points, data_c4.answer
    plt.figure()
    plt.plot(D1, y1, color='red', label='источник в середине')
    plt.plot(D2, y2, color='green', label='одинаковые источники симметрично')
    plt.plot(D3, y3, color='yellow', label='разные источники симметрично')
    plt.plot(D4, y4, label='Разные источники на 0.2 и 0.8')
    plt.title('Задание 2 пункт 5')
    plt.legend()
    plt.grid(True)
    plt.show()
def task3():
    a = 0.1
    b = 1.1
    ua = lambda t: 2.
    ub = lambda t: 4.
    k = lambda x: x
    f = lambda x: x**3 +  2.
    h = 0.05
    t = 0.001
    K = int((b - a)/h) + 1
    T = 501
    M = np.zeros(shape=(T, K))
    X = np.linspace(a, b, K)
    phi = lambda x:  x**3 +  2.

    M[:,0] = np.array([ua(i) for i in np.linspace(0, T, T)])
    M[:,-1] = np.array([ub(i) for i in np.linspace(0, T, T)])
    M[0,:] = np.array([phi(xi) for xi in np.linspace(a, b, K)])
    for i in range(1, T):
        for j in range(1, K-1):
            xj = a + j*h
            M[i][j] = k(xj + h/2)*M[i-1][j+1]*t/(h*h) + \
                      (1 - (k(xj + h/2) + k(xj - h/2))*t/(h*h)) * M[i-1][j] + \
                      k(xj - h/2)*M[i-1][j-1]*t/(h*h) + \
                      t*f(xj)*(1 - np.exp(-i*t))
    print(M)

    for i in range(0, 21, 2):
        plt.plot(X, M[i], label=i)
    plt.legend()
    plt.show()
def task4():
    a = -1
    b = 1
    ua = lambda t: 1
    ub = lambda t: 1
    k = 0.5
    f = lambda x: 0
    phi = lambda x: np.abs(x)
    h = (b - a) / 50
    t = 0.5 * h*h /k
    T = 0.4
    nK = int((b - a)/h) + 1
    nT = int(T/t)+1
    X = np.linspace(a, b, nK)
    M = np.zeros(shape=(nT, nK))
    M[:,0] = np.array([ua(i) for i in np.linspace(0, T, nT)])
    M[:,-1] = np.array([ub(i) for i in np.linspace(0, T, nT)])
    M[0,:] = np.array([phi(xi) for xi in np.linspace(a, b, nK)])
    #print(M)
    for i in range(1, nT):
        for j in range(1, nK-1):
            xj = a + j*h
            M[i][j] = k * M[i-1][j+1]*t/(h*h) + \
                      (1 - 2*k*t/(h*h)) * M[i-1][j] + \
                      k*M[i-1][j-1]*t/(h*h) + \
                      t*f(xj)
    for i in range(0, nT, 50):
        plt.plot(X, M[i], label=i)
    plt.legend()
    plt.show()
if __name__=='__main__':
    # task1()
    task2()
    task3()
    task4()