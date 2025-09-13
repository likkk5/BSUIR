from numpy import array, sin, cos, arctan, eye, pi, set_printoptions


def get_initial_matrix() -> array:
    c = array([
        [0.2, 0.0, 0.2, 0.0, 0.0],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.2, 0.0, 0.2, 0.0, 0.2],
        [0.0, 0.2, 0.0, 0.2, 0.0],
        [0.0, 0.0, 0.2, 0.0, 0.2]
    ])
    d = array([
        [2.33, 0.81, 0.67, 0.92, -0.53],
        [0.81, 2.33, 0.81, 0.67, 0.92],
        [0.67, 0.81, 2.33, 0.81, 0.92],
        [0.92, 0.67, 0.81, 2.33, -0.53],
        [-0.53, 0.92, 0.92, -0.53, 2.33]
    ])
    k = 4
    res = k * c + d
    return res



def print_matrix(matrix: array):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(f"{matrix[i][j]:5.2f}", end="  ")
        print()


def get_sum_of_sqs_of_non_diag(matrix) -> float:
    sum_: float = 0.0
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if i != j:
                sum_ += matrix[i][j] ** 2

    return sum_


def get_max_of_non_diag(matrix) -> (int, int):
    max_: float = 0.0
    max_row: int = 0
    max_col: int = 0
    for i in range(len(matrix) - 1):
        for j in range(i + 1, len(matrix[i])):
            if abs(matrix[i][j]) > max_:
                max_ = abs(matrix[i][j])
                max_row = i
                max_col = j

    return max_row, max_col


def get_phi(matrix: array, idx: (int, int)) -> float:
    if matrix[idx[0]][idx[0]] == matrix[idx[1]][idx[1]]:
        p = pi / 4
    else:
        p = 2 * matrix[idx[0]][idx[1]] / (matrix[idx[0]][idx[0]] - matrix[idx[1]][idx[1]])
    res = 0.5 * arctan(p)

    return res


def get_v(size: int, idx: (int, int), phi: float) -> array:
    v_ = eye(size)
    v_[idx[0]][idx[0]] = v_[idx[1]][idx[1]] = cos(phi)
    v_[idx[0]][idx[1]] = -sin(phi)
    v_[idx[1]][idx[0]] = sin(phi)

    return v_


def solve_jacobi(matrix: array) -> (array, array):
    v: array = eye(len(matrix))
    iterations = 0
    while get_sum_of_sqs_of_non_diag(matrix) >= EPS:
        iterations += 1
        max_el_idx: (int, int) = get_max_of_non_diag(matrix)

        phi = get_phi(matrix, max_el_idx)

        next_v = get_v(len(matrix), max_el_idx, phi)
        v = v @ next_v
        matrix = next_v.T @ matrix @ next_v

    eigenvalues = array([matrix[i][i] for i in range(len(matrix))])

    return eigenvalues, v


def main():
    a = get_initial_matrix()

    print("Исходная матрица:")
    print_matrix(a)

    values, vectors = solve_jacobi(a)
    set_printoptions(suppress=True, precision=4, floatmode="fixed")
    print("\nВектор собственных значений:")
    print(values)
    print("\nСобственные векторы:")
    vectors = array([vect for vect in vectors.T])
    for vect in vectors:
        print(vect)

if __name__ == '__main__':
    EPS = 0.0001
    main()
