from matplotlib import pyplot
from adams import evaluate
import numpy as np


h, T, Y_Adams3, Y_exact, error = evaluate(2)
pyplot.title('Green - exact; Blue - Adams3')
pyplot.plot(T, Y_exact, 'g--')
pyplot.plot(T, Y_Adams3, 'b')
pyplot.show()

print('step:', h)
print(f'epsilon: {max(error)}\n')
for it in range(0, len(T), 13):
    print(f'point {T[it]:.3f}: \n\texact - {Y_exact[it]:.3f}, adams - {Y_Adams3[it]:.3f}\n\tdifference:{error[it]}')
