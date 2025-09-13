import matplotlib.pyplot as plt
import numpy as np
import polynom_functions as pf


def newton(x_values, y_values, x):
    points_number = 1000
    points_x = np.linspace(min(x_values), max(x_values), points_number)
    points_y = [np.polyval(pf.newton(x_values, y_values, x), pnt) for pnt in points_x]
    plt.plot(points_x, points_y, linewidth=3, label="Newton method")
    plt.plot(x_values, y_values, 'g*', markersize=7, label="Real values")
    plt.legend()
    plt.show()


def lagrange(x_values, y_values):
    points_number = 1000
    points_x = np.linspace(min(x_values), max(x_values), points_number)
    points_y = [np.polyval(pf.best(x_values, y_values), pnt) for pnt in points_x]
    plt.plot(points_x, points_y, linewidth=3, label="Lagrange")
    plt.plot(x_values, y_values, 'g*', markersize=7, label="Real values")
    plt.legend()
    plt.show()
