import sympy as sp

z = sp.symbols('z')

left_border_1, right_border_1, middle_dot_1 = 1, 4, 2.5
f_first=5*z**4

left_border_2, right_border_2, middle_dot_2 = 0, 5, 2.5
f_second=sp.sinh(z)

left_border_3, right_border_3, middle_dot_3 = 0, 2, 1
f_third=z**4+4*z**3-9*z**2+7.89
