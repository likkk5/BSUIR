from scipy import interpolate as inter
import numpy as np
from sympy import *
import matplotlib.pyplot as plt


def func(x):
    return np.sqrt(x)


def get_cubic_interpolation_in_point(x):
    x_points = [0, 1, 2, 3, 4]
    y_points = [np.sqrt(x_points[i]) for i in range(len(x_points))]
    tck = inter.splrep(x_points, y_points)
    return inter.splev(x, tck)


def count_c(dots):
    matrix = [[0 for i in range(len(dots) - 2)] for j in range(len(dots) - 2)]
    vector_d = []
    for i in range(1, len(dots) - 1, 1):
        h_i = abs(dots[i][0] - dots[i - 1][0])
        h_i_next = abs(dots[i + 1][0] - dots[i][0])
        list_with_k = [(h_i / 3),
                       (2 / 3)*h_i_next + (2 / 3)*h_i,
                       h_i_next / 3]
        for j in range(len(list_with_k)):
            if (i - 2 + j >= 0) and (i - 2 + j < len(dots) - 2):
                matrix[i - 1][i - 2 + j] = list_with_k[j]

        y_i_next = dots[i + 1][1]
        y_i = dots[i][1]
        y_i_prev = dots[i - 1][1]

        vector_d.append(((y_i_next-y_i) / h_i_next) -
                        (y_i-y_i_prev)/h_i)

    d_index = 0
    y1 = matrix[0][0]

    y_vector = [y1]

    a_i_prev = (-matrix[0][1]) / y1
    b_i_prev = vector_d[d_index] / y1

    a_vector = [a_i_prev]
    b_vector = [b_i_prev]

    for i in range(1, len(matrix) - 1):
        d_index += 1
        y = matrix[i][i] + matrix[i][i - 1] * a_i_prev
        a_i = (-matrix[i][i + 1]) / y
        b_i = (vector_d[d_index] - matrix[i][i-1] * b_i_prev) / y
        a_vector.append(a_i)
        b_vector.append(b_i)
        a_i_prev = a_i
        b_i_prev = b_i
        y_vector.append(y)
    b_n = matrix[len(matrix) - 1][len(matrix) - 1]
    a_n = matrix[len(matrix) - 1][len(matrix) - 2]
    y = b_n + a_n * a_i_prev
    b_vector.append((vector_d[d_index + 1] - a_n*b_i_prev) / y)

    vector_result = [b_vector[len(b_vector) - 1]]
    j = 0
    for i in range(len(b_vector) - 2, -1, -1):
        vector_result.append(a_vector[i]*vector_result[j]+b_vector[i])
        j += 1

    return vector_result


def count_k(dots):
    vector_res = count_c(dots)
    vector_c = [0 for i in range(len(dots) + 1)]
    for i in range(1, (len(dots) - 1)):
        vector_c[i] = vector_res[i-1]

    vector_a = []
    for i in range(1, len(dots)):
        vector_a.append(dots[i - 1][1])

    vector_b = []
    for i in range(1, len(dots)):
        y_i = dots[i][1]
        y_i_prev = dots[i-1][1]
        h_i = abs(dots[i][0]-dots[i-1][0])
        b_i = (y_i-y_i_prev)/h_i - \
              vector_c[i]*h_i - \
              ((vector_c[i+1]-vector_c[i])*h_i)/3
        vector_b.append(b_i)

    vector_d = []
    for i in range(1, len(dots)):
        h_i = abs(dots[i][0] - dots[i - 1][0])
        vector_d.append((vector_c[i+1]-vector_c[i])/(3*h_i))

    x, s = symbols('x s')
    (x1, y1) = map(list, zip(*dots))

    plt.plot(x1, y1, 'og')
    xplot = np.linspace(min(x1), max(x1), 10 ** 4)

    left = 0
    right = 1
    res = 0
    for i in range(0, len(dots) - 1):
        s = vector_a[i] + vector_b[i] * (x - dots[i][0]) + vector_c[i+1]*((x - dots[i][0]) ** 2) \
            + vector_d[i]*((x - dots[i][0])**3)
        yplot = []
        x_new_cords = []
        for xdot in xplot:
            if (xdot >= left) and (xdot < right):
                yplot.append(s.subs([(x, xdot)]))
                x_new_cords.append(xdot)

        plt.plot(x_new_cords, yplot, 'blue')
        print(s.subs([(x, 2)]))
        print(s)
        left = right
        right += 1

    yplot = [func(xdot) for xdot in xplot]
    plt.plot(xplot, yplot, 'black')
    plt.show()
