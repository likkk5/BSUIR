from cmath import sqrt
import numpy as np

def main():
    print('sqrt(1-lg^2(x))')
    func = lambda x : sqrt(1-(np.log10(x))**2 )
    calculate(1.0, 10.0, func)
    print()

    print('sqrt(x^3) / sin(x)')
    func = lambda x : np.sqrt(x**3) / np.sin(x)
    calculate(1.0, 2.0, func)
    print()

    print('sh(x) * cos(x)')
    func = lambda x : np.sinh(x) * np.cos(x)
    calculate(1.0, 2.0, func)
    print()

    print('arctg(x) / (9 - x^2)')
    func = lambda x : np.arctan(x) / (9 - x**2)
    calculate(1.0, 2.0, func)
    print()

def calculate(left, right, my_func):
    epsilon = 1e-6
    res = integrate(my_func, left, right, epsilon, "central_rect")
    print("Метод средних прямоугольников: ", res[0], "\nКоличество итераций:", res[1])
    res = integrate(my_func, left, right, epsilon, "simpson")
    print("Метод Симпсона: ", res[0], "\nКоличество итераций:", res[1])
    res = integrate(my_func, left, right, epsilon, "left_rect")
    print("Метод левых прямоугольников: ", res[0], "\nКоличество итераций:", res[1])
    res = integrate(my_func, left, right, epsilon, "right_rect")
    print("Метод правых прямоугольников: ", res[0], "\nКоличество итераций:", res[1])
    res = integrate(my_func, left, right, epsilon, "trapezium")
    print("Метод трапеций: ", res[0], "\nКоличество итераций:", res[1])
    res = diff1(my_func, (left + right) / 2, epsilon)
    print()
    print("Первая производная: ", res[0], "\nКоличество итераций:", res[1])
    res = diff2(my_func, (left + right) / 2, epsilon)
    print("Вторая производная: ", res[0], "\nКоличество итераций:", res[1])


methods = dict(
    left_rect = lambda func, n, left_border, h:
    sum([func(left_border + i * h) for i in range(int(n))]) * h,
    right_rect = lambda func, n, left_border, h:
    sum([func(left_border + (i + 1) * h) for i in range(int(n))]) * h,
    central_rect = lambda func, n, left_border, h:
    sum([func(left_border + (i + 1 / 2) * h) for i in range(int(n))]) * h,
    trapezium = lambda func, n, left_border, h:
    (sum([func(left_border + i * h) for i in range(1, int(n))]) + 0.5 *
     (func(left_border + h * n) + func(left_border))) * h,
    simpson=lambda func, n, left_border, h:
    (h / 3) * (func(left_border) + func(left_border + float(n) * h) +
               2 * sum([func(left_border + (2 * float(i)) * h)
                        for i in range(1, int(n) // 2)]) +
                  4 * sum([func(left_border + h * (2 * i + 1)) for i in range(int(n) // 2)])))


def calculate_iterations(left_border, right_border, epsilon, power):
    h = np.power(epsilon, power)
    return (right_border - left_border) / h


def integrate(func, left_border, right_border, epsilon, _type_, total=None):
    if _type_ != "simpson":
        n = np.ceil(calculate_iterations(left_border, right_border, epsilon, 0.25))
        h = (right_border - left_border) / n
        I = methods[_type_](func, n, left_border, h)
        I_prev = I + epsilon * 20
        counter = 0
        while abs(I - I_prev) / 3 > epsilon or (total is not None and counter < total):
            counter += 1
            I_prev = I
            h /= 2
            n *= 2
            I = methods[_type_](func, n, left_border, h)
        return I, counter
    else:
        n = np.ceil(calculate_iterations(left_border, right_border, epsilon, 0.25) / 2) * 2
        h = (right_border - left_border) / n
        I = methods[_type_](func, n, left_border, h)
        I_prev = I + epsilon * 20
        counter = 0
        while abs(I - I_prev) > epsilon or (total is not None and counter < total):
            counter += 1
            I_prev = I
            h /= 2
            n *= 2
            I = methods[_type_](func, n, left_border, h)
        return I, counter


def diff1(func, x, epsilon):
    diff_ = 10 * epsilon
    h = 0.1
    derivative = 10 * epsilon
    derivative = (func(x + h) - func(x - h)) / (2 * h)
    counter = 0
    while abs(diff_) > epsilon:
        temp = derivative
        derivative = (func(x + h) - func(x - h)) / (2 * h)
        if counter != 0:
            diff_ = derivative - temp
        else:
            diff_ = 10 * epsilon
        h /= 4
        counter += 1
    return derivative, counter


def diff2(func, x, epsilon):
    diff_ = 10 * epsilon
    h = 0.1
    derivative = 10 * epsilon
    derivative = (func(x + h) - func(x - h)) / (2 * h)
    counter = 0
    h /= 4
    while abs(diff_) >= epsilon:
        temp = derivative
        derivative = (func(x + h) + func(x - h) - 2 * func(x)) / (h ** 2)
        diff_ = abs(derivative - temp)
        counter += 1
        h /= 2
    return derivative, counter


if __name__ == '__main__':
    main()