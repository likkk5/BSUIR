import numpy as np


def lagranz(vector_x, vector_y, t):
    if not check_has_solution(vector_x):
        return None
    result = 0
    for i in range(len(vector_y)):
        p1 = 1
        p2 = 1
        for j in range(len(vector_x)):
            if i == j:
                p1 *= 1
                p2 *= 1
            else:
                p1 = p1 * (t - vector_x[j])
                p2 = p2 * (vector_x[i] - vector_x[j])
        result = result + vector_y[i] * (p1/p2)
    return result


def newton(vector_x, vector_y, t):
    if not check_has_solution(vector_x):
        return None
    result = 0
    for i in range(len(vector_y)):
        p1 = 1
        for j in range(0, i):
            p1 *= (t - vector_x[j])

        f_div = 0

        for j in range(i + 1):
            p2 = 1
            for k in range(i + 1):
                if j != k:
                    p2 *= (vector_x[j]-vector_x[k])
            f_div += vector_y[j] / p2

        result = result + p1 * f_div
    return result


def check_has_solution(vector_x):
    calc = 1
    for i in range(len(vector_x)):
        for j in range(len(vector_x)):
            if i < j:
                calc *= (vector_x[j] - vector_x[i])
    if calc == 0:
        return False
    return True


def best_approximation(x, y, power=11, point=0.47):
    for i in range(1, power):
        f = (np.poly1d(np.polyfit(x, y, i)))
        print(i, f(point))


def diff_approximation_inter(x, y, power=11, point=0.47):
    for i in range(1, power):
        f = (np.poly1d(np.polyfit(x, y, i)))
        print(i, f(point))
        print(abs(f(point) - lagranz(x, y, point)))
