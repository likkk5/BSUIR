# Program: Task 1
# Lab Number: 3
# Program Version: 1.2
# Developer: Lishyk Ksenia
# Date: 27.03.2024

import math
from input_validation import validate_float_input
from arithmetic_series import arcsin_series

def main():
    """
    Main function to execute the program
    """
    while True:
        x = validate_float_input("Enter the value of x (-1 < x < 1): ")
        if abs(x) >= 1:
            print("Error: |x| must be less than 1.")
            continue

        eps = validate_float_input("Enter the desired precision (eps): ")
        if eps <= 0:
            print("Error: Precision (eps) must be positive.")
            continue

        print("\nResult:")
        print("x\t F(x)\t\t n\t Math F(x)")
        print("-" * 40)
        calculated_value, terms = arcsin_series(x, eps)
        math_value = math.asin(x)
        print(f"{x:.4f}\t {calculated_value:.6f}\t {terms}\t {math_value:.6f}")

        choice = input("\nDo you want to calculate again (Y/N)? ").upper()
        if choice != 'Y':
            break
        if choice == 'N':
            break

if __name__ == "__main__":
    main()
