import math

import numpy as np


def default_values():
    vector_x = []
    step = 0
    for i in range(11):
        vector_x.append(round(step, 1))
        step += 0.1
    np.array(vector_x)
    vector_p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
    return input_values(vector_x, vector_p)


def input_values(vector_x, vector_p):
    k = 12
    m = 3.96
    vector_y = [round(vector_p[i] + ((-1)**k) * m, 2) for i in range(len(vector_x))]
    print(vector_x)
    print(vector_y)
    np.array(vector_y)
    return vector_x, vector_y


def input_value1():
    x = np.array([2, 5, -6, 7, 4, 3, 8, 9, 1, -2], dtype=float)
    y = np.array([-1, 77, -297, 249, 33, 9, 389, 573, -3, -21], dtype=float)
    return x, y


def input_value2():
    x = np.array([0, 1, 2, 3], dtype=float)
    y = np.array([-2, -5, 0, -4], dtype=float)
    print(x, y)
    return x, y


def input_value3():
    x = np.array([-1.5, -0.75, 0, 0.75, 1.5], dtype=float)
    y = np.array([math.tan(x[i]) for i in range(len(x))], dtype=float)
    print(x, y)
    return x, y
