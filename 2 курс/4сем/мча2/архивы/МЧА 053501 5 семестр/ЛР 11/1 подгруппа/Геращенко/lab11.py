import numpy as np
import matplotlib.pyplot as plt

k = 7
a, b = np.sin(k), np.cos(k)

l, r = -1, 1
collacation_points_amount = 7
phi_0 = np.poly1d([0])

p = np.poly1d(0)
q = np.poly1d([b, 0, 1])
f = np.poly1d([-1])

values = []

def beutify(text):
    max_len = 60
    star_len = (max_len - len(text) - 2) // 2
    name = star_len * '*' + ' ' + text + ' ' + star_len * '*'

    def wrapped(func):
        def wrapped_2():
            print(name)
            func()
            print(len(name) * '-')

        return wrapped_2

    return wrapped


def print_A_b_result(A, b):
    print('A:\n', A)
    print('b:\n', b)

    solution = np.linalg.solve(A, b)
    values.append(solution)
    print('Результат:\n', solution)


@beutify('Первоначальные данные')
def print_initial_info():
    global x, phis
    print ('Вариант:\n k =', k)
    x = np.linspace((l + r) / 2, r, collacation_points_amount + 1)[:-1]
    print('Точки коллокации:\n', x)

    phis = [get_phi(i) for i in range(1, collacation_points_amount + 1)]
    phis[0] = np.poly1d([-1, 0, 1])
    print('Базисные функции:')
    for i in range(len(phis)):
        print(phis[i])


def get_phi(n):
    if n == 0:
        return np.poly1d([0])
    else:
        coef = [0] * (n+3)
        coef[0] = -1
        coef[2] = 1
        return np.poly1d(coef)


def get_L_phis(f):
    return np.polyder(np.polyder(f)) + np.polyder(f) * p + f * q


@beutify('Метод коллокаций')
def collocation_method():
    def get_A(x):
        l = []
        for i in range(collacation_points_amount):
            l.append(get_L_phis(phis[i])(x))
        return l

    A = np.array([get_A(x[i]) for i in range(collacation_points_amount)])
    b = np.array([f(x[i]) - get_L_phis(phi_0)(x[i]) for i in range(collacation_points_amount)])

    print_A_b_result(A, b)


@beutify('Метод наименьших квадратов (непрерывный вариант)')
def min_squares_continuous():
    def get_scalar_product_int(f, g):
        func = np.polyint(f * g)
        return func(r) - func(l)

    def get_A(x):
        A = np.zeros((collacation_points_amount, collacation_points_amount))
        for i in range(collacation_points_amount):
            for j in range(collacation_points_amount):
                A[i][j] = get_scalar_product_int(get_L_phis(phis[i]), get_L_phis(phis[j]))
        return A

    def get_b(x):
        return [get_scalar_product_int(f - get_L_phis(phi_0), get_L_phis(phis[i]))
                for i in range(collacation_points_amount)]

    A = get_A(x)
    b = get_b(x)

    print_A_b_result(A, b)


@beutify('Метод наименьших квадратов (дискретный вариант)')
def min_squares_discrete():
    def get_scalar_product_int(f, g):
        return sum([f(x[i]) * g(x[i]) for i in range(collacation_points_amount)])

    def get_A(x):
        A = np.zeros((collacation_points_amount, collacation_points_amount))
        for i in range(collacation_points_amount):
            for j in range(collacation_points_amount):
                A[i][j] = get_scalar_product_int(get_L_phis(phis[i]), get_L_phis(phis[j]))
        return A

    def get_b(x):
        return [get_scalar_product_int(f - get_L_phis(phi_0), get_L_phis(phis[i]))
                for i in range(collacation_points_amount)]

    A = get_A(x)
    b = get_b(x)

    print_A_b_result(A, b)



@beutify('Метод Галеркина')
def galerkin_method():
    def get_scalar_product_int(f, g):
        func = np.polyint(f * g)
        return func(r) - func(l)

    def get_A(x):
        A = np.zeros((collacation_points_amount, collacation_points_amount))
        for i in range(collacation_points_amount):
            for j in range(collacation_points_amount):
                A[i][j] = get_scalar_product_int(get_L_phis(phis[i]), phis[j])
        return A

    def get_b(x):
        return [get_scalar_product_int(f - get_L_phis(phi_0), phis[i]) for i in range(collacation_points_amount)]

    A = get_A(x)
    b = get_b(x)

    print_A_b_result(A, b)


def plot():
    fig = plt.figure(figsize=(8, 6))
    for i in range(len(values)):
        l = np.linspace(0, 1)
        poly = np.polynomial.polynomial.Polynomial(values[i][::-1])
        plt.plot(l, poly(l))

    plt.ylim(-0.02, 0.01)
    plt.xlim(0, 0.2)

    plt.grid()
    plt.axvline(color="black", linewidth=0.5)
    plt.axhline(color='black', linewidth=0.5)
    plt.show()

if __name__ == '__main__':
    print_initial_info()
    print()
    collocation_method()
    print()
    min_squares_continuous()
    print()
    min_squares_discrete()
    print()
    galerkin_method()
    plot()