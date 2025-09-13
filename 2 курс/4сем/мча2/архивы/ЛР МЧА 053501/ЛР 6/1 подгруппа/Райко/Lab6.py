import numpy
import math
import matplotlib.pyplot as plt

%matplotlib inline

p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
m = 2.5
k = 5

data = [
    [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0],
    [p[i] + ((-1)**k)*m for i in range(len(p))]
]
print(data[0])
print(data[1])

def w(data_src=None, x=0, exclude=None, top_value=None):
    result = 1
    if top_value is None:
        top_value = len(data_src)
    for i in range(top_value):
        if i == exclude:
            continue
        result *= (x - data_src[0][i])
    return result

def lagrange_interpolation(_data_, x=0.1):
    result = 0
    for i in range(len(_data_)):
        result += _data_[1][i]*(w(data_src=_data_, x=x, exclude=i)/w(data_src=_data_, x=data[0][i], exclude=i))
    return result

print(lagrange_interpolation(data, x=0.47))
test1 = []
test1.append([i/10 + 0.03 for i in rang(10)])
test1.append([lagrange_interpolation(data, x = test1[0][i]) for i in range(10)])

def newton_interpolation(_data_, x=0.1):
    def _a_(_data=None, top_idx=None):
        result = 0
        for k in range(top_idx + 1):
            result += _data_[1][k]/w(data_src=_data_, x=_data[0][k], exclude=k, top_value=top_idx + 1)
        return result
    result = 0
    for i in range(len(_data_)):
        result += _a_(_data_, i)*w(data_src=_data_, x=x, top_value=i)
    return result


print(newton_interpolation(data, x=0.47))
test2 = []
test2.append([i/10 + 0.07 for i in rang(10)])
test2.append([newton_interpolation(data, x = test2[0][i]) for i in range(10)])

plt.scatter (data[0], data[1], color="black")
plt.scatter (test1[0], test1[1], color="red")
plt.scatter (test2[0], test2[1], color="blue")