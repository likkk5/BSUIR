print("Euler method and Runge-Kutta method \n")
print("Adams' method \n")

import numpy as np
import matplotlib.pyplot as plt

plotdots = 10 ** 3
eps = 10 ** -3

m, a = 1.0, 0.5


def yder(x, y):
    return (a * (1 - y ** 2)) / ((1 + m) * x ** 2 + y ** 2 + 1)


y0 = 0
LEFT, RIGHT = 0, 1


def Euler(xdot, N):
    ydots = [y0]
    h = xdot / N
    for i in range(N):
        x = i * h
        y = ydots[-1]
        ydots += [y + h * yder(x, y)]
    return ydots


def BetterEuler(xdot, N):
    ydots = [y0]
    h = xdot / N
    for i in range(N):
        x = i * h
        y = ydots[-1]
        ydots += [y + h * yder(x + h / 2, y + h / 2 * yder(x, y))]
    return ydots


def RungeKutta(xdot, N):
    ydots = [y0]
    h = xdot / N
    for i in range(N):
        x = i * h
        y = ydots[-1]
        K1 = h * yder(x, y)
        K2 = h * yder(x + h / 2, y + K1 / 2)
        K3 = h * yder(x + h / 2, y + K2 / 2)
        K4 = h * yder(x + h, y + K3)
        ydots += [y + 1 / 6 * (K1 + 2 * K2 + 2 * K3 + K4)]
    return ydots


def GetValueAtPoint(method, x):
    n = 1
    while True:
        olddots, newdots = method(x, n), method(x, 2 * n)
        if max(abs(newdots[2 * i] - olddots[i]) for i in range(n + 1)) < eps:
            return newdots[-1], 2 * n
        else:
            n *= 2


def CreateYdots(method, xdots):
    ydots = []
    maxn = 0
    midn = []
    for x in xdots:
        y, n = GetValueAtPoint(method, x)
        ydots.append(y)
        maxn = max(maxn, n)
        midn += [n]
    midn = sum(midn) / len(xdots)
    return ydots, midn, maxn


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
        ydots += [y + h * (3 / 2 * flast - 1 / 2 * fprev)]
        fprev = flast
    return ydots

print("Dots for calculating = ", plotdots)
print("Epsilon = ", eps)

xdots = [LEFT + (RIGHT - LEFT) / plotdots * i for i in range(plotdots + 1)]

ydots, midn, maxn = CreateYdots(Euler, xdots)
print("\n MidN / MaxN per dot in " + "Euler" + " method	= ", midn, " / ", maxn)
plt.plot(xdots, ydots, 'y')

ydots, midn, maxn = CreateYdots(BetterEuler, xdots)
print("\n MidN / MaxN per dot in " + "BetterEuler" + " method = ", midn, " / ", maxn)
plt.plot(xdots, ydots, 'b--')

ydots, midn, maxn = CreateYdots(RungeKutta, xdots)
print("\n MidN / MaxN per dot in " + "RungeKutta" + " method = ", midn, " / ", maxn)
plt.plot(xdots, ydots, 'r:')

ydots, midn, maxn = CreateYdots(Adams, xdots)
print("\n MidN / MaxN per dot in " + "Adams" + " method	= ", midn, " / ", maxn)
plt.plot(xdots, ydots, 'g')
plt.show()
