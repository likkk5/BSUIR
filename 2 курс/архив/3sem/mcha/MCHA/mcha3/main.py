import numpy as np

import task
from nonlinear_methods import newton, secant, bisection
from sturms_row import get_root_intervals, get_sturm_row
from accuracy import check_accuracy


def main():
    y = task.y

    interval = task.interval

    print(f'Equation is \n y={y}')
    print('#' * 50)
    intervals = get_root_intervals(get_sturm_row(y), interval)
    print(f"\nIntervals with 1 root: {[x for x in intervals]}\n")
    roots = []
    for inter in intervals:
        print(f'\n\t\tCurrent interval is: {inter}')

        print('#' * 50)
        bisect_ans = bisection(y, inter)
        print(f'**** Solving with Bisection method ****\n'
              f'ROOT: {bisect_ans[0]}\n'
              f'Iteration: {bisect_ans[1]}')

        print('#' * 50)
        secant_ans = secant(y, inter)
        print(f'**** Solving with Secant method ****\n'
              f'ROOT: {secant_ans[0]}\n'
              f'Iteration: {secant_ans[1]}')

        print('#' * 50)
        newton_ans = newton(y, inter)
        print(f'**** Solving with Newton method ****\n'
              f'ROOT: {newton_ans[0]}\n'
              f'Iteration: {newton_ans[1]}')

        roots.append(newton_ans[0])

    print('#' * 50)
    correct_roots = np.roots([1, task.a, task.b, task.c])
    print(f'**** Solving with Numpy ****\n'
          f'ROOTS: {correct_roots}\n')

    print(check_accuracy(sorted(list(filter(lambda x: interval[0] <= x <= interval[1], correct_roots))), sorted(roots)))

if __name__ == '__main__':
    main()
