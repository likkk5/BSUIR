from numpy_operations import ArrayOperations
import numpy as np
class CustomArrayOperations(ArrayOperations):
   def calculate_median_standard(self, row):
        """Calculate the median of a row using the standard function."""
        return np.median(row)

   def calculate_median_formula(self, row):
        """Calculate the median of a row using a custom formula."""
        sorted_row = sorted(row)
        n = len(sorted_row)
        if n % 2 == 0:
            median = (sorted_row[n//2 - 1] + sorted_row[n//2]) / 2 #целочисленное деление
        else:
            median = sorted_row[n//2]
        return median

   def insert_first_row_after_min_element_and_calculate_median(self):
    while True:
        try:
            # Insert first row after the row with the first encountered minimum element
            print("Enter matrix elements row by row (separate elements by spaces):")
            rows = int(input("Enter number of rows: "))
            cols = int(input("Enter number of columns: "))
            if rows <= 0 or cols <= 0:
                raise ValueError("Number of rows and columns must be positive integers.")
            
            data = []
            for i in range(rows):
                row = [int(x) for x in input(f"Enter elements for row {i+1}: ").split()]
                if len(row) != cols:
                    raise ValueError(f"Number of elements in row {i+1} does not match the number of columns.")
                data.append(row) #добавить в существующий список

            matrix = self.create_array(data)
            print("Original Matrix:")
            print(matrix)

            min_element_row = None
            min_element_index = None
            for i, row in enumerate(matrix):
                min_index = np.argmin(row)
                if min_element_row is None or row[min_index] < min_element_row[min_element_index]:
                    min_element_row = row
                    min_element_index = min_index
            
            new_matrix = np.insert(matrix, min_element_index + 1, matrix[0], axis=0)
            print("\nMatrix after inserting first row after the row with the first encountered minimum element:")
            print(new_matrix)
            break
        except ValueError as e:
            print("Error:", e)
            
            print("Please enter valid input.") 
    # Calculate the median of the first row using standard function
    first_row = new_matrix[0]
    median_standard = self.calculate_median_standard(first_row)
    print("\nMedian of the first row (Standard Function):", median_standard)

    # Calculate the median of the first row using custom formula
    median_formula = self.calculate_median_formula(first_row)
    print("Median of the first row (Custom Formula):", median_formula)

