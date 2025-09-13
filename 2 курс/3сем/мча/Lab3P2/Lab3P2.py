# -*- coding: windows-1251 -*-
import math
from typing import List, Dict
#import numpy as np
import sympy as sp

MAX_ITERATIONS = 1000

class Result:
    def __init__(self, root=0, iterations=0):
        self.root = root
        self.iterations = iterations

class Segment:
    def __init__(self, a=0, b=0):
        self.a = a
        self.b = b

class Polynomial:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def f0(self, x):
        return x ** 3 + self.a * x ** 2 + self.b * x + self.c

    def f1(self, x):
        return 3 * x ** 2 + 2 * self.a * x + self.b

    def f2(self, x):
        return (2.0 / 9.0) * self.a ** 2 * x - (2.0 / 3.0) * self.b * x + (1.0 / 9.0) * self.a * self.b - self.c

    def f3(self, x):
        numerator = 4 * self.a ** 3 * self.c - (self.a * self.b) ** 2 - 18 * self.a * self.b * self.c + 4 * self.b ** 3 + 27 * self.c ** 2
        denominator = (self.a ** 2 - 3 * self.b) ** 2
        return -(9.0 / 4.0) * (numerator / denominator)

    def N(self, x):
        values = [self.f0(x), self.f1(x), self.f2(x), self.f3(x)]
        count = 0

        for i in range(3):
            if values[i] * values[i + 1] < 0:
                count += 1

        return count

    def number_of_roots(self, segment: Segment):
        return self.N(segment.a) - self.N(segment.b)

    def segment_with_roots(self, segment: Segment, step: float):
        segments = []

        x = segment.a
        while x < segment.b:
            if self.f0(x) * self.f0(x + step) < 0:
                segments.append(Segment(x, x + step))
            x += step

        upd_segments = []
        for item in segments:
            if self.number_of_roots(item) != 1:
                upd_segments.extend(self.segment_with_roots(item, step / 2))
            else:
                upd_segments.append(item)
        return upd_segments

    def half_division(self, segment: Segment, eps: float):
        if not (self.f0(segment.a) * self.f0(segment.b) < 0) or self.number_of_roots(segment) != 1:
            return Result(-1, -1)

        iterations = 1
        left, right = segment.a, segment.b
        mid = (left + right) / 2

        while abs(self.f0(mid)) > eps and iterations < MAX_ITERATIONS:
            if self.f0(left) * self.f0(mid) < 0:
                right = mid
            else:
                left = mid
            mid = (left + right) / 2
            iterations += 1

        return Result(mid, iterations)

    def chord_method(self, segment: Segment, eps: float):
        if not (self.f0(segment.a) * self.f0(segment.b) < 0) or self.number_of_roots(segment) != 1:
            return Result(-1, -1)

        iterations = 1
        Xn_prev, Xn_curr = 0, 0

        if self.f0(segment.b) * (2 * self.a + 6 * segment.b) > 0:
            Xn_prev = segment.a
            Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.b) - self.f0(Xn_prev)) * (segment.b - Xn_prev))

            while abs(Xn_curr - Xn_prev) > eps and iterations < MAX_ITERATIONS:
                Xn_prev = Xn_curr
                Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.b) - self.f0(Xn_prev)) * (segment.b - Xn_prev))
                iterations += 1
        else:
            Xn_prev = segment.b
            Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.a) - self.f0(Xn_prev)) * (segment.a - Xn_prev))

            while abs(Xn_curr - Xn_prev) > eps and iterations < MAX_ITERATIONS:
                Xn_prev = Xn_curr
                Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.a) - self.f0(Xn_prev)) * (segment.a - Xn_prev))
                iterations += 1

        return Result(Xn_curr, iterations)

    def newton_method(self, segment: Segment, eps: float):
        if self.number_of_roots(segment) != 1:
            return Result(-1, -1)

        iterations = 1
        Xn_prev = 0

        if self.f0(segment.b) >= 0:
            Xn_prev = segment.b
        else:
            Xn_prev = segment.a

        Xn_curr = Xn_prev - self.f0(Xn_prev) / self.f1(Xn_prev)

        while abs(Xn_curr - Xn_prev) > eps and iterations < MAX_ITERATIONS:
            Xn_prev = Xn_curr
            Xn_curr = Xn_prev - self.f0(Xn_prev) / self.f1(Xn_prev)
            iterations += 1

        return Result(Xn_curr, iterations)

if __name__ == "__main__":
    LSegment = -10
    RSegment = 10

    x = sp.symbols('x')
    a = -14.4621 
    b = 60.6959
    c = -70.9238
    equation = x**3 + a*x**2 + b*x + c
    
    polynomial = Polynomial(a, b, c)

    eps = float(input("Считать корни с точностью eps = "))
    signs = int(input("Выводить знаков после запятой в корнях: "))
    step = float(input("Отделять корни табличным методом с шагом: "))

    print(f"Отрезок: [{LSegment:.{signs}f}, {RSegment:.{signs}f}]\n")

    rootsNumber = polynomial.number_of_roots(Segment(LSegment, RSegment))
    print(f"Корней: {rootsNumber}\n")

    segmentsWithRoots = polynomial.segment_with_roots(Segment(LSegment, RSegment), step)

    if rootsNumber != len(segmentsWithRoots):
        print("Обнаружен корень четной кратности.")
        print("Необходимо отделить корни вручную.\n")

        segmentsWithRoots = [Segment() for _ in range(rootsNumber)]

        for i in range(rootsNumber):
            print(f"Отрезок с корнем {i + 1}:")
            segmentsWithRoots[i].a, segmentsWithRoots[i].b = map(float, input().split())
    else:
        print("Отрезки:")
        for segment in segmentsWithRoots:
            print(f"[{segment.a:.{signs}f}, {segment.b:.{signs}f}]")

    print("\n**************************************************************")

    methodsNames = ["Метод половинного деления: ", "Метод хорд: ", "Метод Ньютона: "]
    results: Dict[str, List[Result]] = {name: [] for name in methodsNames}

    for i in range(rootsNumber):
        results["Метод половинного деления: "].append(polynomial.half_division(segmentsWithRoots[i], eps))
        results["Метод хорд: "].append(polynomial.chord_method(segmentsWithRoots[i], eps))
        results["Метод Ньютона: "].append(polynomial.newton_method(segmentsWithRoots[i], eps))

    for i in range(rootsNumber):
        print(f"\nОтрезок [{segmentsWithRoots[i].a:.{signs}f}, {segmentsWithRoots[i].b:.{signs}f}]:")
        for j in range(3):
            print(f"{methodsNames[j]:<27}", end=' ')

            if results[methodsNames[j]][i].iterations == -1:
                print("решение данным методом на данном отрезке невозможно")
            else:
                print(f"{results[methodsNames[j]][i].root:.{signs}f}. Итераций: {results[methodsNames[j]][i].iterations}")


accurate_solution=sp.solve(equation)
print("Точное решение x:", accurate_solution)