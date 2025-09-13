import methods
import sympy
m = 0.1
a = 0.8


def main():
    (x, y) = sympy.symbols("x y")
    first_equation = sympy.tan(x * y + m) - x
    sec_equation = a * (x ** 2) + 2 * (y ** 2) - 1
    print("Equations: \n", first_equation, "= 0\n", sec_equation, "= 0\n", "----------------------")
    x0 = 0.6
    y0 = 0.5
    print("Initial approximation: ", (x0, y0))
    graphics = sympy.plot_implicit(sympy.Eq(first_equation, 0), (x, -2, 2), (y, -2, 2), 
    line_color="blue", show=False)
    graphics.extend(sympy.plot_implicit(sympy.Eq(sec_equation, 0), (x, -2, 2), (y, -2, 2), 
    line_color="red", show=False))
    methods.calculate(methods.simple_iterations, x0, y0)
    methods.calculate(methods.newton, x0, y0)
    graphics.show()


if __name__ == '__main__':
    main()
