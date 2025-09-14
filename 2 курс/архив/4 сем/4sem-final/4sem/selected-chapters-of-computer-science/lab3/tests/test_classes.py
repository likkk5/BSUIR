import unittest

from custom_serializer.encoder.encoder import Encoder


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


class TestSimpleClass(unittest.TestCase):
    def test_class_with_value(self):
        encoded = Encoder.encode(ClassWithValue)
        decoded = Encoder.decode(encoded)

        result = ClassWithValue.a
        result_to_test = decoded.a

        return self.assertEqual(result, result_to_test)

    def test_class_with_static_method(self):
        encoded = Encoder.encode(ClassWithStaticAndClassMethods)
        decoded = Encoder.decode(encoded)

        result = ClassWithStaticAndClassMethods.test_static()
        result_to_test = decoded.test_static()

        self.assertEqual(result, result_to_test)

        result = ClassWithStaticAndClassMethods.test_class()
        result_to_test = decoded.test_class()
        self.assertEqual(result, result_to_test)


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


class TestInherited(unittest.TestCase):
    def test_double_inheritance(self):
        encoded = Encoder.encode(ClassC)
        decoded = Encoder.decode(encoded)

        result = ClassC().method_a()
        result_to_test = decoded().method_a()

        self.assertEqual(result, result_to_test)

        result = ClassC().method_b()
        result_to_test = decoded().method_b()

        self.assertEqual(result, result_to_test)


class TestObjects(unittest.TestCase):
    def test_object(self):
        encoded = Encoder.encode(ClassC())
        decoded = Encoder.decode(encoded)

        result = ClassC().method_a()
        result_to_test = decoded.method_a()

        self.assertEqual(result, result_to_test)

        result = ClassC().method_b()
        result_to_test = decoded.method_b()

        self.assertEqual(result, result_to_test)


if __name__ == "__main__":
    unittest.main()
