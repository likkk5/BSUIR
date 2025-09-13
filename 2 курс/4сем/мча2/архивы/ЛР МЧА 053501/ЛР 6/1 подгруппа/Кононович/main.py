import numpy as np
import polynom_functions as pf
import plot_functions as plot


def main(k, m):
    x = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    y = [10.00, 5.00, 3.33, 2.50, 2.00, 1.67, 1.43, 1.25, 1.11, 1.00]
    print(f"x = {x}")
    print(f"y = {y}")
    point = 0.21

    print("Интерполяционный многочлен Лагранжа:")
    pol_lagrange = pf.lagrange(x, y)
    print(pol_lagrange)
    print(f"\nЗначение в точке x = {point}:   {np.polyval(pol_lagrange, point):.5f}")

    print("\nИнтерполяционный многочлен Ньютона:")
    pol_newton = pf.newton(x, y, x)
    print(pol_newton)
    print(f"\nЗначение в точке x = {point}:   {np.polyval(pol_newton, point):.5f}")

    print("\nМногочлен наилучшего приближения:")
    pol_square = np.poly1d(pf.best(x, y))
    print(pol_square)
    print(f"\nЗначение в точке x = {point}:   {np.polyval(pol_square, point):.5f}")

    max_error = pf.get_error(x, y)

    print(f"\nПогрешность:   {max_error:.5f}")

    print(f"Разность значений многочленов в точке x = {point}:   "
          f"{abs(np.polyval(pol_newton, point) - np.polyval(pol_square, point)):.5f}")

    plot.newton(x, y, x)
    plot.lagrange(x, y)


if __name__ == '__main__':
    main(6, 3)
