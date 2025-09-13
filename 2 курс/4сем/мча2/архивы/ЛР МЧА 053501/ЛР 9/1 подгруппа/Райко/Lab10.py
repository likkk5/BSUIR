import numpy as np
import sympy as sp
import math
import matplotlib.pyplot as plt

m = 1.5
a = 1.3

target_function = lambda x, y : (a*(1 - y**2))/((1 + m)*x**2 + y**2 + 1)
function = lambda x, y: y

initial_value = (0, 0)
solution_range = [0, 1]

def calculate_iterations(left_border, right_border, accuracy):
    h = np.power(accuracy, 0.25)
    return (right_border - left_border)/h

def calculate_additional_points(function, initial_value, h):
    points = [
        [initial_value[0]],
        [initial_value[1]]
    ]
    points[0].append(points[0][0] + h)
    k = []
    k.append(h*function(points[0][0], points[1][0]))
    k.append(h*function(points[0][0] + h/2, points[1][0] + k[0]/2))
    k.append(h*function(points[0][0] + h/2, points[1][0] + k[1]/2))
    k.append(h*function(points[0][0] + h, points[1][0] + k[2]))
    points[1].append(points[1][0] + (1/6)*(k[0] + k[3] + 2*(k[1]+k[2])))
    return points

def get_diff(data_new, data_old):
    size = len(data_old)
    if size == 1:
        return 100
    dY = np.array([data_new[2*i] - data_old[i] for i in range(2, size)])
    return (dY @ dY)/(size - 1)

def adams_method(function, _range_, initial_value, accuracy):
    n = np.ceil(calculate_iterations(_range_[0], _range_[1], accuracy))
    accuracy_sequence = [
        [],
        []
    ]
    h = (_range_[1] - _range_[0])/n
    points = calculate_additional_points(function, initial_value, h)
    for i in range(int(n) - 1):
        points[0].append(points[0][i + 1] + h)
        points[1].append(points[1][i + 1] + h*((3/2)*function(points[0][i + 1], points[1][i + 1]) - (1/2)*function(points[0][i], points[1][i])))
    diff = accuracy*4
    counter = 0
    while diff > accuracy*accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = calculate_additional_points(function, initial_value, h)
        for i in range(int(n) - 1):
            points[0].append(points[0][i + 1] + h)
            points[1].append(points[1][i + 1] + h*((3/2)*function(points[0][i + 1], points[1][i + 1]) - (1/2)*function(points[0][i], points[1][i])))
        diff = get_diff(points[1], points_temp[1])
        accuracy_sequence[0].append(counter)
        accuracy_sequence[1].append(math.log10(math.sqrt(diff)))
        counter += 1
    print("Method - adams : " + str(n))
    plt.scatter(points[0], points[1])
    return None

adams_method(target_function, solution_range, initial_value, 1e-6)