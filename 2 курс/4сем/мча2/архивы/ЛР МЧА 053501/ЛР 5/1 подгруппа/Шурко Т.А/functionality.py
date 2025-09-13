import numpy


def main(matrix_a, input_values, power):
    eps = 10 ** (-power)

    numpy.set_printoptions(suppress=True, precision=power, floatmode="fixed")

    n = len(matrix_a)

    print("Input matrix:")
    print(matrix_a)

    if abs((matrix_a - matrix_a.T) ** 2).sum() > eps:
        raise ValueError("Matrix matrix_a is non-symmetric")

    iterations = 0

    answers_vector = numpy.eye(n)
    while True:
        iterations += 1
        max_elem = (0, 1)
        for i in range(n):
            for j in range(i + 1, n):
                if abs(matrix_a[i][j]) > abs(matrix_a[max_elem]):
                    max_elem = (i, j)
        (i, j) = max_elem
        if matrix_a[i][i] == matrix_a[j][j]:
            p = numpy.pi / 4
        else:
            p = 2 * matrix_a[i][j] / (matrix_a[i][i] - matrix_a[j][j])
        c = numpy.cos(1 / 2 * numpy.arctan(p))
        s = numpy.sin(1 / 2 * numpy.arctan(p))
        matrix = numpy.eye(n)
        matrix[i][i] = c
        matrix[i][j] = -s
        matrix[j][i] = s
        matrix[j][j] = c
        matrix_a = matrix.T @ matrix_a @ matrix
        answers_vector = answers_vector @ matrix
        if abs(matrix_a - numpy.diag(numpy.diag(matrix_a))).sum() < eps:
            answer_values = numpy.diag(matrix_a)
            break

    matrix_a = input_values()

    print("------Result------")
    (W, V) = normalization(answer_values, answers_vector)
    print("Eigenvalues: ")
    print(W)
    print("Eigenvectors: ")
    print(V)
    print("Iterations: ", iterations)

    matrix_a = input_values()
    r = numpy.ones(len(matrix_a))
    iterations = 0
    while True:
        iterations += 1
        old_u = (r.T @ matrix_a @ r) / (r.T @ r)
        r = (matrix_a @ r) / numpy.sqrt(sum((matrix_a @ r) ** 2))
        u = (r.T @ matrix_a @ r) / (r.T @ r)
        if abs(u - old_u) < eps:
            break
    print("Power method:")
    print(f"Max value: {u:.{power}f};\nMax vector: {r}")
    print("Iterations count =", iterations)


def normalization(matrix, vector):
    vector = numpy.array([(-i if i[0] < 0 else i) for i in vector.T]).T
    (matrix_, vector_) = list(zip(*(sorted(list(zip(matrix, vector.T)), key=lambda t: t[0]))))
    matrix_ = numpy.array(matrix_)
    vector_ = numpy.array(vector_)
    return matrix_, vector_
