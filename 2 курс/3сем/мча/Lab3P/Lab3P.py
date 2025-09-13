from math import pow, fabs

MAX_ITERATIONS = 1000

class Result:
    def __init__(self, root=0, iterations=0):
        self.rootOfEq = root
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
        return pow(x, 3) + self.a * pow(x, 2) + self.b * x + self.c

    def f1(self, x):
        return 3 * pow(x, 2) + 2 * self.a * x + self.b

    def f2(self, x):
        return ((2.0 / 9.0) * pow(self.a, 2) * x - (2.0 / 3.0) * self.b * x + (1.0 / 9.0) * self.a * self.b - self.c)

    def f3(self, x):
        numerator = 4 * pow(self.a, 3) * self.c - pow(self.a * self.b, 2) - 18 * self.a * self.b * self.c + 4 * pow(self.b, 3) + 27 * pow(self.c, 2)
        denominator = pow(self.a * self.a - 3 * self.b, 2)
        return -(9.0 / 4.0) * (numerator / denominator)

    def N(self, x):
        val = [self.f0(x), self.f1(x), self.f2(x), self.f3(x)]
        count = 0
        for i in range(3):
            if val[i] * val[i + 1] < 0:
                count += 1
        return count

    def number_of_roots(self, segment):
        return self.N(segment.a) - self.N(segment.b)

    def segment_with_roots(self, segment, step):
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

    def half_division(self, segment, eps):
        if not (self.f0(segment.a) * self.f0(segment.b) < 0) or self.number_of_roots(segment) != 1:
            return Result(-1, -1)

        iterations = 1
        left, right = segment.a, segment.b
        middle = (left + right) / 2

        while abs(self.f0(middle)) > eps and iterations < MAX_ITERATIONS:
            if self.f0(left) * self.f0(middle) < 0:
                right = middle
            else:
                left = middle
            middle = (left + right) / 2
            iterations += 1

        return Result(middle, iterations)

    def chrod_method(self, segment, eps):
        if not (self.f0(segment.a) * self.f0(segment.b) < 0) or self.number_of_roots(segment) != 1:
            return Result(-1, -1)

        iterations = 1
        Xn_prev, Xn_curr = 0, 0

        if self.f0(segment.b) * (2 * self.a + 6 * segment.b) > 0:
            Xn_prev = segment.a
            Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.b) - self.f0(Xn_prev))) * (segment.b - Xn_prev)

            while fabs(Xn_curr - Xn_prev) > eps and iterations < MAX_ITERATIONS:
                Xn_prev = Xn_curr
                Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.b) - self.f0(Xn_prev))) * (segment.b - Xn_prev)
                iterations += 1
        else:
            Xn_prev = segment.b
            Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.a) - self.f0(Xn_prev))) * (segment.a - Xn_prev)

            while fabs(Xn_curr - Xn_prev) > eps and iterations < MAX_ITERATIONS:
                Xn_prev = Xn_curr
                Xn_curr = Xn_prev - (self.f0(Xn_prev) / (self.f0(segment.a) - self.f0(Xn_prev))) * (segment.a - Xn_prev)
                iterations += 1

        return Result(Xn_curr, iterations)

    def newton_method(self, segment, eps):
        if self.number_of_roots(segment) != 1:
            return Result(-1, -1)

        iterations = 1
        Xn_prev = 0

        if self.f0(segment.b) >= 0:
            Xn_prev = segment.b
        else:
            Xn_prev = segment.a

        Xn_curr = Xn_prev - self.f0(Xn_prev) / self.f1(Xn_prev)

        while fabs(Xn_curr - Xn_prev) > eps and iterations < MAX_ITERATIONS:
            Xn_prev = Xn_curr
            Xn_curr = Xn_prev - self.f0(Xn_prev) / self.f1(Xn_prev)
            iterations += 1

        return Result(Xn_curr, iterations)

if __name__ == "__main__":
    leftSegment = -10
    rightSegment = 10

    a = 20.2374
    b = -131.210
    c = -843.923

    polynomial = Polynomial(a, b, c)

    eps = 0.0001
    signs = 4
    step = 2

    print(f"Segment: [{leftSegment:.{signs}f}, {rightSegment:.{signs}f}]")
    rootsNumber = polynomial.number_of_roots(Segment(leftSegment, rightSegment))
    print(f"Roots: {rootsNumber}\n")

    segmentsWithRoots = polynomial.segment_with_roots(Segment(leftSegment, rightSegment), step)

    if rootsNumber != len(segmentsWithRoots):
        print("**********************************************************\nThe root of even multiplicity is found.")
        print("It is necessary to separate the roots manually.\n")

        segmentsWithRoots.clear()
        segmentsWithRoots = [Segment() for _ in range(rootsNumber)]

        for i in range(rootsNumber):
            print(f"A segment with a root {i + 1}:")
            segmentsWithRoots[i].a, segmentsWithRoots[i].b = map(float, input().split())
    else:
        print("Segments:")
        for segment in segmentsWithRoots:
            print(f"[{segment.a:.{signs}f}, {segment.b:.{signs}f}]")

    print("\n**************************************************************")

    methodsNames = ["The method of half division: ", "The chord method: ", "Newton's Method: "]
    results = {name: [] for name in methodsNames}

    for i in range(rootsNumber):
        results["The method of half division: "].append(polynomial.half_division(segmentsWithRoots[i], eps))
        results["The chord method: "].append(polynomial.chrod_method(segmentsWithRoots[i], eps))
        results["Newton's Method: "].append(polynomial.newton_method(segmentsWithRoots[i], eps))

    for i in range(rootsNumber):
        print(f"\nSegment [{segmentsWithRoots[i].a:.{signs}f}, {segmentsWithRoots[i].b:.{signs}f}]:")
        for j in range(3):
            print(f"{methodsNames[j]:<27}", end=' ')

            if results[methodsNames[j]][i].iterations == -1:
                print("The solution by this method is not possible on this segment")
            else:
                print(f"{results[methodsNames[j]][i].rootOfEq:.{signs}f}. Number of iterations: {results[methodsNames[j]][i].iterations}")

