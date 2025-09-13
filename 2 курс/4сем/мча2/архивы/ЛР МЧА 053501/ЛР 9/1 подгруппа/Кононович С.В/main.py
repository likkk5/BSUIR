import matplotlib.pyplot as plt


def euler(inputs, n):
    outputs = [y0]
    h = inputs / n

    for i in range(n):
        x = i * h
        y = outputs[-1]
        outputs += [y + h * yder(x, y)]

    return outputs


def better_euler(xdot, n):
    y_dots = [y0]
    h = xdot / n
    for i in range(n):
        x = i * h
        y = y_dots[-1]
        y_dots += [y + h * yder(x + h/2, y + h/2 * yder(x, y))]
    return y_dots


def runge_kutta(xdot, n):
    y_dots = [y0]
    h = xdot / n
    
    for i in range(n):
        x = i * h
        y = y_dots[-1]
        k1 = h * yder(x, y)
        k2 = h * yder(x + h/2, y + k1/2)
        k3 = h * yder(x + h/2, y + k2/2)
        k4 = h * yder(x + h, y + k3)
        y_dots += [y + 1/6 * (k1 + 2*k2 + 2*k3 + k4)]
        
    return y_dots


def evaluate(method, x):
    n = 1
    while True:
        old_points, points = method(x, n), method(x, 2*n)
        if max(abs(points[2*i] - old_points[i]) for i in range(n+1)) < eps:
            return points[-1], 2*n
        n *= 2


def solve(method, inputs):
    outputs = []
    max_number = 0
    mean_number = []

    for x in inputs:
        y, n = evaluate(method, x)
        outputs.append(y)
        max_number = max(max_number, n)
        mean_number += [n]

    mean_number = sum(mean_number) / len(inputs)
    return outputs, mean_number, max_number


def main():
    print(f"Epsilon = {eps}\n")

    x_dots = [LEFT + (RIGHT - LEFT) / points * i for i in range(points + 1)]

    y_dots, mean_number, max_number = solve(euler, x_dots)
    print(f"Euler method\nMean number of dots: {mean_number}\nMax number of dots {max_number}\n")
    plt.plot(x_dots, y_dots, 'y', label="Euler")

    y_dots, mean_number, max_number = solve(better_euler, x_dots)
    print(f"Better Euler method\nMean number of dots: {mean_number}\nMax number of dots {max_number}\n")
    plt.plot(x_dots, y_dots, 'b--', label="Better Euler")

    y_dots, mean_number, max_number = solve(runge_kutta, x_dots)
    print(f"RungeKutta method\nMean number of dots: {mean_number}\nMax number of dots {max_number}\n")
    plt.plot(x_dots, y_dots, 'r:', label="RungeKutta")

    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.show()


def yder(x, y):
    return (a * (1-y**2)) / ((1 + m) * x**2 + y**2 + 1)


if __name__ == "__main__":
    points = 10 ** 3
    eps = 10 ** -3

    m, a = 2.0, 0.5

    y0 = 0
    LEFT, RIGHT = 0, 1

    main()
