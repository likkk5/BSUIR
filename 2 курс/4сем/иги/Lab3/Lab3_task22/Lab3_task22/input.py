import random

def input_abc():
    """Returns G/U value."""
    while True:
        try:
            x = input("Enter 'G' to generate automatically or 'U' for user input: ").upper()
            break;
        except ValueError:
            print("Incorrect input, try again!")
    return x

def input_int():
    while True:
        try:
            a = int(input("Enter int value(enter 0 to stop) "))
            break;
        except ValueError:
            print("Incorrect input, try again!")
    return a

#нет необходимости хранить все данные
def generate_random_sequence():
    """Generator for a sequence of floating-point values."""
    while True:
        yield random.randint(0, 1000)


def continue_or_exit():
    """Provides a choice to the user to continue or exit the program."""
    while True:
        choice = input("Do you want to continue (Y/N)? ").strip().upper()
        if choice == 'Y':
            return True
        elif choice == 'N':
            return False
        else:
            print("Invalid choice. Please enter 'Y' to continue or 'N' to exit.")
