import sympy as sp

a=0
b=4
n=5
x = sp.symbols('x')
f_expr = sp.sqrt(x)
f = sp.lambdify(x, f_expr, 'numpy')
point=0.5*(b-a)

