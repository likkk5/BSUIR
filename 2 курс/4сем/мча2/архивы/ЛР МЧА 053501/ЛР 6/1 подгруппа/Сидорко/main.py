from numpy import poly1d, polyval, polyfit, linspace, polyder, roots
from matplotlib.pyplot import plot, show
from math import factorial


def lagrange(x_values, y_values):
    res = poly1d([0])
    for i in range(len(x_values)):
        l_i = poly1d([1])
        for j in range(len(x_values)):
            if i == j:
                continue
            l_i *= (poly1d([1, -x_values[j]]) / (x_values[i] - x_values[j]))
        res += (l_i * y_values[i])

    return res


def newton(x_values, y_values):
    divided_diffs = get_divided_differences(x_values, y_values)
    res = poly1d([0])
    for i in range(len(x_values)):
        f = poly1d([1])
        for j in range(i):
            f *= poly1d([1, -x_values[j]])
        res += (f * divided_diffs[0][i])

    return res


def get_divided_differences(x_values, y_values):
    div_diffs = [[0 for i in range(len(x_values) - j)] for j in range(len(x_values))]
    for i in range(len(div_diffs)):
        div_diffs[i][0] = y_values[i]
    for j in range(1, len(x_values)):
        for i in range(len(x_values) - j):
            div_diffs[i][j] = (div_diffs[i + 1][j - 1] - div_diffs[i][j - 1]) / (x_values[i + j] - x[i])

    return div_diffs


def get_square_appr(x_values, y_values):
    return poly1d(polyfit(x_values, y_values, min(8, len(x_values) - 1)))


# def get_interpolation_error(x_values, y_values):
#     div_diffs = get_divided_differences(x_values, y_values)
#     max_diff = max([max(div_diffs[i]) for i in range(len(div_diffs))])
#     w: poly1d = poly1d([1])
#     for x_i in x_values:
#         w *= poly1d([1, -x_i])
#     error = max_diff * w / factorial(len(x_values) + 1)
#     der = polyder(error)
#     max_error = 0.0
#     for root in roots(der):
#         if x_values[0] <= root <= x_values[-1]:
#             max_error = max(max_error, abs(polyval(error, root)))
#
#     return max_error


def plot_(x_values, y_values):
    points_number = 1000
    plot(x_values, y_values, 'g*', markersize=7)
    points_x = linspace(min(x_values), max(x_values), points_number)
    points_y = [polyval(get_square_appr(x_values, y_values), pnt) for pnt in points_x]
    plot(points_x, points_y, color='blue')
    points_y = [polyval(newton(x_values, y_values), pnt) for pnt in points_x]
    plot(points_x, points_y, color='#d62728', linestyle='dashed', linewidth=3)
    show()


if __name__ == '__main__':
    k = 4
    m = 2
    x = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
    y = [p[i] + ((-1) ** k) * m for i in range(len(x))]
    print(y)
    point = 0.47
    # x = [0.0, 0.2, 0.4, 0.6, 0.8, 1.0]
    # y = [0.0, 0.04, 0.16, 0.36, 0.64, 1.0]
    # point = 0.52
    # x = [-1.0, -0.5, 0.0, 0.5, 1.0]
    # y = [-1.0, -0.125, 0.0, 0.125, 1.0]
    # point = 0.25
    # x = [-1.0, -0.6, -0.3, 0.0, 0.3, 0.6, 1.0]
    # y = [-1.56, -0.68, -0.31, 0.0,  0.31, 0.68, 1.56]
    # point = 0.25
    # x = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    # y = [10.00, 5.00, 3.33, 2.50, 2.00, 1.67, 1.43, 1.25, 1.11, 1.00]
    # point = 0.35


    print("Интерполяционный многочлен Лагранжа:")
    pol_lagrange = lagrange(x, y)
    print(pol_lagrange)
    print(f"\nЗначение в точке x = {point}:   {polyval(pol_lagrange, point):.5f}")

    print("\n\nИнтерполяционный многочлен Ньютона:")
    pol_newton = newton(x, y)
    print(pol_newton)
    print(f"\nЗначение в точке x = {point}:   {polyval(pol_newton, point):.5f}")

    print("\n\nМногочлен наилучшего приближения:")
    pol_square = poly1d(get_square_appr(x, y))
    print(pol_square)
    print(f"\nЗначение в точке x = {point}:   {polyval(pol_square, point):.5f}")

    # print("\n\nПогрешность: " + str(get_interpolation_error(x, y)))

    #
    func = lagrange(x, y) - get_square_appr(x, y)
    der = polyder(func)
    max_error = 0.0
    for root in roots(der):
        if x[0] <= root <= x[-1]:
            max_error = max(max_error, polyval(func, root))
    print(f"\nПогрешность:   {max_error:.5f}")

    print(f"Разность значений многочленов в точке x = {point}:   "
          f"{abs(polyval(pol_newton, point) - polyval(pol_square, point)):.5f}")

    plot_(x, y)
