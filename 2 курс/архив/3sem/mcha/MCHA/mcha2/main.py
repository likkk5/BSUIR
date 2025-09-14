import numpy as np
import task
from accuracy import check_accuracy
from iteration_method import iteration_method
from tools import print_equation
from zeidels_method import zeidels_method

A = task.A
b = task.b
e = task.E

print('Default matrix')
print_equation(A, b)

# Real exactly solution
x_real = np.linalg.solve(A, b)
print(f'Real Accurate solution *X*\n{x_real}')

# Iteration method
print('#' * 50)
x_iteration = iteration_method(A, b, e, 1)

print('#' * 50)
print(f'----Iteration method result----\nX = {x_iteration[0].reshape((1, x_iteration[0].shape[0]))}\n '
      f'Done in {x_iteration[1]} iterations')

# Gauss - seidel method
print('#' * 50)
x_zeidel = zeidels_method(A, b, e, 1)

print('#' * 50)
print(f'----Zeidels method result----\nX = {x_zeidel[0].reshape((1, x_zeidel[0].shape[0]))}\n'
      f'Done in {x_zeidel[1]} iterations')

check_accuracy(x_iteration[0], x_real)
