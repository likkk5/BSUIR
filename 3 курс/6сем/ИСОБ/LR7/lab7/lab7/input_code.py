def hello_world():
    print("Hello, World!")

def add(a, b):
    return a + b

def multiply(a, b):
    return a * b

def greet_user(name):
    print(f"Hello, {name}!")

def calculate_area_of_circle(radius):
    return 3.14159 * radius * radius

def conditional_example(x):
    if x > 0:
        return "Positive number"
    else:
        return "Negative number"

def loop_example():
    for i in range(5):
        print(f"Loop number {i}")

if __name__ == "__main__":
    hello_world()
    result_add = add(5, 7)
    print("Addition result:", result_add)
    result_multiply = multiply(3, 4)
    print("Multiplication result:", result_multiply)
    greet_user("Ksusha")
    area = calculate_area_of_circle(5)
    print("Area of the circle:", area)
    condition_result = conditional_example(-5)
    print(condition_result)
    loop_example()
