#!/usr/bin/env python
# coding: utf-8

# In[375]:


import numpy as np
import sympy as sp

from sympy.solvers.solveset import linsolve
from sympy import init_printing
import matplotlib.pyplot as plt
from IPython.display import display


# In[376]:


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


# In[403]:


variant = 8
A = np.sin(variant)
B = np.cos(variant)
N = 6
left = -1
right = 1
an = [sp.symbols(f"a{i}") for i in range(N + 1)]

x = sp.symbols("x")

px = 0

qx = (1 + B * x ** 2) / A

fx = -1 / A


# In[ ]:





# In[ ]:





# In[404]:


def get_phi(n):
    return x ** n * (1 - x ** 2)


# In[405]:


def get_yn():
    expr = get_phi(0)
    for i in range(1, N + 1):
        expr = expr + get_phi(i) * an[i]
    return expr


# In[406]:


def get_discrepancy():
    return sp.diff(get_yn(), x, 2) + px * sp.diff(get_yn(), x) + qx * get_yn() - fx


# In[407]:


def get_result_expression(an_values):
    return get_yn().subs(list(zip(an[1:], an_values)))


# In[408]:


def collocation_method():
    step = (right - left) / (N - 1)
    points = [left + step * i for i in range(N)]
    equations = [get_discrepancy().subs(x, value) for value in points]
    res = linsolve(equations, an[1:])
    res = list(res)[0]
    plot(get_result_expression(res), left, right)
    discrepancy_expr = get_discrepancy().subs(list(zip(an[1:], res)))
    plot(discrepancy_expr, left, right)


# In[409]:


collocation_method()


# In[416]:


def galerkin_method():
    equations = [sp.integrate(sp.Mul(get_discrepancy(), get_phi(i)), (x, left, right)) for i in range(1, N + 1)]
    res = linsolve(equations, an[1:])
    res = list(res)[0]
    plot(get_result_expression(res), left, right)
    discrepancy_expr = get_discrepancy().subs(list(zip(an[1:], res)))
    print(discrepancy_expr.subs(x, -1))
    print(discrepancy_expr.subs(x, 1))
    plot(discrepancy_expr, left, right)
    


# In[417]:


galerkin_method()


# In[412]:


def integral_mnk():
    equations = [sp.integrate(sp.Mul(get_discrepancy(), sp.diff(get_discrepancy(), an[i])), (x, left, right)) for i in range(1, N + 1)]
    res = linsolve(equations, an[1:])
    res = list(res)[0]
    plot(get_result_expression(res), left, right)
    discrepancy_expr = get_discrepancy().subs(list(zip(an[1:], res)))
    plot(discrepancy_expr, left, right)


# In[413]:


integral_mnk()


# In[414]:


def discrete_mnk():
    def summ():
        res = 0
        M = N + 1
        step = (right - left) / (M - 1)
        for i in range(1, M + 1):
            xx = left + step * (i - 1)
            res = res + get_discrepancy().subs(x, xx) ** 2
        return res
    
    s = summ()
    
    equations = [sp.diff(s, an[i]) for i in range(1, N + 1)]
    res = linsolve(equations, an[1:])
    res = list(res)[0]
    plot(get_result_expression(res), left, right)
    discrepancy_expr = get_discrepancy().subs(list(zip(an[1:], res)))
    plot(discrepancy_expr, left, right)


# In[415]:


discrete_mnk()


# In[ ]:





# In[ ]:




