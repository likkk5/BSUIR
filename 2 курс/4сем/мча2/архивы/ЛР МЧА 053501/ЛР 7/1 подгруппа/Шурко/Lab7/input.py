import numpy as np


def input_values(left_interval, right_interval, number_of_nods):
    return get_points(left_interval, right_interval, number_of_nods)


def func(x):
    return np.sqrt(x)


def get_points(left_interval, right_interval, number_of_nods):
    dots = []
    for i in range(number_of_nods):
        x = left_interval + ((right_interval-left_interval) * i) / (number_of_nods - 1)
        y = func(x)
        dots.append((x, y))
    return dots
