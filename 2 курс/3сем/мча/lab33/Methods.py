from re import I
from sympy import symbols, lambdify
import numpy as np


def bisection_method(function, interval: tuple, tol=0.0001):
    x, y = symbols('x y')
    a, b = interval[0], interval[1]
    mid = (a + b) / 2

    f = lambdify(x, function, "numpy")

    if f(a) * f(b) > 0:
        raise Exception(f"Couldn't solve because there is no roots/more than one root")
    x_delta = tol * 2
    iteration = 1
    while f(mid) > tol or x_delta > tol:
        if f(a) == 0:
            return a, iteration
        elif f(b) == 0:
            return b, iteration
        elif f(mid) == 0:
            return mid, iteration

        if f(a) * f(mid) < 0:
            b = mid
        elif f(b) * f(mid) < 0:
            a = mid

        x_delta = mid
        mid = (a + b) / 2

        x_delta = abs(x_delta - mid)
        iteration += 1

    return mid, iteration


def secant_method(function, interval: tuple, tol=0.0001):
    x, y = symbols('x y')
    a, b = interval[0], interval[1]
    f = lambdify(x, function, "numpy")
    if f(a) * f(b) > 0:
        raise Exception(f"Secant method couldn't solve f(x) = 0, "
                        f"because f(a) * f(b) = {f(a) * f(b)} >= 0\n"
                        f"--> more than 1 root on ({(a, b)}) or no roots)")

    x_sec = a - (f(a) * (b - a)) / (f(b) - f(a))

    x_delta = 0
    iteration = 1
    while abs(f(x_sec)) > tol or x_delta > tol:
        if f(a) == 0:
            return a, iteration
        elif f(b) == 0:
            return b, iteration
        elif f(x_sec) == 0:
            return x_sec, iteration

        if f(x_sec) * f(a) < 0:
            b = x_sec
        elif f(x_sec) * f(b) < 0:
            a = x_sec

        x_delta = x_sec
        x_sec = a - (f(a) * (b - a)) / (f(b) - f(a))

        x_delta = abs(x_delta - x_sec)
        iteration += 1

    return x_sec, iteration


def ClassicalNewtonMethod (polynom, interval, epsilon):
    root = 0
    iterations = 0
    local_left = interval[0]
    local_right = interval[1]
    point = (local_left+local_right)/2;
    while True:
            if (iterations > 1e5):
                print ("Raschoditsya")
                return root
            iterations += 1
            delta_point = np.polyval (polynom, point) / np.polyval (np.polyder (polynom), point)
            point -= delta_point
            if (abs (delta_point) < epsilon):
                root=point
                break
    return root,iterations


def SimplifiedNewtonMethod (polynom, interval,epsilon):
    i = 0
    root=0
    iterations = 0
    local_right = interval[1]
    point = (local_right+interval[0]) / 2
    first_derivative = np.polyval(np.polyder (polynom), point)
    while True:
            iterations += 1 
            if (iterations > 1e5):
                print ("Rasch")
                return root
            delta_point = np.polyval (polynom, point) / first_derivative
            point -= delta_point
            
            if (abs (delta_point) < epsilon):
                root=point
                break
    return root,iterations

def FalsePlacementNewtonMethod (polynom, intervals, epsilon):
    root=0
    iterations = 0
    local_left = intervals[0]
    local_right = intervals[1]
    point = (local_left + local_right) / 2
    while True:
            iterations += 1 
            if (iterations > 1e5):
                print ("Rasch")
                return root
            
            delta_point = ((local_right - point) / (np.polyval (polynom, local_right) - np.polyval (polynom, point))) * np.polyval (polynom, point)
            point -= delta_point
            if (abs (delta_point) < epsilon):
                root=point
                break  
    return root,iterations


def AitkenBoost(point_1, point_2,point_3):
        return point_1-((point_2-point_1)**2)/(point_3-2*point_2+point_1)

def BoostChordMethod(polynom, intervals, left_border, epsilon):
    i = 0
    roots = []
    iterations = 0
    local_left = intervals[0]
    local_right = intervals[1]
    local_point = 0
    point = 0
    if (np. polyval (polynom, local_left) * np.polyval(np.polyder(np.polyder (polynom)), left_border) > 0):
            local_point = local_left
    elif (np.polyval (polynom, local_left) * np.polyval(np.polyder(np.polyder (polynom)), left_border) < 0):
            point = local_left
    if (np.polyval (polynom, local_right) * np.polyval(np.polyder(np.polyder (polynom)), local_right) > 0):
            local_point = local_right
    elif (np. polyval (polynom, local_right) * np.polyval(np.polyder(np.polyder (polynom)), local_right) < 0):
            point = local_right
    temp_roots = []
    delta_point=0
    while True:
        if (iterations > 1e5):
            print ("Rasch")
            return roots
        if (iterations != 0 and iterations % 3 == 0):
            point =AitkenBoost(temp_roots[len(temp_roots)-3],temp_roots[len(temp_roots)-2],temp_roots[len(temp_roots)-1])
            temp_roots.append (point)
            delta_point = temp_roots[len(temp_roots)-1]-temp_roots[len(temp_roots)-2]
        else:
            delta_point = np.polyval (polynom, point) * (point - local_point) / (np.polyval (polynom, point) - np.polyval (polynom, local_point))
            point -= delta_point
            temp_roots.append(point)
        
        iterations += 1
        if (abs (delta_point) < epsilon):
            roots.append (point)
            break
    
    return roots,iterations
