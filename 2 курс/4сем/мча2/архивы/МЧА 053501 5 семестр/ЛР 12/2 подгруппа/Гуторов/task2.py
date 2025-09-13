# from sympy import Symbol, diff, sin, cos, series, exp, symbols, Function, Eq, dsolve, linsolve, solve, integrate, isprime, cosh, sinh
# import numpy as np
# import math
#
# import matplotlib.pyplot as plt
# import matplotlib
# matplotlib.use('TkAgg')
#
# variant = 29
#
# f = symbols('f', cls=Function)
# a0, a1, a2, a3, a4, x = symbols('a0 a1 a2 a3 a4 x')
#
# x_down, x_up = 0, 1
# y_down, y_up = 0, -1
#
#
# def get_points(n):
#     step = (x_up - x_down) / n
#     curr = x_down
#     points = [curr]
#
#     while round(curr, 10) + step <= x_up:
#         curr += step
#         points.append(round(curr, 10))
#
#     return points, step
#
#
# def get_y_points(points, step):
#     system = []
#     system_var = []
#
#     func = function_to_solve()
#
#     for i in range(1, len(points) - 1):
#         y_k0 = Symbol(f"y{i - 1}")
#         y_k1 = Symbol(f"y{i}")
#         y_k2 = Symbol(f"y{i + 1}")
#
#         if not system_var.__contains__(y_k0):
#             system_var.append(y_k0)
#
#         if not system_var.__contains__(y_k1):
#             system_var.append(y_k1)
#
#         if not system_var.__contains__(y_k2):
#             system_var.append(y_k2)
#
#         if points[i - 1] == x_down:
#             system_var.append(y_k0)
#             system.append(Eq(y_k0, y_down))
#             y_k0 = y_down
#
#         if points[i + 1] == x_up:
#             system_var.append(y_k2)
#             system.append(Eq(y_k2, y_up))
#             y_k2 = y_up
#
#         y_diff_1 = (y_k2 - y_k0) / (2 * step)
#         y_diff_2 = (y_k2 - 2 * y_k1 + y_k0) / (step ** 2)
#
#         res = Eq(y_diff_2, func.rhs.subs(f(x).diff(x), y_diff_1).subs(f(x), y_k1).subs(x, points[i]))
#         res1 = Eq(res.lhs - res.rhs, 0)
#
#         system.append(res1)
#
#     res = solve(tuple(system), tuple(system_var))
#
#     return points, list(res.values())
#
#
# # p(x) > 0
# def get_y_points_special_case(points, step, p_x, f_x):
#     system = []
#     system_var = []
#     a_koeff = []
#     b_koeff = []
#     c_koeff = []
#     d_koeff = []
#
#     for i in range(1, len(points) - 1):
#         y_k0 = Symbol(f"y{i - 1}")
#         y_k1 = Symbol(f"y{i}")
#         y_k2 = Symbol(f"y{i + 1}")
#
#         if not system_var.__contains__(y_k0):
#             system_var.append(y_k0)
#
#         if not system_var.__contains__(y_k1):
#             system_var.append(y_k1)
#
#         if not system_var.__contains__(y_k2):
#             system_var.append(y_k2)
#
#         if points[i - 1] == x_down:
#             system.append(Eq(y_k0, y_down))
#             system_var.append(y_k0)
#             y_k0 = y_down
#
#         if points[i + 1] == x_up:
#             system.append(Eq(y_k2, y_up))
#             system_var.append(y_k2)
#             y_k2 = y_up
#
#         b_koeff.append((-(2 + step ** 2 * p_x)).subs(x, points[i]))
#
#         res = Eq(y_k0 - (2 + step ** 2 * p_x) * y_k1 + y_k2, step ** 2 * f_x).subs(x, points[i])
#
#         d_koeff.append(res.rhs)
#         a_koeff.append(1)
#         c_koeff.append(1)
#
#         if 2 + p_x.subs(x, points[i]) <= 2:
#             raise ValueError("Non-observance of the conditions for the predominance of diagonal elements")
#
#         system.append(res)
#
#     res_sweep_method = sweep_method(a_koeff, b_koeff, c_koeff, d_koeff)
#
#     # res = solve(tuple(system), tuple(system_var))
#     res_sweep_method.insert(0, y_down)
#     res_sweep_method.append(y_up)
#
#     return points, res_sweep_method
#     # list(res.values())
#     #res_sweep_method
#
#
# def get_y_points_special_case_python(points, step, p_x, f_x):
#     system = []
#     system_var = []
#
#     for i in range(1, len(points) - 1):
#         y_k0 = Symbol(f"y{i - 1}")
#         y_k1 = Symbol(f"y{i}")
#         y_k2 = Symbol(f"y{i + 1}")
#
#         if not system_var.__contains__(y_k0):
#             system_var.append(y_k0)
#
#         if not system_var.__contains__(y_k1):
#             system_var.append(y_k1)
#
#         if not system_var.__contains__(y_k2):
#             system_var.append(y_k2)
#
#         if points[i - 1] == x_down:
#             system.append(Eq(y_k0, y_down))
#             system_var.append(y_k0)
#             y_k0 = y_down
#
#         if points[i + 1] == x_up:
#             system.append(Eq(y_k2, y_up))
#             system_var.append(y_k2)
#             y_k2 = y_up
#
#         res = Eq(y_k0 - (2 + step ** 2 * p_x) * y_k1 + y_k2, step ** 2 * f_x).subs(x, points[i])
#
#         if 2 + p_x.subs(x, points[i]) <= 2:
#             raise ValueError("Non-observance of the conditions for the predominance of diagonal elements")
#
#         system.append(res)
#
#     res = solve(tuple(system), tuple(system_var))
#
#     return points, list(res.values())
#
#
# def sweep_method(a_k, b_k, c_k, d_k):
#     i = 0
#     y = [b_k[i]]
#     alpha = [-c_k[i] / y[i]]
#     betta = [-d_k[i] / y[i]]
#
#     while i + 1 < len(a_k) - 1:
#         i += 1
#         y.append(b_k[i] + a_k[i] * alpha[i-1])
#         alpha.append(-c_k[i] / y[i])
#         betta.append((d_k[i] - a_k[i] * betta[i-1]) / y[i])
#
#     i += 1
#
#     y.append(b_k[i] + a_k[i]*alpha[i-1])
#     betta.append((d_k[i] - a_k[i]*betta[i-1]) / y[i])
#
#     x = [0] * len(a_k)
#     x[i] = betta[i]
#     while i > 0:
#         i -= 1
#         x[i] = (alpha[i]*x[i + 1]+betta[i])
#
#     return x
#
#
# # def function_to_solve():
# #     return Eq(f(x).diff(x, x), (-1 - (1 + np.cos(variant) * x ** 2) * f(x)) / np.sin(variant))
#
# def function_to_solve():
#     return Eq(f(x).diff(x, x), (2*x + f(x)))
#
#
# def show_plots(n):
#     n = 50
#     x_points, h = get_points(n)
#
#     p_x = (1 + np.cos(variant) * x ** 2) / np.sin(variant)
#     f_x = -1 / np.sin(variant)
#
#     x2, y2 = get_y_points_special_case(x_points, h, -p_x, f_x)
#     print(x2)
#     print(y2)
#
#     n = 10
#     x_points, h = get_points(n)
#     x3, y3 = get_y_points_special_case_python(x_points, h, -p_x, f_x)
#     print(x3)
#     print(y3)
#
#     # plt.plot(x1, y1, label=r'f_1(x) - default case')
#     plt.plot(x2, y2, label=r'f_2(x) - special case(sweep method)')
#     plt.plot(x3, y3, label=r'f_3(x) - special case(python)')
#
#     plt.xlabel(r'$x$', fontsize=14)
#     plt.ylabel(r'$f(x)$', fontsize=14)
#
#     plt.grid(True)
#     plt.legend(loc='best', fontsize=12)
#
#     plt.show()
#
#     return
#
#
# def get_norm_as_max(y_points, h):
#     y_max = y_points[0]
#     for y in y_points:
#         if y_max < abs(y):
#             y_max = abs(y)
#
#     return y_max
#
#
# def get_norm(y_points, h):
#     res = (sum(y ** 2 * h for y in y_points)) ** (1 / 2)
#
#     return res
#
#
# def get_number_of_points(precision):
#     n = 4
#     x_points, h = get_points(n)
#     print(f"Step: {h}")
#
#     x_p_prev, y_p_prev = get_y_points(x_points, h)
#     y_prev_norm = get_norm_as_max(y_p_prev, h)
#
#     print(y_prev_norm)
#
#     n *= 2
#     x_points, h = get_points(n)
#     print(f"Step: {h}")
#
#     x_p_next, y_p_next = get_y_points(x_points, h)
#     y_next_norm = get_norm_as_max(y_p_next, h)
#
#     print(y_next_norm)
#
#     while abs(y_next_norm - y_prev_norm) > precision:
#         y_prev_norm = y_next_norm
#
#         n *= 2
#         x_points, h = get_points(n)
#         print(f"Step: {h}")
#
#         x_p_next, y_p_next = get_y_points(x_points, h)
#         y_next_norm = get_norm_as_max(y_p_next, h)
#
#         print(y_next_norm)
#
#     print(f"Number of points: {n} -- {abs(y_next_norm - y_prev_norm)}")
#
#
# if __name__ == '__main__':
#     # p_x = (1 + np.cos(variant) * x ** 2) / np.sin(variant)
#     # f_x = -1 / np.sin(variant)
#
#     # p_x = 5 * np.sin(x)
#     # q_x = 5 * (1 - x**2)
#     # f_x = 5 * np.exp(0.5 * x)
#     # get_number_of_points(0.2)
#     n = 4
#     x_points, h = get_points(n)
#     print(f"Step: {h}")
#
#     diffeq = function_to_solve()
#     # Вызов функции dsolve, возврат объекта Eq, точность управления подсказкой
#     fun = (sinh(x) / sinh(1)) - 2*x
#     func_y = [fun.subs(x, i) for i in x_points]
#     x_p_prev, y_p_prev = get_y_points(x_points, h)
#     plt.plot(x_p_prev, y_p_prev, label=r'f(x) - approximate', color=(0.9, 0.2, 0.6, 0.5), linewidth=6)
#     plt.plot(x_points, func_y, label=r'f(x) - exact')
#     plt.xlabel(r'$x$', fontsize=14)
#     plt.ylabel(r'$f(x)$', fontsize=14)
#
#     plt.grid(True)
#     plt.legend(loc='best', fontsize=12)
#     plt.show()
#
#
#
