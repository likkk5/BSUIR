from prettytable import PrettyTable
import matplotlib.pyplot as plt
import numpy as np

import methods

A = -1
B = 1
k = 0.5
phi = lambda x: 1 - x ** 2
g1 = lambda t: 0
g2 = lambda t: 0
f = lambda x, t: x
T = 0.4


variants_1 = [
    # N, tau, t1, t2
    [10, 0.001, 0.1, 0.12],
    [10, 0.0005, 0.1, 0.12],
    [10, 0.00025, 0.1, 0.12],
    [10, 0.000125, 0.1, 0.12],
    [10, 0.0000625, 0.1, 0.12]
]

variants_2 = [
    # N, t1, t2
    [10, 0.1, 0.12],
    [20, 0.1, 0.12],
    [30, 0.1, 0.12],
    [40, 0.1, 0.12],
    [50, 0.1, 0.12]
]

methods = [
    [methods.explicit_method_1, 'Explicit method #1'],
    [methods.explicit_method_2, 'Explicit method #2'],
    [methods.implicit_method_1, 'Implicit method #1'],
    [methods.implicit_method_2, 'Implicit method #2']
]

table_1 = PrettyTable()
table_2 = PrettyTable()
table_3 = PrettyTable()
table_4 = PrettyTable()
table_1.field_names = ['N', 'tau', 's(t=t1)', 's(t=t2)', 'max(t=t1)', 'max(t=t2)']
table_2.field_names = ['N', 'tau', 's(t=t1)', 's(t=t2)', 'max(t=t1)', 'max(t=t2)']
table_3.field_names = ['N', 'tau', 's(t=t1)', 's(t=t2)', 'max(t=t1)', 'max(t=t2)']
table_4.field_names = ['N', 'tau', 's(t=t1)', 's(t=t2)', 'max(t=t1)', 'max(t=t2)']
errors_t1 = []
errors_t2 = []

for method, name in methods:
    print(name)
    print('_____________________________________________________________________')
    for N, tau, t1, t2 in variants_1:
        h = (B - A) / N
        solution_1 = method(h, tau)
        solution_2 = method(h, tau / 2)
        err_t1 = (solution_1[int(t1 / tau)] - solution_2[2 * int(t1 / tau)])
        err_t2 = (solution_1[int(t2 / tau)] - solution_2[2 * int(t2 / tau)])
        errors_t1.append((tau, np.linalg.norm(err_t1)))
        errors_t2.append((tau, np.linalg.norm(err_t2)))

        table_1.add_row([N, tau, err_t1.std(), err_t2.std(), max(abs(err_t1)), max(abs(err_t2))])

    print('h is fixed')
    print(table_1)
    table_1.clear_rows()

    plt.xscale('log')
    plt.xlabel('tau', fontsize=18)
    plt.ylabel('error', fontsize=18)
    plt.plot([tau for tau, err in errors_t1], [tau for tau, err in errors_t1], label='t = t1')
    plt.legend()
    plt.show()
    errors_t1.clear()
    
    plt.xscale('log')
    plt.xlabel('tau', fontsize=18)
    plt.ylabel('error', fontsize=18)
    plt.plot([tau for tau, err in errors_t2], [tau for tau, err in errors_t2], label='t = t2')
    plt.legend()
    plt.show()
    errors_t2.clear()

    for N, t1, t2 in variants_2:
        h = (B - A) / N
        tau = 0.0001
        solution_1 = method(h, tau)
        solution_2 = method(h / 2, tau)
        err_t1 = (solution_1[int(t1 / tau)] - solution_2[int(t1 / tau)][::2])
        err_t2 = (solution_1[int(t2 / tau)] - solution_2[int(t2 / tau)][::2])
        errors_t1.append((h, np.linalg.norm(err_t1)))
        errors_t2.append((h, np.linalg.norm(err_t2)))

        table_2.add_row([N, tau, err_t1.std(), err_t2.std(), max(abs(err_t1)), max(abs(err_t2))])

    print('tau is fixed')
    print(table_2)
    table_2.clear_rows()

    plt.xscale('log')
    plt.xlabel('h', fontsize=18)
    plt.ylabel('error', fontsize=18)
    plt.plot([h for h, err in errors_t1], [h for h, err in errors_t1], label='t = t1')
    plt.legend()
    plt.show()
    errors_t1.clear()
    
    plt.xscale('log')
    plt.xlabel('h', fontsize=18)
    plt.ylabel('error', fontsize=18)
    plt.plot([h for h, err in errors_t2], [h for h, err in errors_t2], label='t = t2')
    plt.legend()
    plt.show()
    errors_t2.clear()

    print('tau is h ^ 2 / 6 (relative to tau)')

    for N, t1, t2 in variants_2:
        h = (B - A) / N
        tau = (h ** 2) / 6
        solution_1 = method(h, tau)
        solution_2 = method(h, tau / 2)
        err_t1 = (solution_1[int(t1 / tau)] - solution_2[2 * int(t1 / tau)])
        err_t2 = (solution_1[int(t2 / tau)] - solution_2[2 * int(t2 / tau)])
        # errors_t1.append((tau, np.linalg.norm(err_t1)))
        # errors_t2.append((tau, np.linalg.norm(err_t2)))

        table_3.add_row([N, tau, err_t1.std(), err_t2.std(), max(abs(err_t1)), max(abs(err_t2))])

    print(table_3)
    table_3.clear_rows()

    # plt.xscale('log')
    # plt.xlabel('tau', fontsize=18)
    # plt.ylabel('error', fontsize=18)
    # plt.plot([tau for tau, err in errors_t1], [tau for tau, err in errors_t1], label='t = t1')
    # plt.legend()
    # plt.show()
    # errors_t1.clear()
    
    # plt.xscale('log')
    # plt.xlabel('tau', fontsize=18)
    # plt.ylabel('error', fontsize=18)
    # plt.plot([tau for tau, err in errors_t2], [tau for tau, err in errors_t2], label='t = t2')
    # plt.legend()
    # plt.show()
    # errors_t2.clear()

    print('tau is h ^ 2 / 6 (relative to h)')

    for N, t1, t2 in variants_2:
        h = (B - A) / N
        tau = (h ** 2) / 6
        solution_1 = method(h, tau)
        solution_2 = method(h / 2, tau)
        err_t1 = (solution_1[int(t1 / tau)] - solution_2[int(t1 / tau)][::2])
        err_t2 = (solution_1[int(t2 / tau)] - solution_2[int(t2 / tau)][::2])
        # errors_t1.append((h, np.linalg.norm(err_t1)))
        # errors_t2.append((h, np.linalg.norm(err_t2)))

        table_4.add_row([N, tau, err_t1.std(), err_t2.std(), max(abs(err_t1)), max(abs(err_t2))])

    print(table_4)
    table_4.clear_rows()

    # plt.xscale('log')
    # plt.xlabel('h', fontsize=18)
    # plt.ylabel('error', fontsize=18)
    # plt.plot([h for h, err in errors_t1], [h for h, err in errors_t1], label='t = t1')
    # plt.legend()
    # plt.show()
    # errors_t1.clear()
    
    # plt.xscale('log')
    # plt.xlabel('h', fontsize=18)
    # plt.ylabel('error', fontsize=18)
    # plt.plot([h for h, err in errors_t2], [h for h, err in errors_t2], label='t = t2')
    # plt.legend()
    # plt.show()
    # errors_t2.clear()