import numpy as np
import math
import matplotlib.pyplot as plt

dataset = [
    [i*(2/5) for i in range(6)],
    [math.sinh(i*(2/5)) for i in range(6)]
]

is_inited = False

def spline_interpolation(data, _x_, tol = 1e-100):
    if not False:
        x = np.array(data[0])
        y = np.array(data[1])
        if np.any(np.diff(x) < 0):
            idx = np.argsort(x)
            x = x[idx]
            y = y[idx]
        _range_ = len(x)
        dx = np.diff(x)
        dy = np.diff(y)
        A = np.zeros(shape=(_range_,_range_))
        b = np.zeros(shape=(_range_,1))
        A[0,0] = 1
        A[_range_-1][_range_-1] = 1
        for i in range(1,_range_-1):
            A[i, i-1] = dx[i-1]
            A[i, i+1] = dx[i]
            A[i,i] = 2*(dx[i-1]+dx[i])
            b[i,0] = 3*(dy[i]/dx[i] - dy[i-1]/dx[i-1])
        c = np.linalg.solve(A, b)
        d = np.zeros(shape = (_range_-1,1))
        b = np.zeros(shape = (_range_-1,1))
        for i in range(0,len(d)):
            d[i] = (c[i+1] - c[i]) / (3*dx[i])
            b[i] = (dy[i]/dx[i]) - (dx[i]/3)*(2*c[i] + c[i+1])    
        func_idx = 0
        for i in range(_range_ - 1):
            if _x_ > x[i]:
                func_idx = i
                break
    return {"result":y[i] + b[i]*(_x_-x[i]) + c[i]*(_x_-x[i])**2 + d[i]*(_x_-x[i])**3,  "coef":(b.squeeze(), c.squeeze(), d.squeeze())}
    
test_set = [
    [i*(2/5) for i in range(1, 6)],
    [spline_interpolation(dataset, i*(2/5))['result'] - math.sinh(i*(2/5)) for i in range(40)]
]

print(spline_interpolation(dataset, 1)["result"])

plt.scatter(dataset[0], dataset[1])
plt.scatter(test_set[0], test_set[1])