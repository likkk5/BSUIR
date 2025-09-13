from scipy import integrate as inter
import sympy
import functionality
import numpy as np
from sympy import *
import math


def func(y):
    return np.cosh(y)


def main():
    x = Symbol('x')
    y = sympy.cosh(x)
    res = y.diff(x)
    print(res.subs([(x, 1)]))
    res = y.diff(x, 2)
    print(res.subs([(x, 1)]))
    print(functionality.first_derivative(0.001, 1, lambda p: np.cosh(p)))
    print(functionality.first_derivative_2(0.001, 1, lambda p: np.cosh(p)))
    print(functionality.second_derivative(0.001, 1, lambda p: np.cosh(p)))
    print(functionality.second_derivative2(0.001, 1, lambda p: np.cosh(p)))
    res = inter.quad(func, 0, 2)
    print("Res: ", res[0])
    n = 14
    print(n, functionality.sympson(0, 2, n, y))
    n = 1796
    print(n, functionality.trapezoid_method(0, 2, n, lambda p: np.cosh(p)))
    n = 1869100
    print(n, functionality.rectangle_method(0, 2, n, lambda p: np.cosh(p)))


if __name__ == '__main__':
    main()
