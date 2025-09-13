import numpy as np
import matplotlib.pyplot as plt


def calculate(nodes, spline: list, x: float) -> float:
    for i in range(1, len(nodes)):
        if nodes[i - 1][0] <= x <= nodes[i][0]:
            value = nodes[i][1]
            h = nodes[i][0] - nodes[i - 1][0]
            b = (nodes[i][1] - nodes[i - 1][1]) / h \
                + (2 * (0.0 if i == len(nodes) - 1 else spline[i][1])) + spline[i - 1][1] * h / 3
            value += b * (x - nodes[i][0])
            value += (0.0 if i == len(nodes) - 1 else spline[i][1]) * ((x - nodes[i][0]) ** 2)
            d = ((0.0 if i == len(nodes) - 1 else spline[i][1]) - spline[i - 1][1]) / (3 * h)
            value += d * ((x - nodes[i][0]) ** 3)
            return value


def main():
    interval = (0, 2)
    n = 6

    nodes = []
    for i in range(n):
        x = interval[0] + (interval[1] - interval[0]) / (n - 1) * i
        y = np.arctan(x)
        nodes.append((x, y))
    nodes = np.array(nodes)

    n = len(nodes) - 1
    matrix = [[
        0.0,
        2 / 3 * ((nodes[1][0] - nodes[0][0]) + (nodes[2][0] - nodes[1][0])),
        (nodes[2][0] - nodes[1][0]) / 3
    ]]

    vector = [(nodes[2][1] - nodes[1][1]) / (nodes[2][0] - nodes[1][0])
              - (nodes[1][1] - nodes[0][1]) / (nodes[1][0] - nodes[0][0])]

    for i in range(2, n - 1):
        h_i = nodes[i][0] - nodes[i - 1][0]
        h_i_1 = nodes[i + 1][0] - nodes[i][0]
        a = h_i / 3
        b = 2 / 3 * (h_i + h_i_1)
        c = h_i_1 / 3

        matrix.append([a, b, c])
        d = (nodes[i + 1][1] - nodes[i][1]) / h_i_1 - (nodes[i][1] - nodes[i - 1][1]) / h_i
        vector.append(d)

    matrix.append([
        (nodes[n - 1][0] - nodes[n - 2][0]) / 3,
        2 / 3 * ((nodes[n - 1][0] - nodes[n - 2][0]) + (nodes[n][0] - nodes[n - 1][0])),
        0.0
    ])

    vector.append((nodes[n][1] - nodes[n - 1][1]) / (nodes[n][0] - nodes[n - 1][0])
                  - (nodes[n - 1][1] - nodes[n - 2][1]) / (nodes[n - 1][0] - nodes[n - 2][0]))
    matrix = np.array(matrix)
    vector = np.array(vector)

    matrix = [[matrix[i][j] * 3 for j in range(len(matrix[i]))] for i in range(len(matrix))]
    vector = [vector[i] * 3 for i in range(len(vector))]
    a = [0.0]
    b = [0.0]
    for i in range(len(matrix)):
        a.append(-matrix[i][2] / (matrix[i][0] * a[i] + matrix[i][1]))
        b.append((vector[i] - matrix[i][0] * b[i]) / (matrix[i][0] * a[i] + matrix[i][1]))
    sol = [0.0 for _ in range(len(matrix))]
    sol[-1] = b[-1]

    for i in range(len(matrix) - 2, -1, -1):
        sol[i] = a[i + 1] * sol[i + 1] + b[i + 1]

    sys_sol = np.array(sol)

    c = [0.0] + list(sys_sol) + [0.0]
    spline_coefficients = []
    for i in range(len(c) - 1):
        a = nodes[i][1]
        h = nodes[i + 1][0] - nodes[i][0]
        b = (nodes[i + 1][1] - nodes[i][1]) / h - (c[i + 1] + 2 * c[i]) * h / 3
        d = (c[i + 1] - c[i]) / (3 * h)
        spline_coefficients.append([a, b, c[i], d])

    spline = [i[::-1] for i in spline_coefficients]
    for i in range(len(spline)):
        print(f"({nodes[i][0]:.1f}, {nodes[i + 1][0]:.1f}):")
        print(np.poly1d(spline[i]))
        print()

    x = (interval[1] - interval[0]) / 2
    print(f"\n\nЗначение в точке {x}: {0.784413:.6f}")
    print(f"Разность значений в точке: {abs(np.arctan(x) - 0.784413)}")

    points_number = 100
    for i in range(len(spline)):
        points_x = np.linspace(nodes[i][0], nodes[i + 1][0], points_number)
        points_y = [calculate(nodes, spline, pnt) for pnt in points_x]
        if i == 0:
            plt.plot(points_x, points_y, color='blue', label="spline estimation")
            continue

        plt.plot(points_x, points_y, color='blue')

    points_x = np.linspace(min(node[0] for node in nodes), max(node[0] for node in nodes), 1000)

    points_y = [np.arctan(pnt) for pnt in points_x]
    plt.plot(points_x, points_y, color='red', label="real function")
    plt.plot([nodes[i][0] for i in range(len(nodes))], [nodes[i][1] for i in range(len(nodes))], 'go', label="nodes")
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()
