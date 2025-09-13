import numpy as np
import matplotlib.pyplot as plt

def main():
    epsilon = 1e-3

    # task    
    k = 6; m = 1.5; a = 0.5
    func = lambda x, y: (a * (1 - y**2)) / ((1 + m) * x**2 + y**2 + 1)
    vals = (0, 0); 
    eiler_method(func, [0, 1], vals, epsilon)
    eiler_modified_method(func, [0, 1], vals, epsilon)
    runge_method(func, [0, 1], vals, epsilon)
    
    # tests
    print("Test 1: y' = x^2 - 2y")
    func = lambda x, y: x**2 - 2*y
    vals = (0, 1)
    eiler_method(func, [0, 1], vals, epsilon)
    eiler_modified_method(func, [0, 1], vals, epsilon)
    runge_method(func, [0, 1], vals, epsilon)
    
    print("Test 2: y' = 3x^2 + x^2 * exp(x^3)")
    func = lambda x, y: 3 * x**2 * y + x**2 * np.exp(x**3)
    vals = (0, 0)
    eiler_method(func, [0, 1], vals, epsilon)
    eiler_modified_method(func, [0, 1], vals, epsilon)
    runge_method(func, [0, 1], vals, epsilon)
    
    print("Test 3: y' = cos(x) - y")
    func = lambda x, y: np.cos(x) - y
    vals = 0, 0.5
    eiler_method(func, [0, 1], vals, epsilon)
    eiler_modified_method(func, [0, 1], vals, epsilon)
    runge_method(func, [0, 1], vals, epsilon)


def eiler_method(func_, _range_, init_v, accuracy):
    n = 2
    h = (_range_[1] - _range_[0]) / n
    points = [[init_v[0]], [init_v[1]]]
    eiler_points_append(func_, h, n, points)
    diff = accuracy * 4
    while accuracy < diff:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = [[init_v[0]], [init_v[1]]]
        eiler_points_append(func_, h, n, points)
        diff = get_derivative(func_, h, points_temp[1], points_temp[0])
    print("Метод Эйлера: ")
    print("Число отрезков:", n)
    print("Погрешность:", diff)
    plt.title("Метод Эйлера")
    plt.plot(points[0], points[1], color='red')
    plt.show()


def eiler_modified_method(func_, _range_, init_v, accuracy):
    n = 2
    h = (_range_[1] - _range_[0]) / n
    points = [[init_v[0]], [init_v[1]]]
    modified_euler_points_append(func_, h, n, points)
    diff = accuracy * 4
    while diff > accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = [[init_v[0]], [init_v[1]]]
        modified_euler_points_append(func_, h, n, points)
        diff = get_derivative(func_, h, points_temp[1], points_temp[0])
    print("Модифицированный метод Эйлера: ")
    print("Число отрезков:", n)
    print("Погрешность:", diff)
    plt.title("Модифицированный метод Эйлера")
    plt.plot(points[0], points[1], color='red')
    plt.show()


def eiler_points_append(func_, h, n, points):
    for i in range(int(n)):
        points[0].append(points[0][i] + h)
        points[1].append(points[1][i] + h * func_(points[0][i], points[1][i]))


def runge_method(func_, _range_, init_v, accuracy):
    n = 2
    h = (_range_[1] - _range_[0]) / n
    points = [[init_v[0]], [init_v[1]]]
    runge_points_append(func_, h, n, points)
    diff = accuracy * 4
    while diff > accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = [[init_v[0]], [init_v[1]]]
        runge_points_append(func_, h, n, points)
        diff = get_derivative(func_, h, points_temp[1], points_temp[0])
    print("Метод Рунге-Кутта: ")
    print("Число отрезков:", n)
    print("Погрешность:", diff)
    plt.title("Метод Рунге-Кутта")
    plt.plot(points[0], points[1], color='red')
    plt.show()


def runge_points_append(func_, h, n, points):
    for i in range(int(n)):
        points[0].append(points[0][i] + h)
        tmp = []
        tmp.append(h * func_(points[0][i], points[1][i]))
        tmp.append(h * func_(points[0][i] + h / 2, points[1][i] + tmp[0] / 2))
        tmp.append(h * func_(points[0][i] + h / 2, points[1][i] + tmp[1] / 2))
        tmp.append(h * func_(points[0][i] + h, points[1][i] + tmp[2]))
        points[1].append(points[1][i] + (1 / 6) * (tmp[0] + tmp[3] + 2 * (tmp[1] + tmp[2])))


def modified_euler_points_append(func_, h, n, points):
    for i in range(int(n)):
        points[0].append(points[0][i] + h)
        points[1].append(points[1][i] +
                         h * func_(points[0][i] +
                                   h / 2, points[1][i] +
                                   (h / 2) * func_(points[0][i], points[1][i])))

def get_derivative(f, h, old_data_y, old_data_x):
    size = len(old_data_y)
    d_y = abs(np.array([old_data_y[i] - (old_data_y[i] + h * f(old_data_x[i], old_data_y[i])) for i in range(1, size)]))
    return d_y.max()

if __name__ == "__main__":
    main()