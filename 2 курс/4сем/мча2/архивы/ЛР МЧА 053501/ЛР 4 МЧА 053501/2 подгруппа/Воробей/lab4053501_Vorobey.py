import numpy
import sympy


(x, y) = sympy.symbols("x y")

print(sympy.tan(x * y + 0.2) - x, "= 0")
print(0.9 * (x ** 2) + 2 * (y ** 2) - 1, "= 0")


def eqx(x, y):
    return numpy.tan(x * y + 0.2)
def eqy(x, y):
    return numpy.sqrt((1 - 0.9 * (x ** 2)) / 2)

def val1(x, y):
    return numpy.tan(x * y + 0.2) - x
def val2(x, y):
    return 0.9 * (x ** 2) + 2 * (y ** 2) - 1

# Якоби
def W(x, y):
    return numpy.array([
        [(1 + numpy.tan(x * y + 0.2) ** 2) * y - 1, (1 + numpy.tan(x * y + 0.2) ** 2) * x],
        [2 * 0.9 * x, 4 * y]
    ])



plots = sympy.plot_implicit(sympy.Eq(sympy.tan(x * y + 0.2) - x, 0), (x, -2, 2), (y, -2, 2), line_color = "blue", show = False)
plots.extend(sympy.plot_implicit(sympy.Eq(0.9 * (x ** 2) + 2 * (y ** 2) - 1, 0), (x, -2, 2), (y, -2, 2), line_color = "red", show = False))
plots.show()


def SimpleMethod(x0, y0):
    global iters
    iters = 0
    (x, y) = (x0, y0)
    iters += 1
    oldx = x
    oldy = y
    x = eqx(x, y)
    y = eqy(x, y)


def NewtonMethod(x0, y0):
    global iters
    iters = 0
    (x, y) = (x0, y0)
    while True:
        iters += 1
        w = W(x, y)
        f = numpy.array([[val1(x, y)], [val2(x, y)]])
        deltas = numpy.linalg.solve(w, -f)
        x += deltas[0][0]
        y += deltas[1][0]
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Sequence {x} is divergent")



x0 = 1.0
y0 = 0.5

def test(method):
    global iters
    try:
        (x, y) = method(x0, y0)
        print("(x, y) = ({:.4f}, {:.4f})".format(x, y))
        print(" via {} method (with {} iterations)".format(method.__name__, iters))
    except Exception as ex:
        print("ERROR: {} - in {} method (with {} iterations)".format(ex, method.__name__, iters))
    print()

test(SimpleMethod)
test(NewtonMethod)


plots.show()
