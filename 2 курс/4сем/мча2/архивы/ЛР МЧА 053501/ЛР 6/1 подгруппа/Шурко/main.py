import examples
import functionality
import numpy as np
import matplotlib.pyplot as plt


def main():
    x, y = examples.default_values()
    x_new = np.linspace(np.min(x), np.max(x), 100)
    y_new2 = [functionality.lagranz(x, y, i) for i in x_new]

    y_new = []
    prev = None
    eps = None

    for i in range(len(x_new)):
        y_new.append(functionality.lagranz(x, y, x_new[i]))
        if prev is None:
            prev = y_new[i]
        if prev is not None and eps is None:
            eps = abs(y_new[i] - prev)
        elif abs(y_new[i] - prev) > eps:
            eps = abs(y_new[i] - prev)
        prev = y_new[i]

    print("Eps: ", eps)
    for i in range(len(x)):
        plt.scatter(x[i], y[i], 27, 'r')

    plt.plot(x, y, 'g', x_new, y_new, 'g')
    plt.plot(x, y, 'g', x_new, y_new2, 'b')

    print(functionality.lagranz(x, y, 0.47))
    print(functionality.newton(x, y, 0.47))

    functionality.best_approximation(x, y)
    functionality.diff_approximation_inter(x, y)

    plt.grid(True)
    plt.show()


if __name__ == '__main__':
    main()
