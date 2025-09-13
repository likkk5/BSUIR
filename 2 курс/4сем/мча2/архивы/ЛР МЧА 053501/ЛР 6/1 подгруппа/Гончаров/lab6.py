
print("Polynomial interpolation \n")

import imp
import numpy as np
import matplotlib.pyplot as plt
from methods import input
from methods import Lagrange
from methods import DividedDifferences




dots = input()
(x, y) = map(list, zip(*dots))
print("(x,y) =", dots, '\n')




lagr = Lagrange(dots)
print("Lagrange polynom =")
print(lagr, '\n')

    
def Inaccuracy(xs, xdot):
    n = len(xs)
    diffs = DividedDifferences(xs)
    maxdiff = 0.0
    for i in range(len(diffs)):
        for j in range(len(diffs[i])):
            maxdiff = max(maxdiff, abs(diffs[i][j]))
    w = 1
    for i in range(n):
        w *= xdot - xs[i]
    f = 1
    for i in range(1, n+1 + 1):
        f *= i
    R = maxdiff * w / f
    return R


def Newton(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))

    diffs = DividedDifferences(x)

    polynom = np.poly1d([0])
    for i in range(n):
        p = np.poly1d([1])
        for j in range(i):
            p *= np.poly1d([ 1, -x[j] ])
        polynom += p * diffs[0][i]

    return polynom
    
newt = Newton(dots)
print("Newton polynom =")
print(newt, '\n')


def Simple(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))
    A = []
    for i in range(n):
        A.append([])
        for j in range(n):
            A[i].append(x[i] ** j)
    polynom = np.poly1d(np.linalg.solve(A, y)[::-1])
    return polynom

def Squares(dots, m = None):
    n = len(dots) - 1
    if m is None:
        m = n
    assert 0 <= m <= n
    if m == n:
        return Simple(dots)
    
    (x, y) = map(list, zip(*dots))
    
    b = []
    for k in range(m + 1):
        s = 0
        for i in range(n + 1):
            s += y[i] * (x[i] ** (m - k)) 
        b.append(s)

    A = []
    for k in range(m + 1):
        A.append([])
        for j in range(m + 1):
            s = 0
            for i in range(n + 1):
                s += x[i] ** (2 * m - k - j)
            A[k].append(s)
    
    polynom = np.poly1d(np.linalg.solve(A, b))
    return polynom

def LeastSquares(dots, m = None):
    n = len(dots) - 1
    if m is None:
        m = n
    assert 0 <= m <= n
    return np.poly1d(np.polyfit(*map(list, zip(*dots)), m))

sqrs = Squares(dots)
print("Squares polynom =")
print(sqrs, '\n')

last = LeastSquares(dots)
print("LeastSquares polynom =")
print(last, '\n')


M = 2
print(f"\n Let-s build least squares polymon with degree = {M} \n")
sqrs = Squares(dots, M)
print("Squares polynom =")
print(sqrs, '\n')
last = LeastSquares(dots, M)
print("LeastSquares polynom =")
print(last, '\n')


xdot = 0.47
print(f"Largange({xdot}) =", lagr(xdot))
print(f"Newton({xdot}) =", newt(xdot))
print(f"Squares({xdot}) =", "{:.4f}".format(sqrs(xdot)))
print(f"LeastSquares({xdot}) =", last(xdot))
print("|Largange - Newton| =", abs(lagr(xdot) - newt(xdot)))
print("|Squares - LeastSquares| =", abs(sqrs(xdot) - last(xdot)))
print("|Inteprolation - Squares|      =", "{:.4f}".format(abs((lagr(xdot) + newt(xdot)) / 2 - sqrs(xdot))) ) 
print("|Inteprolation - LeastSquares| =", abs((lagr(xdot) + newt(xdot)) / 2 - last(xdot)) ) 
print(f"Inaccuracy({xdot}) = ", Inaccuracy(x, xdot))


plotdots = 10**4

plt.plot(x, y, 'og')

xplot = np.linspace(min(x), max(x), plotdots)

yplot = [last(xdot) for xdot in xplot]
plt.plot(xplot, yplot, 'y')

yplot = [sqrs(xdot) for xdot in xplot]
plt.plot(xplot, yplot, 'c--')

yplot = [lagr(xdot) for xdot in xplot]
plt.plot(xplot, yplot, 'b')

yplot = [newt(xdot) for xdot in xplot]
plt.plot(xplot, yplot, 'r--')


plt.show()
