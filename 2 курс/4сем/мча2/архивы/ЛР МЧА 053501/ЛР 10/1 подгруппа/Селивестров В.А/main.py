import numpy as np
import matplotlib.pyplot as plt

def main():
    epsilon = 1e-3

    #task
    m = 2.0; a = 0.5
    func = lambda x, y: (a * (1 - y**2)) / ((1 + m) * x**2 + y**2 + 1)
    vals = (0, 0)
    adams(func, [0, 1], vals, epsilon)

    # tests
    print("Test 1: y' = x^2 - 2y")
    func = lambda x, y: x**2 - 2*y
    vals = (0, 1)
    adams(func, [0, 1], vals, epsilon)
    
    print("Test 2: y' = 3x^2 + x^2 * exp(x^3)")
    func = lambda x, y: 3 * x**2 * y + x**2 * np.exp(x**3)
    vals = (0, 0)
    adams(func, [0, 1], vals, epsilon)
    
    print("Test 3: y' = cos(x) - y")
    func = lambda x, y: np.cos(x) - y
    vals = 0, 0.5
    adams(func, [0, 1], vals, epsilon)



def add_points(f, initial_value, h):
    points = [[initial_value[0]], [initial_value[1]]]
    points[0].append(points[0][0] + h)
    k = []
    k.append(h * f(points[0][0], points[1][0]))
    k.append(h * f(points[0][0] + h / 2, points[1][0] + k[0] / 2))
    k.append(h * f(points[0][0] + h / 2, points[1][0] + k[1] / 2))
    k.append(h * f(points[0][0] + h, points[1][0] + k[2]))
    points[1].append(points[1][0] + (1 / 6) * (k[0] + k[3] + 2 * (k[1] + k[2])))
    return points


def get_diff(f, h, y_old, x_old):
    size = len(y_old)

    dY = np.array([y_old[i] - (y_old[i] + h * f(x_old[i], y_old[i])) for i in range(1, size)])
    dY = abs(dY)
    return dY.max()


def adams(f, _range_, initial_value, accuracy):
    n = 2
    h = (_range_[1] - _range_[0]) / n
    points = add_points(f, initial_value, h)

    for i in range(int(n) - 1):
        points[0].append(points[0][i + 1] + h)
        points[1].append(points[1][i + 1] +
                         h * ((3 / 2) * f(points[0][i + 1],
                                          points[1][i + 1]) -
                              (1 / 2) * f(points[0][i], points[1][i])))
    diff = accuracy * 4

    while diff > accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = add_points(f, initial_value, h)
        for i in range(int(n) - 1):
            points[0].append(points[0][i + 1] + h)
            points[1].append(points[1][i + 1] +
                             h * ((3 / 2) * f(points[0][i + 1],
                                              points[1][i + 1]) -
                                  (1 / 2) * f(points[0][i], points[1][i])))
        diff = get_diff(f, h, points_temp[1], points_temp[0])


    print("Метод Адамса: ")
    print("Число отрезков:", n)
    print("Погрешность:", diff)
    plt.title("Метод Адамса")
    plt.plot(points[0], points[1], color='r')
    plt.show()

if __name__ == "__main__":
    main()