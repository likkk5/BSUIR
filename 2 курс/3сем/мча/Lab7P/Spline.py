#-*-coding:windows-1251-*-
from SweepMethod import sweep_method
import numpy as np
def spline_built(dots):
    n = len(dots) - 1
    (x, y) = map(list, zip(*dots))

    h = [None]
    for i in range(1, n + 1):
        h += [x[i] - x[i - 1]]

    A = [[None] * n for i in range(n)]

    for i in range(1, n):
        for j in range(1, n):
            A[i][j] = 0.0

    for i in range(1, n - 1):
        A[i + 1][i] = h[i + 1]

    for i in range(1, n):
        A[i][i] = 2 * (h[i] + h[i + 1])

    for i in range(1, n - 1):
        A[i][i + 1] = h[i + 1]

    F = []
    for i in range(1, n):
        F += [3 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i])]

    A = [A[i][1:] for i in range(len(A)) if i]

    c = sweep_method (A, F)
    c = [0.0] + list(c) + [0.0]
    
    def evaluate(xdot):
        for i in range(1, len(x)):
            if x[i - 1] <= xdot <= x[i]:
                val = 0
                val += y[i]
                b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
                val += b * (xdot - x[i])
                val += c[i] * ((xdot - x[i]) ** 2)
                d = (c[i] - c[i - 1]) / (3 * h[i])
                val += d * ((xdot - x[i]) ** 3)
                return val
        return None
    
    def output():
        print("Кубические сплайны:", '\n')
        for i in range(1, len(x)):
            val = 0
            b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
            d = (c[i] - c[i - 1]) / (3 * h[i])
            print(x[i - 1], x[i], "->")
            print(np.poly1d([d, c[i], b, y[i]]))
            spline_at_midpoint = evaluate(x[i-1])
            print(f"Значение сплайна в узле ({x[i-1]}): {spline_at_midpoint}\n")
            if(i==len(x)-1):
                spline_at_midpoint = evaluate(x[i])
                print(f"Значение сплайна в узле ({x[i]}): {spline_at_midpoint}\n") 
          
    return evaluate, output