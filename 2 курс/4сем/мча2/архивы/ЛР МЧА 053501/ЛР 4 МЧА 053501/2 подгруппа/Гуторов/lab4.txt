import numpy
import sympy

m = 0.2
a = 0.9
eps = 10.0 ** -5
it = 0
x0 = 1.0
y0 = 0.5
(x, y) = sympy.symbols("x y")
eq1 = sympy.tan(x * y + m) - x
eq2 = a * (x ** 2) + 2 * (y ** 2) - 1

print(eq1, "= 0")
print(eq2, "= 0")
print("Начальное приближение =", (x0, y0))

def eqx(x, y):
    return numpy.tan(x * y + m)
def eqy(x, y):
    return numpy.sqrt((1 - a * (x ** 2)) / 2)

def test(method):
    global it
    try:
        (x, y) = method(x0, y0)
        print("(x, y) = ({:.4f}, {:.4f})".format(x, y))
        if (method.__name__ == "SimpleMethod"):
            print(" Используя метод простых итераций: {} итераций".format(it))
        else:
            print(" Используя метод Ньютона: {} итераций".format(it))
    except Exception as ex:
        print("Ошибка: {} - в методе с {} итерациями".format(ex, method.__name__, it))

def SimpleMethod(x0, y0):
    global it
    it = 0
    (x, y) = (x0, y0)
    while True:
        it += 1
        oldx = x
        oldy = y
        x = eqx(x,y)
        y = eqy(x,y)
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Последовательность {x} расходится")
        if (max(abs(x - oldx), abs(y - oldy)) < eps):
            return (x, y)

def NewtonMethod(x0, y0):
    global it
    it = 0
    (x, y) = (x0, y0)
    while True:
        it += 1
        w = numpy.array([
        [(1 + numpy.tan(x * y + m) ** 2) * y - 1, (1 + numpy.tan(x * y + m) ** 2) * x],
        [2 * a * x, 4 * y]
    ])
        f = numpy.array([[numpy.tan(x * y + m) - x], [a * (x ** 2) + 2 * (y ** 2) - 1]])
        deltas = numpy.linalg.solve(w, -f)
        x += deltas[0][0]
        y += deltas[1][0]
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Последовательность {x} расходится")
        if (max(abs(deltas)) < eps):
            return (x, y)

plots = sympy.plot_implicit(sympy.Eq(eq1, 0), (x, -3, 3), (y, -3, 3), line_color = "green", show = False)
plots.extend(sympy.plot_implicit(sympy.Eq(eq2, 0), (x, -3, 3), (y, -3, 3), line_color = "purple", show = False))
test(SimpleMethod)
test(NewtonMethod)


plots.show()
