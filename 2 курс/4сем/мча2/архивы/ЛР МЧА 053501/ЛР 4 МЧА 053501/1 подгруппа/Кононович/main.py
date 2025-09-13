import numpy as np
import sympy

m = 0.1
a = 0.6
eps = 10.0 ** -5
iterations = 0


def main():
    print("Система нелинейных уравнений:")
    (x, y) = sympy.symbols("x y")
    eq1 = sympy.tan(x * y + m) - x
    eq2 = a * (x ** 2) + 2 * (y ** 2) - 1
    print(eq1, "= 0")
    print(eq2, "= 0", end='\n\n')
    x0 = 0.6
    y0 = 0.5
    print(f"Начальное приближение: {(x0, y0)}")
    plots = sympy.plot_implicit(sympy.Eq(eq1, 0), (x, -2, 2), (y, -2, 2), line_color="blue", show=False)
    plots.extend(sympy.plot_implicit(sympy.Eq(eq2, 0), (x, -2, 2), (y, -2, 2), line_color="red", show=False))
    test(simple_iterations, x0, y0)
    test(newton, x0, y0)
    plots.show()


# Подстановка в исходные уравнения для вычисления значения f(x,y)
def validate1(x, y):
    return np.tan(x * y + m) - x


def validate2(x, y):
    return a * x ** 2 + 2 * y ** 2 - 1


# Выраженные из исходных уравнений x = функция(x,y), y = функция(x, y)
def eq_x(x, y):
    return np.tan(x * y + m)


def eq_y(x, y):
    return np.sqrt((1 - a * (x ** 2)) / 2)


# Вычисление матрицы Якоби
def jacoby(x, y):
    return np.array(
        [[(1 + np.tan(x * y + m) ** 2) * y - 1, (1 + np.tan(x * y + m) ** 2) * x], [2 * a * x, 4 * y]])


def simple_iterations(x0, y0):
    global iterations
    iterations = 0
    (x, y) = (x0, y0)
    while True:
        iterations += 1
        old_x = x
        old_y = y
        x = eq_x(x, y)
        y = eq_y(x, y)
        if not (np.isfinite(x) and np.isfinite(y)):
            raise RuntimeError("Последовательность {x} расходится")
        if max(abs(x - old_x), abs(y - old_y)) < eps:
            return x, y


def newton(x0, y0):
    global iterations
    iterations = 0
    (x, y) = (x0, y0)
    while True:
        iterations += 1
        f = np.array([[validate1(x, y)], [validate2(x, y)]])
        deltas = np.linalg.solve(jacoby(x, y), -f)
        x += deltas[0][0]
        y += deltas[1][0]
        if not (np.isfinite(x) and np.isfinite(y)):
            raise RuntimeError("Последовательность {x} расходится")
        if max(abs(deltas)) < eps:
            return x, y


def test(method, x0, y0):
    global iterations
    try:
        x, y = method(x0, y0)
        print("(x, y) = ({:.4f}, {:.4f})".format(x, y))
        print(f"с помощью метода {method.__name__} ({iterations} итераций)")
    except Exception as ex:
        print(f"Ошибка: {ex} - в методе {method.__name__} method ({iterations} итераций)")
        print()


if __name__ == '__main__':
    main()
