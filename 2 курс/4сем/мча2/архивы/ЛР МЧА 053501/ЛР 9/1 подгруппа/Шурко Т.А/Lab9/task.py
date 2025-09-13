import matplotlib.pyplot as plt


print("Euler method and Runge-k_utta method \n")
print("Adams' method \n")


plot_dots = 10**3
eps = 10**-3


m, a = 2.0, 0.9
y0 = 0
LEFT, RIGHT = 0, 1


def func(x, y):
    return (a * (1 - y**2))/((1 + m) * x**2 + y**2 + 1)


def euler(xdot, n):
    y_dots = [y0]
    h = xdot / n
    for i in range(n):
        x = i * h
        y = y_dots[-1]
        y_dots += [y + h * func(x, y)]
    return y_dots


def better_euler(xdot, n):
    y_dots = [y0]
    h = xdot / n
    for i in range(n):
        x = i * h
        y = y_dots[-1]
        y_dots += [y + h * func(x + h/2, y + h/2 * func(x, y))]
    return y_dots


def runge_kutta(xdot, n):
    y_dots = [y0]
    h = xdot / n
    for i in range(n):
        x = i * h
        y = y_dots[-1]
        k_1 = h * func(x, y)
        k_2 = h * func(x + h/2, y + k_1/2)
        k_3 = h * func(x + h/2, y + k_2/2)
        k_4 = h * func(x + h, y + k_3)
        y_dots += [y + 1/6 * (k_1 + 2*k_2 + 2*k_3 + k_4)]
    return y_dots


def get_value_at_point(method, x):
    n = 1
    while True:
        old_dots, new_dots = method(x, n), method(x, 2*n)
        if max(abs(new_dots[2*i] - old_dots[i]) for i in range(n+1)) < eps:
            return new_dots[-1], 2*n
        else:
            n *= 2


def create_y_dots(method, x_dots):
    y_dots = []
    max_n = 0
    mid_n = []
    for x in x_dots:
        y, n = get_value_at_point(method, x)
        y_dots.append(y)
        max_n = max(max_n, n)
        mid_n += [n]
    mid_n = sum(mid_n) / len(x_dots)
    return y_dots, mid_n, max_n


print("Dots for calculating = ", plot_dots)
print("Epsilon = ", eps)

x_dots_for_plot = [LEFT + (RIGHT - LEFT) / plot_dots * i for i in range(plot_dots+1)]

y_dots_for_plot, mid_n_statistics, max_n_statistics = create_y_dots(euler, x_dots_for_plot)
print("\n Midn / Maxn per dot in " + "Euler" + " method       = ", mid_n_statistics, " / ", max_n_statistics)
plt.plot(x_dots_for_plot, y_dots_for_plot, 'y')

y_dots_for_plot, mid_n_statistics, max_n_statistics = create_y_dots(better_euler, x_dots_for_plot)
print("\n Midn / Maxn per dot in " + "BetterEuler" + " method = ", mid_n_statistics, " / ",  max_n_statistics)
plt.plot(x_dots_for_plot, y_dots_for_plot, 'b--')

y_dots_for_plot, mid_n_statistics, max_n_statistics = create_y_dots(runge_kutta, x_dots_for_plot)
print("\n Midn / Maxn per dot in " + "Rungek_utta" + " method  = ", mid_n_statistics, " / ",  max_n_statistics)
plt.plot(x_dots_for_plot, y_dots_for_plot, 'r:')

plt.show()
