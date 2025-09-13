import random

def input_abc():
    """Returns integer value."""
    while True:
        try:
            x = input("Enter 'G' to generate automatically or 'U' for user input: ").upper()
            break;
        except ValueError:
            print("Incorrect input, try again!")
    return x
def generate_sequence(length):
    """Generator for a sequence of floating-point values."""
    for _ in range(length): #повторяется length раз
        yield random.uniform(-100, 100) #возвращает случайное число с плавающей точкой

def user_input_sequence():
    """
    Function to take sequence as user input
    Returns:
    list: User input sequence
    """
    while True:
        try:
            n = int(input("Enter the length of the sequence: "))
            if n <= 0:
                raise ValueError("Length of the sequence should be positive.")
            break
        except ValueError as e:
            print(e)

    sequence = []
    for i in range(n):
        while True:
            try:
                num = float(input(f"Enter element {i+1}: "))
                sequence.append(num)
                break
            except ValueError:
                print("Invalid input! Please enter a valid real number.")
    return sequence