# Program: Task 3
# Lab Number: 3
# Program Version: 1.1
# Developer: Lishyk Ksenia
# Date: 27.03.2024
from input_validation import input_string
from binary_check import is_binary_number

def main():
    """
    Main function to execute the program
    """
    while True:
        input_str = input_string()

        if all(char.isdigit() for char in input_str): #остоит ли каждый символ из цифр
            if is_binary_number(input_str):
                print("The input string is a binary number.")
            else:
                print("The input string is not a binary number.")
        else:
            print("Invalid input! Please enter only digits")

        choice = input("Do you want to check another string (Y/N)? ").upper()
        if choice != 'Y':
            break
        if choice == 'N':
            break

if __name__ == "__main__":
    main()
