import numpy
import sympy

m = 0.1
a = 0.8
(x, y) = sympy.symbols("x y")

print(sympy.tan(x * y + m) - x, "= 0")
print(a * (x ** 2) + 2 * (y ** 2) - 1, "= 0")
print()

count = 0

def Simple(x0, y0):
    global count
    count = 0
    (x, y) = (x0, y0)
    while True:
        count += 1
        oldx = x
        oldy = y
        x = numpy.tan(x * y + m)
        y = numpy.sqrt((1 - a * (x ** 2)) / 2)
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Последовательность расходится")
        if (max(abs(x - oldx), abs(y - oldy)) < 10.0 ** -5):
            return (x, y)


def Newton(x0, y0):
    global count
    count = 0
    (x, y) = (x0, y0)
    while True:
        count += 1
        num1 = numpy.array([[numpy.tan(x * y + m) - x], [a * (x ** 2) + 2 * (y ** 2) - 1]])
        num = numpy.array([
            [(1 + numpy.tan(x * y + m) ** 2) * y - 1, (1 + numpy.tan(x * y + m) ** 2) * x],
            [2 * a * x, 4 * y]
        ])
        deltas = numpy.linalg.solve(num, -num1)
        x += deltas[0][0]
        y += deltas[1][0]

        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Последовательность расходится")

        if (max(abs(deltas)) < 10.0 ** -5):
            return (x, y)


x0 = 1.0
y0 = 0.4
print((x0, y0))
print()


def test(method):
    global count
    try:
        (x, y) = method(x0, y0)
        print("(x, y) = ({:.4f}, {:.4f})".format(x, y))
        print(" via {} (with {} iterations)".format(method.__name__, count))
    except Exception as ex:
        print("ERROR: {} - in {} method (with {} iterations)".format(ex, method.__name__, count))
    print()


test(Simple)
test(Newton)

plots = sympy.plot_implicit(sympy.Eq(sympy.tan(x * y + m) - x, 0), (x, -2, 2), (y, -2, 2), line_color = "blue", show = False)
plots.extend(sympy.plot_implicit(sympy.Eq(a * (x ** 2) + 2 * (y ** 2) - 1, 0), (x, -2, 2), (y, -2, 2), line_color = "red", show = False))
plots.show()

