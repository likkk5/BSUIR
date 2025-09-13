#-*-coding:windows-1251-*-
from sympy.printing.pretty.stringpict import line_width
from lagrange_interpolation import lagrange_poly
from newton_interpolation import newton_poly
import test
import task
import min_squares
from sympy import lambdify, symbols
import numpy as np
import sympy as sp
import matplotlib.pyplot as plt 

x = task.x
y = task.y
point = task.point

x_var = symbols('x')

newton = newton_poly(x, y)
lagrange = lagrange_poly(x, y)

print(f"\tData:\n"
      f"x = {x}\n"
      f"y = {y}")

print('-' * 80)

print(f'\tLagrange interpolation polynomial:\nL(x) = {lagrange}')
print(f'Interpolation point: x = {point}')
print(f'Lagrange poly result on x = {point}\nL({point}) = {float(lagrange.subs(x_var, point)):.4f}')

print('-' * 80)

print(f'\tNewton interpolation polynomial:\nN(x) = {newton}')
print(f'Interpolation point: x = {point}')
print(f'Newton poly result on x = {point}\nN({point}) = {float(newton.subs(x_var, point)):.4f}')

print(sp.simplify(lagrange))
print(sp.simplify(newton))

X=np.linspace(-20,20,25,endpoint=True)
L=lambdify(x_var,lagrange)
N=lambdify(x_var,newton)
L_y=L(X)
N_y=N(X)

fig=plt.figure(figsize=(8,6))
plt.plot(X,L_y,label='Lagrange',color='green')
plt.plot(X,N_y,label='Newton',color='orange')
plt.plot(x, y, label='у',color='blue')
plt.scatter(point,newton.subs(x_var, point) , color='red', label='point',linewidth=2)

plt.xlim(-5, 5)
plt.ylim(-5, 5)
plt.axvline(color='black',linewidth=0.5)
plt.axhline(color='black',linewidth=0.5)
plt.grid()
plt.legend()
plt.show()