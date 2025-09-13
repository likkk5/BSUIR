import numpy


def input_values():
    k_for_matrix = 12
    matrix_c = numpy.array([
        [0.2, 0.0, 0.2, 0.0, 0.0],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.2, 0.0, 0.2, 0.0, 0.2],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.0, 0.0, 0.2, 0.0, 0.2]
    ])
    matrix_d = numpy.array([
        [2.33, 0.81, 0.67, 0.92, -0.53],
        [0.81, 2.33, 0.81, 0.67, 0.92],
        [0.67, 0.81, 2.33, 0.81, 0.92],
        [0.92, 0.67, 0.81, 2.33, -0.53],
        [-0.53, 0.92, 0.92, -0.53, 2.33]
    ])
    matrix_a = k_for_matrix * matrix_c + matrix_d

    return matrix_a


def input_values1():
    matrix_a = numpy.array([[2, 1],
                            [1, 3]])
    return matrix_a


def input_values2():
    matrix_a = numpy.array([[5, 1, 2],
                            [1, 4, 1],
                            [2, 1, 3]])
    return matrix_a



