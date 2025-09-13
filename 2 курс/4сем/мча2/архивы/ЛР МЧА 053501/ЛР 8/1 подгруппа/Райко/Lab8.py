import matplotlib.pyplot as plot
import sympy as sp
import math
import numpy as np

def calculate_iterations(left_border, right_border, accuracy):
    h = np.power(accuracy, 0.25)
    return (right_border - left_border)/h

integration_types = {
    "left_rect": lambda func, n, left_border, h: 
    sum([func(left_border + i*h) for i in range(int(n))])*h,
    "right_rect": lambda func, n, left_border, h: 
    sum([func(left_border + (i+1)*h) for i in range(int(n))])*h,
    "central_rect": lambda func, n, left_border, h: 
    sum([func(left_border + (i+1/2)*h) for i in range(int(n))])*h,
    "trapezium": lambda func, n, left_border, h: 
    (sum([func(left_border + i*h) for i in range(1, int(n))]) 
    + 0.5*(func(left_border + h*n) + func(left_border)))*h,
    "simpson": lambda func, n, left_border, h : 
    (h/3)*(func(left_border) + func(left_border + float(n)*h) 
        + 2*sum([func(left_border + (2*float(i))*h) for i in range(1, int(n)//2)])
        + 4*sum([func(left_border + (2*i + 1)*h) for i in range(int(n)//2)]))
}

def integrate(func, left_border, right_border, accuracy, _type_, total=None):
    if _type_ is not "simpson":
        n = np.ceil(calculate_iterations(left_border, right_border, accuracy))
        h = (right_border - left_border)/n
        I = integration_types[_type_](func, n, left_border, h, 4)
        I_prev = I + accuracy*20
        counter = 0
        while abs(I - I_prev)/3 > accuracy or (total is not None and counter < total):
            counter += 1
            I_prev = I
            h /= 2
            n *= 2
            I = integration_types[_type_](func, n, left_border, h)
        return I, counter
    else:
        n = np.ceil(calculate_iterations(left_border, right_border, accuracy, 4) / 2) * 2
        print(n)
        h = (right_border - left_border)/n
        print(h)
        I = integration_types[_type_](func, n, left_border, h)
        print(I)
        print('step')
        I_prev = I + accuracy*20
        counter = 0
        while abs(I - I_prev)/15 > accuracy or (total is not None and counter < total):
            counter += 1
            I_prev = I
            h /= 2
            n *= 2
            I = integration_types[_type_](func, n, left_border, h)
        return I, counter
        
print("Calculation results:")
print("left_rect metod: (result, steps)")
print(integrate(lambda x: np.sqrt(np.tan(x)), 0, 1.5, 1e-11, "left5_rect"))
print("right_rect method: (result. steps)")
print(integrate(lambda x: np.sqrt(np.tan(x)), 0, 1.5, 1e-11, "right_rect"))
print("central_rect method: (result. steps)")
print(integrate(lambda x: np.sqrt(np.tan(x)), 0, 1.5, 1e-11, "central_rect"))
print("trapezium method: (result. steps)")
print(integrate(lambda x: np.sqrt(np.tan(x)), 0, 1.5, 1e-11, "trapezium"))
print("simpson method: (result. steps)")
print(integrate(lambda x: np.sqrt(np.tan(x)), 0, 1.5, 1e-11, "simson"))

def diff(func, x, accuracy):
    diff = 10*accuracy
    h = 0.1
    derivative = 10*accuracy
    derivative = (func(x + h) - func(x - h))/(2*h)
    counter = 0
    while abs(diff) > accuracy:
        temp = derivative
        derivative = (func(x + h) - func(x - h))/(2*h)
        if counter != 0:
            diff = derivative - temp
        else:
            diff = 10*accuracy
        h /= 4
        counter += 1
    return derivative, counter

print(diff(lambda x: np.sqrt(np.tan(x)), 0.75, 1e-5))
def diff2(func, x, accuracy):
    diff = 10*accuracy
    h = 0.1
    derivative = 10*accuracy
    derivative = (func(x + h) - func(x - h))/(2*h)
    counter = 0
    while abs(diff) > accuracy:
        temp = derivative
        derivative = (func(x + h) + func(x - h) - 2*func(x))/(4*h**2)
        if counter != 0:
            diff = derivative - temp
        else:
            diff = 10*accuracy
        h /= 4
        counter += 1
    return derivative, counter

print(diff2(lambda x: np.sqrt(np.tan(x)), 0.75, 1e-5))