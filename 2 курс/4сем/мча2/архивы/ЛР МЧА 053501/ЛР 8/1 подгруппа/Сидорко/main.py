from sympy import Symbol, diff, atan, lambdify, integrate, solve, sin, cos, sinh, log, exp, sqrt


def main():
    print(f"Функция:   y = {f}")
    print(f"Интервал:   [{LEFT}, {RIGHT}]")

    pnt = (LEFT + RIGHT) / 2

    h = EPS_DIFF
    # h = float(6 * EPS_DIFF / get_func_max(diff(f, x, 3), x, LEFT, RIGHT)) ** (1 / 2)
    d1 = diff_cont_3(pnt, h)
    print(f"\nПроизводная порядка 1 в точке {pnt}: {d1:.2f}")

    der = lambdify(x, diff(f))
    print(f"Точность вычисленного значения: {abs(der(pnt) - d1)}")

    # h = float(12 * EPS_DIFF / get_func_max(diff(f, x, 4), x, LEFT, RIGHT)) ** (1 / 2)
    d2 = diff_2_order(pnt, h)
    print(f"\nПроизводная порядка 2 в точке {pnt}:  {d2:.2f}")

    der_2 = lambdify(x, diff(diff(f)))
    print(f"Точность вычисленного значения: {abs(der_2(pnt) - d2)}")

    integral = lambdify(x, integrate(f, x))
    true_int = integral(RIGHT) - integral(LEFT)
    rect = int_rect()
    trapezoid = int_trapezoid()
    simpson = int_simpson()
    print("\n\nЗначение интеграла:")
    print(f"Метод прямоугольников: {rect:.6f}        точность: {abs(rect - true_int)}")
    print(f"Метод трапеций:        {trapezoid:.6f}        точность: {abs(trapezoid - true_int)}")
    print(f"Метод Симпсона:        {simpson:.6f}        точность: {abs(simpson - true_int)}")


def diff_cont_2(x_, h) -> float:
    x_l = x_ - h / 2
    x_r = x_ + h / 2
    y_l = f_lmd(x_l)
    y_r = f_lmd(x_r)

    return (y_r - y_l) / h


def diff_cont_3(x_, h) -> float:
    x_l = x_ - h
    x_r = x_ + h
    y_l = f_lmd(x_l)
    y_r = f_lmd(x_r)
    return (y_r - y_l) / (2 * h)


def diff_2_order(x_, h) -> float:
    x_l = x_ - h
    x_m = x_
    x_r = x_ + h
    y_l = f_lmd(x_l)
    y_m = f_lmd(x_m)
    y_r = f_lmd(x_r)
    return (y_r - 2 * y_m + y_l) / (h ** 2)


def int_rect() -> float:
    h = EPS_INT
    n = int((RIGHT - LEFT) / h)
    res = 0.0
    for i in range(1, n + 1):
        res += (h * f_lmd(LEFT + i * h - h / 2))

    return res


def int_trapezoid() -> float:
    h = EPS_INT
    n = int((RIGHT - LEFT) / h)
    res = h * (f_lmd(LEFT) + f_lmd(RIGHT)) / 2
    for i in range(1, n):
        res += (h * f_lmd(LEFT + i * h))

    return res


def int_simpson() -> float:
    h = EPS_INT / 2
    n = int((RIGHT - LEFT) / (2 * h))
    res = f_lmd(LEFT) + f_lmd(RIGHT)
    for i in range(2, 2 * n - 1):
        res += (2 * f_lmd(LEFT + i * h))
    for i in range(1, 2 * n):
        res += (4 * f_lmd(LEFT + i * h))

    return res * h / 6


def get_func_max(func, sym: Symbol, left: float, right: float) -> float:
    der = diff(func, sym)
    x_ = solve(der, sym)
    func_l = lambdify(sym, func)
    max_ = max(abs(func_l(left)), abs(func_l(right)))
    for pnt in x_:
        if left <= pnt <= right:
            max_ = max(max_, abs(func_l(pnt)))

    return max_


if __name__ == '__main__':
    LEFT = 0.0
    RIGHT = 1.0
    EPS_DIFF = 1e-2
    EPS_INT = 1e-6
    x = Symbol('x')
    f = sqrt(1 - x ** 2)
    f_lmd = lambdify(x, f)
    main()
