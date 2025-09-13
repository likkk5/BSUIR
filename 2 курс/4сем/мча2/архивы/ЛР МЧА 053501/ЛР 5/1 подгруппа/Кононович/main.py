import math


def make_step(a, h):
    current_i = 0
    current_j = 1
    max_el = a[0][1]

    for i in range(len(a) - 1):
        for j in range(i + 1, len(a[i])):
            if abs(a[i][j]) > abs(max_el):
                max_el = a[i][j]
                current_i = i
                current_j = j

    fi = math.pi / 4

    if a[current_i][current_i] != a[current_j][current_j]:
        fi = 0.5 * math.atan(2 * max_el / (a[current_i][current_i] - a[current_j][current_j]))

    cos = math.cos(fi)
    sin = math.sin(fi)

    a[current_i][current_i] = 2 * cos * sin * a[current_i][current_j] + \
                              cos ** 2 * a[current_i][current_i] + sin ** 2 * a[current_j][current_j]

    a[current_j][current_j] = - 2 * cos * sin * a[current_i][current_j] + \
                              sin ** 2 * a[current_i][current_i] + cos ** 2 * a[current_j][current_j]

    for k in range(len(a)):
        h[current_i][k] = cos * v_matrix[k][current_i] - sin * v_matrix[k][current_j]
        h[current_j][k] = sin * v_matrix[k][current_i] + cos * v_matrix[k][current_j]

        if k == current_i or k == current_j:
            continue

        a[current_i][k] = cos * a[k][current_i] + sin * a[k][current_j]
        a[k][current_i] = a[current_i][k]
        a[current_j][k] = -sin * a[k][current_i] + cos * a[k][current_j]
        a[k][current_j] = a[current_j][k]

        a[current_i][current_j] = 0
        a[current_j][current_i] = 0

    return a, h


def is_over(a):
    for i in range(len(a) - 1):
        for j in range(i + 1, len(a[i])):
            if a[i][j] != 0:
                return False
    return True


if __name__ == "__main__":
    matrix = [[3.53, 0.81, 1.87, 0.92, -0.53],
              [-0.53, 3.53, 0.81, 1.87, 0.92],
              [2.12, -0.53, 3.53, 0.81, 1.87],
              [0.67, 2.12, -0.53, 3.53, 0.81],
              [0.81, 0.67, 2.12, -0.53, 3.53]]

    v_matrix = [[1, 0, 0, 0, 0],
                [0, 1, 0, 0, 0],
                [0, 0, 1, 0, 0],
                [0, 0, 0, 1, 0],
                [0, 0, 0, 0, 1]]

    while not is_over(matrix):
        matrix, v_matrix = make_step(matrix, v_matrix)

    print('Собственные значения:')
    for i in range(0, len(matrix) - 1):
        print(matrix[i][i], end=",  ")

    print(matrix[len(matrix) - 1][len(matrix) - 1], end="\n")

    print('Собственные вектора:')
    for j in range(len(v_matrix)):
        print('( ', end='')
        for i in range(len(v_matrix[j]) - 1):
            print(v_matrix[i][j], end=',  ')
        print(v_matrix[len(v_matrix[j]) - 1][j], end=')\n')
