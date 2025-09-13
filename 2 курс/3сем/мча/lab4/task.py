from sympy import symbols, sqrt, tan, sin, cos
import numpy as np
from math import asin, acos


m = 0.2
a = 0.7

approx = (0.5, -0.7)
approx_2 = (0.5, 0.5)

x = symbols('x:2')
y_1 = tan(x[0]*x[1] + m) - x[0]
y_2 = a*x[0]**2 + 2*x[1]**2 - 1

y_3 = sin(x[0]*x[1])
y_4 = cos(x[0]-x[1])-0.5

def get_system():
    return np.array([
        [
            y_1,
            y_2
        ],
        [
            tan(x[0]*x[1] + m),
            sqrt((1 - a*x[0]**2) / 2)
        ]
    ])

# def get_system():
#     return np.array([
#         [
#             y_3,
#             y_4
#         ],
#         [
#             asin(3.14)/x[0],
#             acos(0.5)+x[1]
#         ]
#     ])
