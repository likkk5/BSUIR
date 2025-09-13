import sympy as sp

x = sp.symbols('x')

a_1=-2
b_1=5
n_1=8
point_1=4.1
f_1_expr = sp.sin(x)
f_1 = sp.lambdify(x, f_1_expr, 'numpy')

a_2=-1.5
b_2=1.5
n_2=20
point_2=0.7
f_2_expr = sp.tan(x)
f_2 = sp.lambdify(x, f_2_expr, 'numpy')

a_3=1
b_3=3
n_3=6
point_3=1
f_3_expr = sp.log(x)
f_3 = sp.lambdify(x, f_3_expr, 'numpy')




