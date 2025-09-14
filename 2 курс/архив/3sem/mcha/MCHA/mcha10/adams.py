import numpy as np
from scipy import integrate

a, b, Y0, eps = 0, 1, np.array([0]), 0.001
c = 0.9
m = 2.0


def evaluate(h):
    T, Y_exact = pick_step(a, b + h, step=h)
    adams_res = adams(T, h)
    difference = np.abs(adams_res - Y_exact)
    while (max(difference) > eps):
        h /= 2
        T, Y_exact = pick_step(a, b + h, step=h)
        adams_res = adams(T, h)
        difference = np.abs(adams_res - Y_exact)

    return h, T, adams_res, Y_exact, difference


def pick_step(a, b, step):
    T = np.arange(a, b, step)
    Y = rungekutta(T)
    return (T, Y)


def f(t, Y):
    dY = np.zeros(Y.shape)
    dY[0] = c*(1-Y[0]**2)/((1+m)*t**2+Y[0]**2+1)
    return dY


def rungekutta(T):
    r = (integrate.ode(f).set_integrator('dopri5', atol=0.0001).set_initial_value(Y0, T[0]))  # выражение интеграла (метод рунге-кутта)
    Y = np.zeros((len(T), len(Y0)))
    Y[0] = Y0
    for it in range(1, len(T)):
        Y[it] = r.integrate(T[it])  # подстановка
        if not r.successful():
            raise RuntimeError("Нельзя интегрировать")
    return Y[:, 0]


def adams(T, h):
    Y = np.zeros((len(T) + 2, 1))
    result = np.zeros((len(T), 1))

    extra_y = rungekutta([T[0], T[0] - h, T[0] + h])
    Y[0] = extra_y[1]
    Y[1] = Y0

    for it in range(2, len(T) + 1):
        Y[it] = Y[it - 1] + h*(1.5*f(T[it - 1], Y[it - 1]) - 0.5*f(T[it - 2], Y[it - 2]))
    for it in range(0, len(T)):
        result[it] = Y[it + 1]
    return result[:, 0]
