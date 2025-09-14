from methods import euler, modified_euler, runge_kutta, create_y_dots
import matplotlib.pyplot as plt
plotdots = 10 ** 3
eps = 10 ** -3
m, a = 1.5, 1.3
y0 = 0
left_border, right_border = 0, 1


def y_diff(x, y): return (a * (1 - y ** 2)) / ((1 + m) * x ** 2 + y ** 2 + 1)
def y_sol(x): return 0


print("Amount of dots: ", plotdots)
print("epsilon:  ", eps)
x_dots = [left_border + (right_border - left_border) / plotdots * i for i in range(plotdots + 1)]

ydots, midn, maxn = create_y_dots(euler, x_dots, y0, y_diff, eps)
print("Euler method:")
for i in range(1, 10, 3):
    print(f"x[{i}]: {x_dots[i*100]}\n"
          f"y[{i}]: {ydots[i*100]}\n")
print(f"max amount of parts (n): {maxn}")
print(f"average amount of parts (n): {midn}\n")
plt.plot(x_dots, ydots, 'y')

ydots, midn, maxn = create_y_dots(modified_euler, x_dots, y0, y_diff, eps)
print("Modified Euler:")
for i in range(1, 10, 3):
    print(f"x[{i}] = {x_dots[i*100]}\n"
          f"y[{i}] = {ydots[i*100]}\n")
print(f"max amount of parts (n): {maxn}")
print(f"average amount of parts (n): {midn}\n")
plt.plot(x_dots, ydots, 'b--')

ydots, midn, maxn = create_y_dots(runge_kutta, x_dots, y0, y_diff, eps)
print("Runge-Kutta method: ")
for i in range(1, 10, 3):
    print(f"x[{i}] = {x_dots[i*100]}\n"
          f"y[{i}] = {ydots[i*100]}\n")
print(f"max amount of parts (n): {maxn}")
print(f"average amount of parts (n): {midn}\n")
plt.plot(x_dots, ydots, 'r:')

plt.show()
