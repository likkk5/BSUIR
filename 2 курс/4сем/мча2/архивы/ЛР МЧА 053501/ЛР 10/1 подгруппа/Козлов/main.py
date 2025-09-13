import numpy as np
import matplotlib.pyplot as plt


a = 1.3
m = 1.5


def f(x, y):
    return (a * (1 - (y ** 2))) / ((1 + m) * (x ** 2) + (y ** 2) + 1)


def t1(x, y):
    return y / x


def t2(x, y):
    return -2 * y


def t3(x, y):
    return -np.cos(x) / np.sin(x) * (2 * y + 1)


def odeEuler(f, y0, t):
    '''Approximate the solution of y'=f(y,t) by Euler's method.

    Parameters
    ----------
    f : function
        Right-hand side of the differential equation y'=f(t,y), y(t_0)=y_0
    y0 : number
        Initial value y(t0)=y0 wher t0 is the entry at index 0 in the array t
    t : array
        1D NumPy array of t values where we approximate y values. Time step
        at each iteration is given by t[n+1] - t[n].

    Returns
    -------
    y : 1D NumPy array
        Approximation y[n] of the solution y(t_n) computed by Euler's method.
    '''
    y = np.zeros(len(t))
    y[0] = y0
    for n in range(1, len(t)):
        y[n] = y[n - 1] + f(t[n - 1], y[n - 1]) * (t[n] - t[n - 1])
    return y


# Finds value of y for a given x using step size h
# and initial value y0 at x0.
def rungeKutta(x0, y0, x, h, dydx):
    # Count number of iterations using step size or
    # step height h
    n = (int)((x - x0)/h)
    # Iterate for number of iterations
    y = y0
    for i in range(1, n + 1):
        "Apply Runge Kutta Formulas to find next value of y"
        k1 = h * dydx(x0, y)
        k2 = h * dydx(x0 + 0.5 * h, y + 0.5 * k1)
        k3 = h * dydx(x0 + 0.5 * h, y + 0.5 * k2)
        k4 = h * dydx(x0 + h, y + k3)

        # Update next value of y
        y = y + (1.0 / 6.0)*(k1 + 2 * k2 + 2 * k3 + k4)

        # Update next value of x
        x0 = x0 + h
    return y


def Adams(xdot, N):
    ydots = [y0]
    h = xdot / N
    xprev = -h
    yprev = GetValueAtPoint(RungeKutta, xprev)[0]
    fprev = yder(xprev, yprev)
    for i in range(N):
        x = i * h
        y = ydots[-1]
        flast = yder(x, y)
        ydots += [ y + h * (3/2 * flast - 1/2 * fprev) ]
        fprev = flast
    return ydots


def solve(f, n, x0, y0, x_max):
    h = (x_max - x0) / n
    x = [x0 + h * i for i in range(n)]
    y_euler = odeEuler(f, y0, x.copy())
    h = 1 / n
    y_rungeKutta = [rungeKutta(x0, y0, xx, h, f) for xx in x]

    plt.plot(x, y_euler)
    plt.plot(x, y_rungeKutta)
    plt.show()


def main():
    solve(f, 1000, 0, 0, 1)

    solve(t1, 1000, 1, 1, 5)
    solve(t2, 1000, 0, 2, 3)
    solve(t3, 1000, 1, 1, 2)


if __name__ == "__main__":
    main()
