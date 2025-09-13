# Program: Task 5
# Lab Number: 3
# Program Version: 1.3
# Developer: Lishyk Ksenia
# Date: 29.03.2024
import sequence_input as inp
import sequence_processing as proc
from display import display_list
import decorator as dec

def main():
    """
    Main function to execute the program
    """
    while True:

        print("Choose how do you want to input numbers' sequence:\n"         
          "G. Generated automatically.\n"
          "U. User input.\n")
    
        while True:
            print("Enter G or U:")
            choice=inp.input_abc()
            if choice!='U' and choice!='G':
                print("Incorrect input!Try again.")
            else:
                break
        
        lst=[]
        if choice=='U':
            lst=inp.user_input_sequence()
        elif choice=='G':
         while True:
          try:
              length = int(input("Enter the length of the sequence: "))
              if length <= 0:
                    raise ValueError("Length of the sequence should be positive.")
              break
          except ValueError as e:
            print(e)
         random_sequence = inp.generate_sequence(length)
         lst = list(random_sequence)
         print("List has been generated:")
    
        display_list(lst)
    
        product = proc.product_of_positive_numbers(lst)
        product_pow = dec.pow_result(proc.product_of_positive_numbers)(lst)
        print(f"Product of positive numbers: {product}, Pow2: {product_pow}")

        sum_before_min_abs = proc.sum_of_elements_before_min_abs(lst)
        sum_before_min_abs_pow = dec.pow_result(proc.sum_of_elements_before_min_abs)(lst)
        print(f"Sum of elements before the minimum absolute element: {sum_before_min_abs}, Pow2: {sum_before_min_abs_pow}")
        
        choice = input("\nDo you want to calculate again (Y/N)? ").upper()
        if choice != 'Y':
            break
        if choice == 'N':
            break
if __name__ == "__main__":
    main()
