import math
from custom_serializer import SerializerFactory


class A:
    def my_method(self):
        return 5


class B:
    def another_method(self):
        return 6


class C(A, B):
    pass


x = 10


def my_func(a):
    return math.sin(x * a)


serializer = SerializerFactory.create_serializer("json")

obj = C()
ser_obj = serializer.dumps(obj)
deser_obj = serializer.loads(ser_obj)
print(deser_obj.my_method())
print(deser_obj.another_method())

ser_class = serializer.dumps(C)
deser_class = serializer.loads(ser_class)
obj = deser_class()
print(obj.my_method())
print(obj.another_method())

ser_func = serializer.dumps(my_func)
deser_func = serializer.loads(ser_func)
print(deser_func(20), math.sin(10 * 20))
