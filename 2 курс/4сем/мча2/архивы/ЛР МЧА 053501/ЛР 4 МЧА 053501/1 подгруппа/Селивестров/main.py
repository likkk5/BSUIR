from sympy import *

#variant 6
eps = 0.0001
m = 0.3
a = 1.0
x = Symbol("x")
y = Symbol("y")
def main():

    print("tg(xy + m) = x")
    print("ax^2 + 2y^2 = 1")
    print("x > 0, y > 0")

    print("Метод простых итераций")
    X = sqrt((1 - 2*y**2) / a)
    Y = (atan(x) - m) / x
    x0 = 1.0
    y0 = 0.4
    ans = simple_iters(X, Y, x0, y0)
    print(f"x = {ans[0]}\ty = {ans[1]}\t число итераций = {ans[2]}")

    print("Метод Ньютона")
    f1 = tan(x*y + m) - x
    f2 = a*x**2 + 2*y**2 - 1
    vec0 = Matrix([1.0, 0.4])
    ans = newton(f1, f2, vec0)
    print(f"x = {ans[0]}\ty = {ans[1]}\t число итераций = {ans[2]}")



def simple_iters(X, Y, x0, y0):
    x1 = X.subs(x, x0).subs(y, y0)
    y1 = Y.subs(x, x0).subs(y, y0)
    count = 1
    while abs(x0 - x1) > eps or abs(y0 - y1) > eps:
        x0 = x1
        y0 = y1
        x1 = X.subs(x, x0).subs(y, y0)
        y1 = Y.subs(x, x0).subs(y, y0)
        #print("Iteration {}".format(count))
        #print(f"x1 {x1}; y1 {y1}")
        count += 1
    return [x1, y1, count]

def newton(f1, f2, vec0):
    F = Matrix([f1, f2])
    J = Matrix([[diff(f1, x), diff(f1, y)], [diff(f2, x), diff(f2, y)]])
    J = J.inv()
    vec1 = (vec0 - J.inv()*F).subs(x, vec0[0]).subs(y, vec0[1])
    count = 1

    while (abs(vec0[0] - vec1[0]) > eps or abs(vec0[1] - vec1[1]) > eps):
      vec0 = vec1
      vec1 = (vec0 - J*F).subs(x, vec0[0]).subs(y, vec0[1])
      count += 1
    return [vec1[0], vec1[1], count]


if __name__ == '__main__':
    main()