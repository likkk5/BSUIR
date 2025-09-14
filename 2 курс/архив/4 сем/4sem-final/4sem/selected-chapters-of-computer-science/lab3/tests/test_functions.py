import math
import unittest

from custom_serializer.encoder.encoder import Encoder


def return_5():
    return 5


def recursion(x):
    if x < 2:
        return 1

    return recursion(x - 1) * x


def square(value):
    return value * value


def sqrt(value):
    return math.sqrt(value)


def function_use_return_5():
    return return_5()


GLOBAL_VAR = 10


def function_use_global_value():
    return GLOBAL_VAR


class TestFunction(unittest.TestCase):
    def test_without_params(self):
        decoded_function = Encoder.decode(Encoder.encode(return_5))

        result = return_5()
        result_to_test = decoded_function()

        return self.assertEqual(result, result_to_test)

    def test_with_params(self):
        decoded_function = Encoder.decode(Encoder.encode(square))

        x = 5
        result = square(x)
        result_to_test = decoded_function(x)

        return self.assertEqual(result, result_to_test)

    def test_with_lib(self):
        encoded = Encoder.encode(sqrt)
        decoded_function = Encoder.decode(encoded)

        x = 5
        result = sqrt(x)
        result_to_test = decoded_function(x)

        return self.assertEqual(result, result_to_test)

    def test_recursion(self):
        decoded_function = Encoder.decode(Encoder.encode(recursion))

        value = 5
        result = recursion(value)
        result_to_test = decoded_function(value)

        return self.assertEqual(result, result_to_test)

    def test_lambda(self):
        test_function = lambda value: value * value * value
        decoded_function = Encoder.decode(Encoder.encode(test_function))

        x = 5
        result = test_function(x)
        result_to_test = decoded_function(x)

        return self.assertEqual(result, result_to_test)

    def test_function_use_another_function(self):
        decoded_function = Encoder.decode(Encoder.encode(function_use_return_5))

        result = 5
        result_to_test = decoded_function()

        return self.assertEqual(result, result_to_test)

    def test_function_use_global_value(self):
        decoded_function = Encoder.decode(Encoder.encode(function_use_global_value))

        result = GLOBAL_VAR
        result_to_test = decoded_function()

        return self.assertEqual(result, result_to_test)


def double_result(func):
    def wrapper(*args, **kwargs):
        value = func(*args, **kwargs)
        return value * 2

    return wrapper


@double_result
def doubled():
    return 5


class TestFunctionWrappers(unittest.TestCase):
    def test_decorator(self):
        encoded = Encoder.encode(double_result)
        decoded_function = Encoder.decode(encoded)

        @decoded_function
        def function():
            return 5

        result = 10
        result_to_test = function()

        return self.assertEqual(result, result_to_test)

    def test_decorated_function(self):
        encoded = Encoder.encode(doubled)
        decoded_function = Encoder.decode(encoded)

        result = 10
        result_to_test = decoded_function()

        return self.assertEqual(result, result_to_test)


def top_level():
    a = 10

    def closure():
        nonlocal a
        a += 1
        return a

    return closure


class TestClosures(unittest.TestCase):
    def test_function_with_closure(self):
        closure = top_level()
        encoded = Encoder.encode(closure)
        decoded_function = Encoder.decode(encoded)

        result = 11
        result_to_test = decoded_function()

        self.assertEqual(result, result_to_test)

        result = 12
        result_to_test = decoded_function()

        return self.assertEqual(result, result_to_test)


iterator = iter([1, 2, 3])


def gen():
    yield 1
    yield 2
    yield 3


class TestIterators(unittest.TestCase):
    def test_iter(self):
        encoded = Encoder.encode(iterator)
        decoded_iter = Encoder.decode(encoded)

        result = [1, 2, 3]
        result_to_test = list(decoded_iter)

        return self.assertSequenceEqual(result, result_to_test)

    def test_generator_function(self):
        encoded = Encoder.encode(gen)
        decoded_function = Encoder.decode(encoded)

        result = [1, 2, 3]
        result_to_test = list(decoded_function())

        return self.assertSequenceEqual(result, result_to_test)

    def test_generator_obj(self):
        encoded = Encoder.encode(gen())
        decoded_gen = Encoder.decode(encoded)

        result = [1, 2, 3]
        result_to_test = list(decoded_gen)

        return self.assertSequenceEqual(result, result_to_test)


if __name__ == "__main__":
    unittest.main()
