import math
import unittest
from custom_serializer import SerializerFactory


def return_5():
    return 5


def square(value):
    return value * value


def recursion(x):
    if x < 2:
        return 1

    return recursion(x - 1) * x


def function_use_return_5():
    return return_5()


def sqrt(value):
    return math.sqrt(value)


GLOBAL_VAR = 10


def function_use_global_value():
    return GLOBAL_VAR


def double_result(func):
    def wrapper(*args, **kwargs):
        value = func(*args, **kwargs)
        return value * 2

    return wrapper


@double_result
def doubled():
    return 5


def top_level():
    a = 10

    def closure():
        nonlocal a
        a += 1
        return a

    return closure


def gen():
    yield 1
    yield 2
    yield 3


class ClassWithValue:
    a = 1


class ClassWithStaticAndClassMethods:
    b = 4

    @staticmethod
    def test_static():
        return 5

    @classmethod
    def test_class(cls):
        return cls.b


class ClassA:
    def __init__(self):
        super().__init__()
        self.a = 1

    def method_a(self):
        return self.a


class ClassB:
    def __init__(self):
        super().__init__()
        self.b = 2

    def method_b(self):
        return self.b


class ClassC(ClassB, ClassA):
    def __init__(self):
        super().__init__()


class TestSerializer(unittest.TestCase):
    def setUp(self) -> None:
        self.serializers = [
            SerializerFactory.create_serializer("json"),
            SerializerFactory.create_serializer("xml"),
        ]

    def test_without_params(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(serializer.dumps(return_5))

                result = return_5()
                result_to_test = decoded_function()

                self.assertEqual(result, result_to_test)

    def test_with_params(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(serializer.dumps(square))

                x = 5
                result = square(x)
                result_to_test = decoded_function(x)

                self.assertEqual(result, result_to_test)

    def test_with_lib(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(serializer.dumps(sqrt))

                x = 5
                result = sqrt(x)
                result_to_test = decoded_function(x)

                self.assertEqual(result, result_to_test)

    def test_recursion(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(serializer.dumps(recursion))

                value = 5
                result = recursion(value)
                result_to_test = decoded_function(value)

                self.assertEqual(result, result_to_test)

    def test_lambda(self):
        for serializer in self.serializers:
            with self.subTest():
                test_function = lambda value: value * value * value
                decoded_function = serializer.loads(serializer.dumps(test_function))

                x = 5
                result = test_function(x)
                result_to_test = decoded_function(x)

                self.assertEqual(result, result_to_test)

    def test_function_use_another_function(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(
                    serializer.dumps(function_use_return_5)
                )

                result = 5
                result_to_test = decoded_function()

                self.assertEqual(result, result_to_test)

    def test_function_use_global_value(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(
                    serializer.dumps(function_use_global_value)
                )

                result = GLOBAL_VAR
                result_to_test = decoded_function()

                self.assertEqual(result, result_to_test)

    def test_decorator(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(serializer.dumps(double_result))

                @decoded_function
                def function():
                    return 5

                result = 10
                result_to_test = function()

                self.assertEqual(result, result_to_test)

    def test_decorated_function(self):
        for serializer in self.serializers:
            with self.subTest():
                decoded_function = serializer.loads(serializer.dumps(doubled))

                result = 10
                result_to_test = decoded_function()

                self.assertEqual(result, result_to_test)

    def test_function_with_closure(self):
        for serializer in self.serializers:
            with self.subTest():
                closure = top_level()
                decoded_function = serializer.loads(serializer.dumps(closure))

                result = 11
                result_to_test = decoded_function()

                self.assertEqual(result, result_to_test)

                result = 12
                result_to_test = decoded_function()

                self.assertEqual(result, result_to_test)

    def test_iter(self):
        for serializer in self.serializers:
            with self.subTest():
                iterator = iter([1, 2, 3])
                encoded = serializer.dumps(iterator)
                decoded_iter = serializer.loads(encoded)

                result = [1, 2, 3]
                result_to_test = list(decoded_iter)

                self.assertSequenceEqual(result, result_to_test)

    def test_generator_function(self):
        for serializer in self.serializers:
            with self.subTest():
                encoded = serializer.dumps(gen)
                decoded_function = serializer.loads(encoded)

                result = [1, 2, 3]
                result_to_test = list(decoded_function())

                self.assertSequenceEqual(result, result_to_test)

    def test_generator_obj(self):
        for serializer in self.serializers:
            with self.subTest():
                encoded = serializer.dumps(gen())
                decoded_gen = serializer.loads(encoded)

                result = [1, 2, 3]
                result_to_test = list(decoded_gen)

                self.assertSequenceEqual(result, result_to_test)

    def test_class_with_value(self):
        for serializer in self.serializers:
            with self.subTest():
                encoded = serializer.dumps(ClassWithValue)
                decoded = serializer.loads(encoded)

                result = ClassWithValue.a
                result_to_test = decoded.a

                self.assertEqual(result, result_to_test)

    def test_class_with_static_method(self):
        for serializer in self.serializers:
            with self.subTest():
                encoded = serializer.dumps(ClassWithStaticAndClassMethods)
                decoded = serializer.loads(encoded)

                result = ClassWithStaticAndClassMethods.test_static()
                result_to_test = decoded.test_static()

                self.assertEqual(result, result_to_test)

                result = ClassWithStaticAndClassMethods.test_class()
                result_to_test = decoded.test_class()
                self.assertEqual(result, result_to_test)

    def test_double_inheritance(self):
        for serializer in self.serializers:
            with self.subTest():
                encoded = serializer.dumps(ClassC)
                decoded = serializer.loads(encoded)

                result = ClassC().method_a()
                result_to_test = decoded().method_a()

                self.assertEqual(result, result_to_test)

                result = ClassC().method_b()
                result_to_test = decoded().method_b()

                self.assertEqual(result, result_to_test)

    def test_object(self):
        for serializer in self.serializers:
            with self.subTest():
                encoded = serializer.dumps(ClassC())
                decoded = serializer.loads(encoded)

                result = ClassC().method_a()
                result_to_test = decoded.method_a()

                self.assertEqual(result, result_to_test)

                result = ClassC().method_b()
                result_to_test = decoded.method_b()

                self.assertEqual(result, result_to_test)


if __name__ == "__main__":
    unittest.main()
