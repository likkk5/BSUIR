import numpy as np
import sympy as sp

from sympy.solvers.solveset import linsolve
from sympy import init_printing
import matplotlib.pyplot as plt
from IPython.display import display

def plot(expression, left, right):
    init_printing()
    print("Expression:")
    display(expression)
    NUM_OF_POINTS = 100
    step = (right - left) / (NUM_OF_POINTS - 1)
    xx = [left + step * i for i in range(NUM_OF_POINTS)]
    yy = [expression.subs(x, val) for val in xx]
    
    plt.plot(xx, yy)
    plt.show()



variant = 2
A = 1
B = 1
N = 2
left = -1
right = 1

def an(n=N):
    return [sp.symbols(f"a{i}") for i in range(n + 1)]

x = sp.symbols("x")

px = 0

qx = (1 + B * x ** 2) / A

fx = -1 / A

def get_phi(n):
    return x ** n * (1 - x ** 2)

def get_yn(n=N):
    expr = get_phi(0)
    for i in range(1, n + 1):
        expr = expr + get_phi(i) * an(n)[i]
    return expr

def get_discrepancy(n=N):
    return sp.diff(get_yn(n), x, 2) + px * sp.diff(get_yn(n), x) + qx * get_yn(n) - fx

def get_result_expression(an_values, n=N):
    return get_yn(n).subs(list(zip(an(n)[1:], an_values)))

def collocation_method(n=N):
    step = (right - left) / (n - 1)
    points = [left + step * i for i in range(n)]
    equations = [get_discrepancy(n).subs(x, value) for value in points]
    res = linsolve(equations, an(n)[1:])
    res = list(res)[0]
    return get_result_expression(res, n), get_discrepancy(n).subs(list(zip(an(n)[1:], res)))


def galerkin_method(n=N):
    equations = [sp.integrate(sp.Mul(get_discrepancy(n), get_phi(i)), (x, left, right)) for i in range(1, n + 1)]
    res = linsolve(equations, an(n)[1:])
    res = list(res)[0]
    return get_result_expression(res, n), get_discrepancy(n).subs(list(zip(an(n)[1:], res)))

def integral_mnk(n=N):
    equations = [sp.integrate(sp.Mul(get_discrepancy(n), sp.diff(get_discrepancy(n), an(n)[i])), (x, left, right)) for i in range(1, n + 1)]
    res = linsolve(equations, an(n)[1:])
    res = list(res)[0]
    return get_result_expression(res), get_discrepancy(n).subs(list(zip(an(n)[1:], res)))

def discrete_mnk(n=N):
    def summ():
        res = 0
        M = n + 1
        step = (right - left) / (M - 1)
        for i in range(1, M + 1):
            xx = left + step * (i - 1)
            res = res + get_discrepancy(n).subs(x, xx) ** 2
        return res
    
    s = summ()
    
    equations = [sp.diff(s, an(n)[i]) for i in range(1, n + 1)]
    res = linsolve(equations, an(n)[1:])
    res = list(res)[0]
    return get_result_expression(res, n), get_discrepancy(n).subs(list(zip(an(n)[1:], res)))


def inf(n1):
    r1 = collocation_method(n1)
    print(r1[1].subs(x, -1))
    print(r1[1].subs(x, 1))
    return r1[1]


plot(collocation_method(3)[0], left, right)
