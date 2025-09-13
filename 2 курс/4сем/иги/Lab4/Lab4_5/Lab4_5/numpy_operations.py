import numpy as np

class ArrayOperations:
    def create_array(self, data):
        """
        Create an array using the array() function.
        """
        return np.array(data)

    def create_array_like(self, arr):
        """
        Create an array similar to another array 'arr' using the np.array_like() function.
        """
        return np.array_like(arr)

    def create_zeros(self, shape):
        """
        Create an array of zeros with the specified shape using the np.zeros() function.
        """
        return np.zeros(shape)

    def create_ones(self, shape):
        """
        Create an array of ones with the specified shape using the np.ones() function.
        """
        return np.ones(shape)

    def create_random_matrix(self, shape, low=0, high=10):
        """
        Create an integer matrix A[n, m] using the random number generator (random) with the given shape.
        """
        return np.random.randint(low, high, shape)

    def array_indexing(self, arr, index):
        """
        Index the array 'arr' at the specified index.
        """
        return arr[index]

    def array_slicing(self, arr, start=None, end=None, step=None):
        """
        Slice the array 'arr' with the specified start, end, and step.
        """
        return arr[start:end:step]

    def array_operations(self, arr1, arr2):
        """
        Operations on arrays arr1 and arr2.
        """
        # Example of a universal (element-wise) function - addition
        return np.add(arr1, arr2)
    
    def user_input_operations(self):
        """
        Perform array operations based on user input.
        """

        while True:  # Loop until valid input is provided
            try:
                # Get the dimensions of the array from the user
                n = int(input("Enter the number of rows in the matrix: "))
                m = int(input("Enter the number of columns in the matrix: "))
                break  # Exit the loop if input is successful
            except ValueError:
                print("Invalid input. Please enter integers for dimensions.")

        # Create a random integer matrix
        random_matrix = self.create_random_matrix((n, m))
        print("\nRandom matrix:")
        print(random_matrix)

        while True:  # Loop until valid input is provided
            try:
                # Index the array
                row_index = int(input("\nEnter the row index: "))
                col_index = int(input("Enter the column index: "))
                print("\nElement at the specified index:", self.array_indexing(random_matrix, (row_index, col_index)))
                break  # Exit the loop if input is successful
            except (ValueError, IndexError):
                print("Invalid index. Please enter valid row and column indices.")

        while True:  # Loop until valid input is provided
            try:
                # Slice the array
                start = int(input("\nEnter the start index of the slice: "))
                end = int(input("Enter the end index of the slice: "))
                print("\nArray slice:")
                print(self.array_slicing(random_matrix, start, end))
                break  # Exit the loop if input is successful
            except (ValueError, IndexError):
                print("Invalid slice indices. Please enter valid start and end indices.")

        while True:  # Loop until valid input is provided
            try:
                # Get the dimensions of the second array from the user
                n2 = int(input("\nEnter the number of rows in the second matrix: "))
                m2 = int(input("Enter the number of columns in the second matrix: "))

                # Create a second random integer matrix
                random_matrix2 = self.create_random_matrix((n2, m2))
                print("\nSecond random matrix:")
                print(random_matrix2)

                # Perform addition of the two arrays
                print("\nSum of arrays:")
                print(self.array_operations(random_matrix, random_matrix2))
                break  # Exit the loop if input is successful
            except ValueError:
                print("Invalid input. Please enter integers for dimensions.")

