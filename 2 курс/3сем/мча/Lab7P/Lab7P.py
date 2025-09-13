#-*-coding:windows-1251-*-
from Spline import spline_built
from AdditionalStaff import input_func
import numpy as np
import matplotlib.pyplot as plt
import Task
import Tests

print(f"����� ���������� �����: {Task.n}")
print("�������� ������� � �����:")
plot_dots = 10 ** 4
dots, f = input_func()
(x, y) = map(list, zip(*dots))
print("(x,y) =", dots, '\n')
plt.plot(x, y, 'ob')
x_plot = np.linspace(min(x), max(x), plot_dots)

y_plot = [f(xdot) for xdot in x_plot]
plt.plot(x_plot, y_plot,label='�������� �������')

spl, output = spline_built(dots)
y_plot = [spl(xdot) for xdot in x_plot]
plt.plot(x_plot, y_plot,label='���������� ������')

output()
xdot=Tests.point_3
print(f"�������� ������� � �����: f({xdot}) =", f(xdot))
print(f"���������� ������ ({xdot}) =", spl(xdot))
print(f"����������� delta({xdot}) =", abs(f(xdot) - spl(xdot)))

plt.legend()
plt.show()

