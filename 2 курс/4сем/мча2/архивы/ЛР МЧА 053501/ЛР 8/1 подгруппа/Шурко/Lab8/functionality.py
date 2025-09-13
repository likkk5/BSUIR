import sympy


def first_derivative(h, x0, func):
    return (func(x0 + h) - func(x0)) / h


def first_derivative_2(h, x0, func):
    return (func(x0 + h) - func(x0 - h)) / (2 * h)


def second_derivative(h, x0, func):
    return (func(x0 + h) - 2*func(x0) + func(x0 - h)) / (h ** 2)


def second_derivative2(h, x0, func):
    return (-func(x0 + 2*h) + 16*func(x0+h) - 30*func(x0) + 16*func(x0-h) - func(x0 - 2*h)) / (12 * (h ** 2))


def integral_rectangle_method(a, b, n, func):
    h = (b - a) / n
    x_value = a
    res = func(x_value)
    while x_value < b:
        x_value += h
        res += func(x_value+h/2)

    return h * res


def rectangle_method(a, b, n, func):
    h = (b - a) / n
    sum = 0
    x_value = a - h/2
    while x_value < b:
        sum += func(x_value - h/2)
        x_value += h

    return sum * h


def trapezoid_method(a, b, n, func):
    s = 0.5 * (func(a) + func(b))
    h = (b - a) / n
    x = a + h
    while x <= b - h:
        s += func(x)
        x += h
    return h * s


def sympson(a, b, n, func):
    h = (b - a) / (2 * n)
    x = sympy.Symbol('x')
    tmp_sum = float(func.subs({x: a})) + \
              float(func.subs({x: b}))

    for step in range(1, 2 * n):
        if step % 2 != 0:
            tmp_sum += 4 * float(func.subs({x: a + step * h}))
        else:
            tmp_sum += 2 * float(func.subs({x: a + step * h}))

    return tmp_sum * h / 3




