from sympy import integrate, sqrt, Symbol, Eq, symbols, Function, exp, sin
from sympy.solvers.solveset import linsolve
from sympy.solvers import solve
import matplotlib.pyplot as plt
import matplotlib
import numpy as np

from matplotlib.colors import LinearSegmentedColormap
from matplotlib import cm
import math
from lab2 import sweep_method
import pylab
from mpl_toolkits.mplot3d import Axes3D

matplotlib.use('TkAgg')

from numpy import linspace
from collections import namedtuple

# variant 29

POWER = 5
POWER_ = 25
# POWER_1 = 35
# POWER_2 = 15
# POWER_3 = 10
# POWER_4 = 30
# ITER_COUNT = 150
LINSPACE_SIZE = 100
x = Symbol('x')
k_x = symbols('k_x', cls=Function)

a = 0.5
b = 1.5
u_a = 1
u_b = 1

CONST_K = 13

# my_k = 1


def k(x, c):
    return sqrt(x)


def function_(x):
    return 15 * (x - sqrt(x))


def get_solution(f, k, c, c1, c2):
    first_integral = (-1 * (1 / (k(x, c))) * integrate(f(x), x) + c1).expand()
    second_integral = integrate(first_integral, x) + c2

    return second_integral


def solve_thermal_conductivity_equation(f, k, c, a, b, u_a, u_b):
    c1, c2 = Symbol('c1'), Symbol('c2')

    solution = get_solution(f, k, c, c1, c2)

    c2_val = solve(solution.subs(x, b) - u_b, c2)[0]
    result_equation = solution.subs(c2, c2_val)

    c1_val = solve(result_equation.subs(x, a) - u_a, c1)[0]
    result_equation = result_equation.subs(c1, c1_val)

    return result_equation


def get_y_points(points, step, u_a, u_b, points_k):
    system = []
    system_var = []

    func = function_

    selected_k = 0

    for i in range(1, len(points) - 1):

        y_k0 = Symbol(f"y{i - 1}")
        y_k1 = Symbol(f"y{i}")
        y_k2 = Symbol(f"y{i + 1}")

        if not system_var.__contains__(y_k0):
            system_var.append(y_k0)

        if not system_var.__contains__(y_k1):
            system_var.append(y_k1)

        if not system_var.__contains__(y_k2):
            system_var.append(y_k2)

        if points[i] > points_k[selected_k][0]:
            selected_k += 1

        y_diff_2 = points_k[selected_k][1] * (y_k2 - 2 * y_k1 + y_k0) / (step ** 2)

        res = Eq(y_diff_2, func(points[i]))

        system.append(res)

    res = solve(tuple(system), tuple(system_var))

    return points, list(res.values())


def get_y_points_special_case_python(points, step, u_a, u_b, points_k, f_x=function_):
    system = []
    system_var = []

    points_k_iter = 0
    k = points_k[points_k_iter][1]

    for i in range(1, len(points) - 1):
        if points[i] > points_k[points_k_iter][0]:
            points_k_iter += 1
            k = points_k[points_k_iter][1]

        y_k0 = Symbol(f"y{i - 1}")
        y_k1 = Symbol(f"y{i}")
        y_k2 = Symbol(f"y{i + 1}")

        if not system_var.__contains__(y_k0):
            system_var.append(y_k0)

        if not system_var.__contains__(y_k1):
            system_var.append(y_k1)

        if not system_var.__contains__(y_k2):
            system_var.append(y_k2)

        if i - 1 == 0:
            system.append(Eq(y_k0, u_a))
            y_k0 = u_a

        if i + 1 == len(points) - 1:
            system.append(Eq(y_k2, u_b))
            y_k2 = u_b

        res = Eq(k * (-1 / (step ** 2)) * (y_k0 - 2 * y_k1 + y_k2), f_x(points[i]))

        system.append(res)
    print(system)
    res = solve(tuple(system), tuple(system_var))

    return points, list(res.values())


def func_for_partition_2(yk_m1, yk, yk_p1, h, k=1, func=None):
    if not func:
        func = function_

    func = -k * (yk_p1 - 2 * yk + yk_m1) / h ** 2 - func(x)
    return func


def task_1():
    var_1 = solve_thermal_conductivity_equation(function_, k, 1, a, b, u_a, u_b)
    var_2 = solve_thermal_conductivity_equation(function_,
                                                lambda x, c: c * k(x, c),
                                                2, a, b, u_a, u_b)
    var_3 = solve_thermal_conductivity_equation(function_,
                                                lambda x, c: c * k(x, c),
                                                0.1, a, b, u_a, u_b)
    print(var_1)
    print(var_2)
    print(var_3)

    x_points = linspace(a, b, LINSPACE_SIZE)
    y_points_1, y_points_2, y_points_3 = [], [], []

    for i in range(len(x_points)):
        y_points_1.append(var_1.subs(x, x_points[i]))
        y_points_2.append(var_2.subs(x, x_points[i]))
        y_points_3.append(var_3.subs(x, x_points[i]))

    plt.plot(x_points, y_points_1, c='purple', label='c=1')
    plt.plot(x_points, y_points_2, c='orange', label='c=2')
    plt.plot(x_points, y_points_3, c='green', label='c=0.1')

    plt.xlabel(r'$x$', fontsize=14)
    plt.ylabel(r'$u(x)$', fontsize=14)

    plt.grid(True)

    plt.legend()
    plt.show()

    var_4 = solve_thermal_conductivity_equation(function_,
                                                lambda x, c: 1 / k(x, c),
                                                1, a, b, u_a, u_b)

    print(var_4)
    y_points_4 = [var_4.subs(x, point) for point in x_points]

    plt.plot(x_points, y_points_1, c='purple', label='u(x) -- 1 case')
    plt.plot(x_points, y_points_4, c='orange', label='u(x) -- 4 case')

    plt.xlabel(r'$x$', fontsize=14)
    plt.ylabel(r'$u(x)$', fontsize=14)

    plt.grid(True)

    plt.legend()
    plt.show()

    var_5 = solve_thermal_conductivity_equation(function_,
                                                k,
                                                1, a, b, -u_a, u_b)
    var_6 = solve_thermal_conductivity_equation(function_,
                                                k,
                                                1, a, b, u_a, -u_b)
    var_7 = solve_thermal_conductivity_equation(function_,
                                                k,
                                                1, a, b, -u_a, -u_b)
    print(var_5)
    print(var_6)
    print(var_7)

    y_points_5 = [var_5.subs(x, point) for point in x_points]
    y_points_6 = [var_6.subs(x, point) for point in x_points]
    y_points_7 = [var_7.subs(x, point) for point in x_points]

    plt.plot(x_points, y_points_5, c='purple', label='u(x) -- 5 case')
    plt.plot(x_points, y_points_6, c='orange', label='u(x) -- 6 case')
    plt.plot(x_points, y_points_7, c='green', label='u(x) -- 7 case')

    plt.xlabel(r'$x$', fontsize=14)
    plt.ylabel(r'$u(x)$', fontsize=14)

    plt.grid(True)

    plt.legend()
    plt.show()


def task_2():
    n = 150

    h = (b - a) / n

    points = linspace(a, b, n).tolist()

    points_x_1, points_y_1 = get_y_points_special_case_python(points, h, u_a, u_b, [(0.5 * (b + a), 0.01), (b, 150)])
    points_x_2, points_y_2 = get_y_points_special_case_python(points, h, u_a, u_b, [(0.5 * (b + a), 150), (b, 0.01)])

    plt.plot(points_x_1, points_y_1, color='green', label='k1 << k2')
    plt.plot(points_x_2, points_y_2, color='orange', label='k1 >> k2')

    plt.grid(True)
    plt.legend()

    plt.show()

    points_x_3, points_y_3 = get_y_points_special_case_python(points, h, u_a, u_b, [(a + (b - a) / 3, 0.3),
                                                                                    (a + 2 * (b - a) / 3, 0.6),
                                                                                    (b, 0.9)])
    points_x_4, points_y_4 = get_y_points_special_case_python(points, h, u_a, u_b, [(a + (b - a) / 3, 0.9),
                                                                                    (a + 2 * (b - a) / 3, 0.6),
                                                                                    (b, 0.3)])
    points_x_5, points_y_5 = get_y_points_special_case_python(points, h, u_a, u_b, [(a + (b - a) / 3, CONST_K),
                                                                                    (a + 2 * (b - a) / 3, 2 * CONST_K),
                                                                                    (b, CONST_K)])
    points_x_6, points_y_6 = get_y_points_special_case_python(points, h, u_a, u_b, [(a + (b - a) / 3, 20 * CONST_K),
                                                                                    (a + 2 * (b - a) / 3, CONST_K),
                                                                                    (b, 20 * CONST_K)])

    plt.plot(points_x_3, points_y_3, color='green', label='k1 < k2 < k3')
    plt.plot(points_x_4, points_y_4, color='orange', label='k1 > k2 > k3')
    plt.plot(points_x_5, points_y_5, color='violet', label='k1=k; k2=2k; k3=k')
    plt.plot(points_x_6, points_y_6, color='blue', label='k1=20k; k2=k; k3=20k')

    plt.grid(True)
    plt.legend()

    plt.show()

    def delta_1(x):
        if x > (a + (b - a) * 0.5):
            return POWER
        return 0

    def delta_2(x):
        p = 0
        if x > (a + (b - a) / 3):
            p = POWER
        if x > (a + 2 * (b - a) / 3):
            p += POWER
        if p != 0:
            return p
        return 0

    def delta_3(x):
        p = 0
        if x > (a + (b - a) / 3):
            p += POWER
        if x > (a + 2 * (b - a) / 3):
            p += POWER_
        if p != 0:
            return p
        return 0

    def delta_4(x):
        p = 0
        if x > (a + (b - a) * 0.2):
            p = POWER
        if x > (a + (b - a) * 0.8):
            p += POWER
        if p != 0:
            return p
        return 0

    def delta_5(x):
        p = 0
        if x > (a + (b - a) * 0.2):
            p = POWER
        if x > (a + (b - a) * 0.8):
            p += POWER_
        if p != 0:
            return p
        return 0

    points_x_7, points_y_7 = get_y_points_special_case_python(points, h, u_a, u_b, [(b, 0.9)], delta_1)
    points_x_8, points_y_8 = get_y_points_special_case_python(points, h, u_a, u_b, [(b, 0.9)], delta_2)
    points_x_9, points_y_9 = get_y_points_special_case_python(points, h, u_a, u_b, [(b, 0.9)], delta_3)
    points_x_10, points_y_10 = get_y_points_special_case_python(points, h, u_a, u_b, [(b, 0.9)], delta_4)
    points_x_11, points_y_11 = get_y_points_special_case_python(points, h, u_a, u_b, [(b, 0.9)], delta_5)

    plt.plot(points_x_7, points_y_7, color='green', label='in the middle of the segment [a,b]')
    plt.plot(points_x_8, points_y_8, color='orange', label='similar power, symmetrical about the middle of the segment')
    plt.plot(points_x_9, points_y_9, color='violet', label='different power, symmetrical about the middle of the segment')
    plt.plot(points_x_10, points_y_10, color='blue', label='similar power, asymmetrical about the middle of the segment')
    plt.plot(points_x_11, points_y_11, color='red', label='different power, asymmetrical about the middle of the segment')

    plt.grid(True)
    plt.legend()

    plt.show()

    return


if __name__ == "__main__":
    task_1()
    # task_2()
    # task_3()
    # task_4()
