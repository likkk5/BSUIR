import numpy
import math


m = 0.1
a = 0.8
eps = 0.0001
iterations = 0


def first_equation(x, y):
    return math.tan(x * y + m) - x

def sec_equation(x, y):
    return a * (x ** 2) + 2 * (y ** 2) - 1

def eq_x(x, y):
    return math.tan(x * y + m)

def eq_y(x, y):
    return math.sqrt((1 - a * (x ** 2)) / 2)

def Jacobi(x, y):
    return numpy.array([[(1 + math.tan(x * y + m) ** 2) * y - 1, (1 + math.tan(x * y + m) ** 2) * x], [2 * a * x, 4 * y]])

def simple_iterations(x0, y0):
    (x, y) = (x0, y0)
    it = 0
    while True:
        prev_x = x
        prev_y = y
        it += 1
        x = eq_x(x, y)
        y = eq_y(x, y)
        if not (math.isfinite(x) and math.isfinite(y)):
            raise RuntimeError("Consistency {x} differs")
        if max(abs(x - prev_x), abs(y - prev_y)) < eps:
            return x, y, it

def newton(x0, y0):
    it = 0
    (x, y) = (x0, y0)
    while True:
        it += 1
        f = numpy.array([[first_equation(x, y)], [sec_equation(x, y)]]) #TODO
        deltas = numpy.linalg.solve(Jacobi(x, y), -f)
        x += deltas[0][0]
        y += deltas[1][0]
        if not (numpy.isfinite(x) and numpy.isfinite(y)):
            raise RuntimeError("Consistency {x} differs")
        if max(abs(deltas)) < eps:
            return x, y, it

def calculate(method, x0, y0):
    (x, y, it) = method(x0, y0)
    print(f"(x, y) = ({x:.4f}, {y:.4f})")
    print("With method ", method.__name__, " (", it, " iterations)")