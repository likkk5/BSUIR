import math
from validate_float_input import InputValidator

class ArcsinSeriesCalculator(InputValidator):
    def __init__(self):
        pass

    def calculate_term(self, x, n):
        """
        Calculate the nth term of the series expansion of arcsin(x)
        """
        # if n == 0:
        #     return x
        # else:
        return (math.factorial(2*n)) / (4**n * (math.factorial(n)**2) * (2*n + 1)) * (x**(2*n + 1))

    def calculate_arcsin_series(self, x, eps=1e-6, max_iterations=500):
        """
        Calculate arcsin(x) using series expansion
        """
        result = 0.0
        iteration = 0
        term = x
        while abs(term) > eps and iteration < max_iterations:
            result += term
            iteration += 1
            term = self.calculate_term(x, iteration)
        return result, iteration

