
print("Polynomial interpolation \n")

import numpy as np
import matplotlib.pyplot as plt


def input():

    x = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
    k = 7
    m = 3.5
    y = [ (p[i] + ((-1) ** k) * m) for i in range(len(x))]
    dots = list(zip(x, y))


    #dots = [(0, 0), (1, 0)]
    #dots = [(-1, 0), (0, 1), (1, 0)]
    #dots = [(1, 1), (2, 2), (3, 3), (4, 4), (5, 6)]
    #dots = [(1, 1), (2, 3), (3, 5), (4, 7), (5, 217341)]
    #dots = [(-1.5, np.tan(-1.5)), (-0.75, np.tan(-0.75)), (0, np.tan(0)), (0.75, np.tan(0.75)), (1.5, np.tan(1.5))]
    
    #dots = [(, ), ]
    
    #def f(x):
    #    return 1 / (1 + x**2)
    #SIZE = 11
    #dots = [(-5 + 10 * x / (SIZE - 1), f(-5 + 10 * x / (SIZE - 1))) for x in range(SIZE) ]


    return dots

dots = input()
(x, y) = map(list, zip(*dots))
print("(x,y) =", dots, '\n')


def Lagrange(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))
    polynom = np.poly1d([0])
    for i in range(n):
        p = np.poly1d([1])
        for j in range(n):
            if j != i:
                p *= np.poly1d([ 1, -x[j] ]) / (x[i] - x[j])
        polynom += y[i] * p
    return polynom

lagr = Lagrange(dots)
print("Lagrange polynom =")
print(lagr, '\n')


def DividedDifferences(xs):
    n = len(xs)
    diffs = [[None for j in range(n - i)] for i in range(n)]
    for i in range(n):
        diffs[i][0] = y[i]
    for j in range(1, n):
        for i in range(n - j):
            diffs[i][j] = ((diffs[i][j - 1] - diffs[i + 1][j - 1]) / (xs[i] - xs[i + j]))
    return diffs
    
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
