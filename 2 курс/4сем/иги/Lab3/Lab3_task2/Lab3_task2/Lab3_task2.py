# Program: Task 2
# Lab Number: 3
# Program Version: 1.0
# Developer: Lishyk Ksenia
# Date: 27.03.2024

import sys
import random

def input_sequence():
    """
    Function to initialize the sequence either by generator function or user input
    Returns:
    list: Initialized sequence
    """
    count=0
    total_sum=0
    while True:
        choice = input("Enter 'G' to generate sequence or 'U' for user input: ").upper()
        if choice == 'G':
            #return generate_sequence()
            for num in generate_sequence():
                print(num)
                total_sum+=num
                if num > 12:
                    count += 1
                if total_sum>500:
                    return total_sum
                               
        elif choice == 'U':
            return user_input_sequence()
        else:
            print("Invalid choice! Please enter 'G' or 'U'.")

# def generate_sequence():
#     """
#     Function to generate sequence using a generator function
#     Returns:
#     list: Generated sequence
#     """
#     while True:
#         try:
#             n = int(input("Enter the length of the sequence: "))
#             if n <= 0:
#                 raise ValueError("Length of sequence should be a positive integer.")
#             sequence = [i for i in range(1, n + 1)]
#             print("Generated sequence:", sequence)
#             return sequence
#         except ValueError as e:
#           if "invalid literal for int() with base 10" in str(e):
#             print("Invalid input! Please enter a valid integer.")
#           else:
#             print(e)

def generate_sequence():
    while True:
        yield random.randint(0, 100)

def user_input_sequence():
    """
    Function to take sequence as user input
    Returns:
    list: User input sequence
    """
    sequence = []
    while True:
        num = input("Enter a number (0 to finish): ")
        try:
            num = int(num)
            if num == 0:
                break
            sequence.append(num)
        except ValueError:
            print("Invalid input! Please enter a valid integer.")
    return sequence


def count_numbers_above_12(sequence):
    """
    Function to count numbers greater than 12 in the sequence
    Args:
    sequence (list): Input sequence
    Returns:
    int: Count of numbers greater than 12
    """
    count = 0
    for num in sequence:
        if num > 12:
            count += 1
    return count

def calculate_sequence_sum(sequence):
    """
    Function to calculate the sum of the sequence
    Args:
    sequence (list): Input sequence
    Returns:
    int: Sum of the sequence
    """
    total_sum = sum(sequence)
    return total_sum

def main():
    """
    Main function to execute the program
    """
    while True:
        sequence = input_sequence()
        count = count_numbers_above_12(sequence)
        total_sum = calculate_sequence_sum(sequence)

        print(f"Number of elements greater than 12: {count}")
        print(f"Sum of the sequence: {total_sum}")

        choice = input("Do you want to continue (Y/N)? ").upper()
        if choice != 'Y':
            break
        if choice == 'N':
            break

if __name__ == "__main__":
    main()
