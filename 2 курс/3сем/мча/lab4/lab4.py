# -*- coding: windows-1251 -*-

from iteration_method import *
import task
from newton_method import *
import numpy as np
import matplotlib.pyplot as plt
from sympy import symbols, Eq, solve, lambdify,tan


def print_list(ls, ):
    output = [el for el in ls]
    return output


system = task.get_system()
approx = task.approx

#print(np.linalg.solve(system[0], system[1]))
print(f"\t\tНачальное приближение: {approx}")
iteration_ans = iteration_solve(system, approx, verbose=1)
print("\t\t*** Метод простой итерации: ***")
print(f"Корни уравнения: {print_list(iteration_ans[0])}")
print(f"Количество итераций: {iteration_ans[1]}")

for i in range(2):
    print('-' * 20)


print(f"\t\tНачальное приближение: {approx}")
newton_ans = newton_solve(system[0], approx)
print("\t\t*** Метод Ньютона: ***")
print(f"Корни уравнения: {print_list(newton_ans[0])}")
print(f"Количество итераций: {newton_ans[1]}")

import numpy as np
import matplotlib.pyplot as plt

m = 0.2
a = 0.7

# Уравнения
def eq1(x, y):
    return np.tan(x * y + m) - x

def eq2(x, y):
    return a * (x ** 2) + 2 * (y ** 2) - 1

# Сетка точек
x = np.linspace(-2, 2, 100)
y = np.linspace(-2, 2, 100)
X, Y = np.meshgrid(x, y)

Z1 = eq1(X, Y)
Z2 = eq2(X, Y)

# Построение графиков
plt.figure(figsize=(6, 6))

plt.contour(X, Y, Z1, levels=[0], colors='blue', label='Equation 1')
plt.contour(X, Y, Z2, levels=[0], colors='red', label='Equation 2')

plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.title('Graphs of Equation 1 and Equation 2')

plt.show()

