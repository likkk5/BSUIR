#coding: windows-1251
from initial_phase_simplex import initial_phase_simplex
import numpy as np

if __name__ == "__main__":
    c = np.array([1, 0, 0])
    A = np.array([[1, 1, 1], [2, 2, 2]])
    b = np.array([[0], [0]])
    
    x, B = initial_phase_simplex(c, A, b)
    if x is None:
        print("Задача несовместна")
    else:
        print("Допустимый базисный план:", x)
        print("Базисные индексы:", [int(b) for b in B])



