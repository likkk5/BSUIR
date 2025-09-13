import numpy as np
import math


a = 0.9
m = 0.2
eps = 10 ** -5

def f1(x):
    return math.tan(x[0] * x[1] + m)


def f2(x):
    return math.sqrt((1 - a * x[0] * x[0]) / 2)

# diffs for simple iteraions method
diff_f1 = [
    [
        lambda x: x[1] / (math.cos(x[0] * x[1] + m) ** 2),
        lambda x: x[0] / (math.cos(x[0] * x[1] + m) ** 2)
    ],
    [
        lambda x: (-math.sqrt(2) * a * x[0]) / (2 * math.sqrt(1 - a * x[0] * x[0])),
        lambda x: 0
    ]
]


f = [f1, f2]

g = [
    lambda x: math.tan(x[0] * x[1] + m) - x[0],
    lambda x: a * (x[0] ** 2) + 2 * (x[1] ** 2) - 1
    ]


def W(x):
    return np.array([
        [x[1] / (math.cos(x[0] * x[1] + m) ** 2) - 1, x[0] / (math.cos(x[0] * x[1] + m) ** 2)],
        [2 * a * x[0], 4 * x[1]]
    ])


def simple_solve(init_approximation, f, diff_f):
    it = 0
    # check_convergence
    nums = []
    n = len(init_approximation)
    good = True
    q = 0
    #for i in range(n):
    #    s = 0;
    #    for j in range(n):
    #        print(init_approximation)
    #        s += diff_f[j][i](init_approximation)
    #    if s >= 1:
    #        q = s
    #        good = False
    #        break

    if not good:
        print(f"iterations diverges in simple iterations method. q = {q}")
        return None

    solve = init_approximation
    pose = 69
    while (pose == 69):
        old_solve = solve.copy()
        it += 1
        for i in range(len(solve)):
            solve[i] = f[i](solve)

        if not np.isfinite(solve).all():
            print("iterations diverges in simple iterations method.")
            return None

        end = True
        for i in range(len(solve)):
            if math.fabs(solve[i] - old_solve[i]) > eps:
                end = False
                break

        if end:
            print(f"{it} iterations")
            break

    return solve


def newton_method(init_approximation, f):
    it = 0
    solve = init_approximation
    while True:
        it += 1
        w = W(init_approximation)
        old_solve = solve.copy()
        ff = np.array([[func(solve)] for func in f])
        d = np.linalg.solve(w, -ff)
        for i in range(len(solve)):
            solve[i] += d[i][0]
        if not np.isfinite(solve).all():
            print("iterations diverges in Newton's method.")
            return None

        if (max(abs(d)) < eps):
            print(f"{it} iterations")
            return solve

def main():
    print(simple_solve([0.5, 0.5], f, diff_f1))
    print(newton_method([0.5, 0.5], g))


if __name__ == "__main__":
    main()

