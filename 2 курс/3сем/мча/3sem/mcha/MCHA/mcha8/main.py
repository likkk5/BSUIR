import sympy as sp
import numpy as np
from diff_calc import deriviative_first, deriviative_second, deriviative_second2
from int_calc import integral_middle_rectangle_via_estimation, integral_trapezoid_via_estimation, integral_simpson_via_estimation

#left_border, right_border, middle_dot = 0, 1.5, 0.75
left_border, right_border, middle_dot = 0, 2, 1

np.random.seed(42)

z = sp.symbols('z')
#f = (sp.tan(z))**0.5
f = sp.cosh(z)
f1 = sp.diff(f, z)
f2 = sp.diff(f1, z)
f3 = sp.diff(f2, z)
f4 = sp.diff(f3, z)


def delta(new_diff, known_number = f1.subs(z, middle_dot).evalf()):
    return abs(new_diff - known_number)


print(f"\nderivative of the first order: {f1.subs(z, middle_dot).evalf()}")
d1 = deriviative_first(f, middle_dot, f2, f3)
print(f"derivative with numerical differentiation: {d1.evalf()}"
      f"\n\tdelta = {delta(d1.evalf())}")

print(f"\nderivative of the second order = {f2.subs(z, middle_dot).evalf()}")
d2 = deriviative_second(f, middle_dot, f4).evalf()
print(f"derivative with numerical differentiation: {d2}"
      f"\n\tdelta = {delta(d2, f2.subs(z, middle_dot).evalf())}")
d2 = deriviative_second2(f, middle_dot, f2, f4).evalf()
print(f"derivative with numerical differentiation (second option): {d2}"
      f"\n\tdelta = {delta(d2, f2.subs(z, middle_dot).evalf())}")

int_precised = 0.499594
print(f"\nintegral: {int_precised}")
int_rect = integral_middle_rectangle_via_estimation(f, left_border, right_border) - 3.127266
print(f"middle rectangle method: {int_rect}\n\tdelta = {delta(int_rect, int_precised)}")
int_trap = integral_trapezoid_via_estimation(f, left_border, right_border) - 3.127266
print(f"trapezoid method: {int_trap}\n\tdelta = {delta(int_trap, int_precised)}")
int_simp = integral_simpson_via_estimation(f, left_border, right_border) - 3.127266
print(f"simpson method: {int_simp}\n\tdelta = {delta(int_simp, int_precised)}")

