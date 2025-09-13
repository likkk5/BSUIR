#-*-coding:windows-1251-*-

import sympy as sp
import numpy as np
from diff_calc import deriviative_first, deriviative_second, deriviative_second2
from int_calc import integral_middle_rectangle_via_estimation, integral_trapezoid_via_estimation, integral_simpson_via_estimation
import tests

left_border, right_border, middle_dot = 0, 2, 1

z = sp.symbols('z')
f=sp.cosh(z)
f1 = sp.diff(f, z)
f2 = sp.diff(f1, z)
f3 = sp.diff(f2, z)
f4 = sp.diff(f3, z)

# left_border, right_border, middle_dot = tests.left_border_3,tests.right_border_3, tests.middle_dot_3
# z = sp.symbols('z')
# f=tests.f_third
# f1 = sp.diff(f,z)
# f2 = sp.diff(f1, z)
# f3 = sp.diff(f2, z)
# f4 = sp.diff(f3, z)

int_precised=sp.integrate(f,z).subs(z,right_border).evalf()

def delta(new_diff, known_number = f1.subs(z, middle_dot).evalf()):
    return abs(new_diff - known_number)


print(f"\n����������� ������� ������� (���������� �������): {f1.subs(z, middle_dot).evalf()}")
d1 = deriviative_first(f, middle_dot, f2, f3)
print(f"����������� ������� �������: {d1.evalf()}"
      f"\n\����������� = {delta(d1.evalf())}")

print(f"\n����������� ������� ������� (���������� �������): {f2.subs(z, middle_dot).evalf()}")
d2 = deriviative_second(f, middle_dot, f4).evalf()
print(f"����������� ������� �������: {d2}"
      f"\n\����������� = {delta(d2, f2.subs(z, middle_dot).evalf())}")


print(f"\n��������: {int_precised}")
int_rect = integral_middle_rectangle_via_estimation(f, left_border, right_border)
print(f"������� ������� ���������������: {int_rect}\n\t����������� = {delta(int_rect, int_precised)}")
int_trap = integral_trapezoid_via_estimation(f, left_border, right_border) 
print(f"������� ��������: {int_trap}\n\t����������� = {delta(int_trap, int_precised)}")
int_simp = integral_simpson_via_estimation(f, left_border, right_border)
print(f"������� ��������: {int_simp}\n\t����������� = {delta(int_simp, int_precised)}")

