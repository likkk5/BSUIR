import math
from sympy import *
from sympy.solvers import solve


def main():
    k = 12
    a = math.sin(k)
    b = math.cos(k)
    left_border = -1
    right_border = 1
    x, i = symbols('x i')
    phi_i = x ** i * (1 - x ** 2)
    left_border = 0
    h = (right_border - left_border) / 2
    points_list = []
    j = left_border

    while j != right_border:
        points_list.append(j)
        j += h
    print_stars()

    print(f'Метод коллокаций :\n\nТочки коллокации: {points_list}\n')
    phi_list = []
    j = 1

    while j <= len(points_list):
        phi_list.append(phi_i.subs(i, j))
        j += 1

    print('Базовая система:')
    for j in range(len(phi_list)):
        print(f'φ{j + 1} = {phi_list[j]}')
    y = 0
    k = 1
    a_list = []

    for j in phi_list:
        a_i = symbols(f'a{k}')
        a_list.append(a_i)
        y += a_i * j
        k += 1

    print(f'\ny = {y}')
    y_diff2 = diff(diff(y, x), x)
    print(f"y'' = {y_diff2}\n")

    psi_list = []
    for j in points_list:
        psi_list.append((a * y_diff2 + (1 + b * x ** 2) * y + 1).subs(x, j))

    print_system(psi_list)
    result = solve(psi_list, tuple(a_list))
    print_solution(result, phi_list)
    print_stars()

    print('Дискретный метод наименьших квадратов:\n')
    s = 0
    amount = 100
    h = (right_border - left_border) / amount
    j = left_border

    while j < right_border:
        s += (a * y_diff2 + (1 + b * x ** 2) * y + 1).subs(x, j) ** 2
        j += h

    diffs = []
    for j in a_list:
        diffs.append(diff(s, j))

    print_system(diffs)
    result = solve(diffs, tuple(a_list))
    print_solution(result, phi_list)
    print_stars()

    print('Интегральный метод наименьших квадратов:\n')

    i = integrate((a * y_diff2 + (1 + b * x ** 2) * y + 1) ** 2, (x, left_border, right_border))

    diffs = []
    for j in a_list:
        diffs.append(diff(i, j))

    print_system(diffs)
    result = solve(diffs, tuple(a_list))
    print_solution(result, phi_list)
    print_stars()

    print('Метод Галеркина :\n')

    system = []
    for j in phi_list:
        system.append(integrate((a * y_diff2 + (1 + b * x ** 2) * y + 1) * j, (x, left_border, right_border)))

    print_system(system)
    result = solve(system, tuple(a_list))
    print_solution(result, phi_list)


def print_solution(result, phi_list):
    if len(result) == 0:
        print('Нет решения')
    else:
        print('\nРешение:')
        print(f'y = ', end='')
        for j in range(len(result)):
            print(f'({list(result.values())[j]} * {phi_list[j]})', end='')
            if j != len(result) - 1:
                print(' + ', end='')
    print()


def print_system(_list):
    print('Система:')
    for j in _list:
        print(f'{j} = 0')


def print_stars():
    print('\n' + '*' * 150)


if __name__ == '__main__':
    main()
