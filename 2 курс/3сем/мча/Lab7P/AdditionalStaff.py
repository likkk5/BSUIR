import numpy as np
import Task
import Tests

def input_func():
    left_border, dots_count, right_border = Task.a, Task.n, Task.b

    dots = []
    for i in range(dots_count):
        x = left_border + (right_border - left_border) * i / (dots_count - 1)
        y = Task.f(x)
        dots += [(x, y)]

    return dots, Task.f

