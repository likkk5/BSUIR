# -*- coding: windows-1251 -*-

import numpy as np
import sympy as sp
from sympy import symbols, sqrt, tan, sin, cos
import time
import Methods
from SturmRow import get_root_intervals, get_sturm_row

interval = (-10, 10)

a = -14.4621 
b = 60.6959
c = -70.9238

x = sp.symbols('x')
y = x ** 3 + a * x ** 2 + b * x + c
y_1 = x ** 2 - 0.9 * x - 0.36
y_2 = x**5 +2.32355*x**4 - 24.9645*x**3 -36.0407*x**2 + 88.1805*x -0.4528758
y_3 = x ** 4 - 2 * x ** 3 - 7 * x ** 2 + 8 * x + 1


polynomial = [1,a,b,c]
polynomial_1 = [1,-0.9,-0.36]
polynomial_2 = [1,2.32355,- 24.9645,-36.0407,88.1805,-0.4528758]
polynomial_3 = [1,-2,-7,8,1]
epsilon = 1e-5

print(f'Equation is \n y={y}')
print('-' * 50)
intervals = get_root_intervals(get_sturm_row(y), interval)
print(f"\nIntervals with 1 root: {[x for x in intervals]}\n")
roots = []

initial_guess = 1.0
tolerance = 1e-4
max_iterations = 100


for inter in intervals:
        print(f'\n\t\tCurrent interval is: {inter}')

        print('-' * 50)
        start_time=time.time()* 1000
        bisect_ans = Methods.bisection_method(y, inter)
        end_time=time.time()* 1000
        execution_time = end_time - start_time
        print(f'**** Solving with Bisection method ****\n'
              f'ROOT: {bisect_ans[0]}\n'
              f'Iteration: {bisect_ans[1]}\n'
              f'Execution Time: {execution_time} seconds')

        print('-' * 50)
        start_time=time.time()* 1000
        secant_ans = Methods.secant_method(y, inter)
        end_time=time.time()* 1000
        execution_time = end_time - start_time
        print(f'**** Solving with Secant method ****\n'
              f'ROOT: {secant_ans[0]}\n'
              f'Iteration: {secant_ans[1]}\n'
              f'Execution Time: {execution_time} seconds')
        
        print('-' * 50)
        start_time=time.time()* 1000
        class_newton_ans = Methods.ClassicalNewtonMethod(polynomial, inter, epsilon)
        end_time=time.time()* 1000
        execution_time = end_time - start_time
        print(f'**** Solving with Classical Newton method ****\n'
              f'ROOT: {class_newton_ans[0]}\n'
              f'Iteration: {class_newton_ans[1]}\n'
              f'Execution Time: {execution_time} seconds')
        
        print('-' * 50)
        start_time=time.time()* 1000
        simpl_newton_ans = Methods.SimplifiedNewtonMethod(polynomial, inter, epsilon)
        end_time=time.time()* 1000
        execution_time = end_time - start_time
        print(f'**** Solving with Simplified Newton method ****\n'
              f'ROOT: {simpl_newton_ans[0]}\n'
              f'Iteration: {simpl_newton_ans[1]}\n'
              f'Execution Time: {execution_time} seconds')
        
        print('-' * 50)
        start_time=time.time()* 1000
        false_place_newton_ans = Methods.FalsePlacementNewtonMethod(polynomial, inter, epsilon)
        end_time=time.time()* 1000
        execution_time = end_time - start_time
        print(f'**** Solving with False placements Newton method ****\n'
              f'ROOT: {false_place_newton_ans[0]}\n'
              f'Iteration: {false_place_newton_ans[1]}\n'
              f'Execution Time: {execution_time} seconds')
        
        print('-' * 50)
        start_time=time.time()* 1000
        boost_ans = Methods.BoostChordMethod(polynomial, inter, inter[0],epsilon)
        end_time=time.time()* 1000
        execution_time = end_time - start_time
        print(f'**** Solving with boost chord method ****\n'
              f'ROOT: {boost_ans[0]}\n'
              f'Iteration: {boost_ans[1]}\n'
              f'Execution Time: {execution_time} seconds')
        
        roots.append(class_newton_ans[0])
  

print('-' * 50)
correct_roots = np.roots(polynomial)
print(f'\n**** Solving with Numpy ****\n'
          f'ROOTS: {correct_roots}\n')




