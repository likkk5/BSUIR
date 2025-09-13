import numpy
from sympy import *
import matplotlib.pyplot as plt   
from scipy.optimize import fsolve

#обозначаем символы х и у как переменные
(x, y) = symbols("x y")

#вводим константы
m = 0.2
a = 0.8

#система из уравнений вида f(x,y) = 0
f1 = tan(x * y + m) - x
f2 = a * (x ** 2) + 2 * (y ** 2) - 1

#функция вида х = w(x,y)
def wx(x, y):
    return numpy.tan(x * y + m)
#функция вида y = w(x,y)
def wy(x, y):
    return numpy.sqrt((1 - a * (x ** 2)) / 2)

#вспомогательные функции для вычисления якобиана
x11 = diff(f1, x)
x12 = diff(f1, y)
x21 = diff(f2, x)
x22 = diff(f2, y)

#вычисляем Якобиан 
def J(x, y):
    return numpy.array([
        [(1 + numpy.tan(x * y + m) ** 2) * y - 1, (1 + numpy.tan(x * y + m) ** 2) * x],
        [2 * a * x, 4 * y]
    ])

# Графики исходных функций
plots = plot_implicit(Eq(f1, 0), (x, -1.5, 1.5), (y, -1.5, 1.5), line_color = "green", show = False)
plots.extend(plot_implicit(Eq(f2, 0), (x, -1.5, 1.5), (y, -1.5, 1.5), line_color = "red", show = False))
plots.show()

Iter_plot_x = []
Iter_plot_y = []

Zeidel_plot_x = []
Zeidel_plot_y = []

Newton_plot_x = []
Newton_plot_y = []
#метод простых итераций
def Iteration_method(x0, y0):
    iters = 0
    (x, y) = (x0, y0)
    while True:
        iters += 1
        p_x = x
        p_y = y
        Iter_plot_x.append(p_x)
        Iter_plot_y.append(p_y)
        x = wx(p_x, p_y)
        y = wy(p_x, p_y)
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Sequence {x} is diverged")
        if (max(abs(x - p_x), abs(y - p_y)) < 0.0001):
            print("Amount of iters in Iteration_method is", iters)
            return (x, y)

#метод Зейделя
def Zeidel_method(x0, y0):
    iters = 0
    (x, y) = (x0, y0)
    while True:
        iters += 1
        p_x = x
        p_y = y
        Zeidel_plot_x.append(p_x)
        Zeidel_plot_y.append(p_y)
        x = wx(x, y)
        y = wy(x, y)
        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Sequence {x} is diverged")
        if (max(abs(x - p_x), abs(y - p_y)) < 0.0001):
            print("Amount of iters in Zeidel_method is", iters)
            return (x, y)

#вычисляем значение функции в точке (х,у)
def func1(x, y):
    return numpy.tan(x * y + m) - x
def func2(x, y):
    return a * (x ** 2) + 2 * (y ** 2) - 1

#метод Ньютона
def Newton_method(x0, y0):
    global iters
    iters = 0
    (x, y) = (x0, y0)
    Newton_plot_x.append(x0)
    Newton_plot_y.append(y0)

    while True:
        iters += 1
        j = J(x, y)
        f = numpy.array([[func1(x, y)], [func2(x, y)]])
        deltas = numpy.linalg.solve(j, -f)
        x += deltas[0][0]
        y += deltas[1][0]

        Newton_plot_x.append(x)
        Newton_plot_y.append(y)

        if (not (numpy.isfinite(x) and numpy.isfinite(y))):
            raise RuntimeError("Sequence {x} is diverged")
        if (max(abs(deltas)) < 0.0001):
            print("Amount of iters in Newton_method is", iters)
            return (x, y)


x0 = 0.6
y0 = 0.6

try:
    print(Iteration_method(x0, y0))
except Exception as ex:
    print("ERROR: {} - in Simple iterarion method".format(ex))


try:
    print(Zeidel_method(x0, y0))
except Exception as ex:
    print("ERROR: {} - in Zeidal method".format(ex))

try:
    print(Newton_method(x0, y0))
except Exception as ex:
    print("ERROR: {} - in Newton method".format(ex))





plt.scatter(Iter_plot_x, Iter_plot_y, color='b')   
plt.title('Simple Iteration')
plt.show()  

plt.scatter(Zeidel_plot_x, Zeidel_plot_y, color='r')   
plt.title('Zeidel')
plt.show()  

plt.scatter(Newton_plot_x, Newton_plot_y, color='g')  
plt.title('Newton')
plt.show()  

plt.legend()  

print(nsolve([f1, f2], [x, y], [0.5, 0.5]))