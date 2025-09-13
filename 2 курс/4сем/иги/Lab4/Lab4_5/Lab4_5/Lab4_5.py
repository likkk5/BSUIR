from numpy_operations import ArrayOperations
from CustomArrayOperations import CustomArrayOperations
from math_stats_operations import MathStatsOperations

def main():
    while True:
        print("\n1. Perform Array Operations")
        print("2. Perform Math and Stats Operations")
        print("3. Exit")
        print("4. Individual: Insert the first line after the line containing the first minimum element encountered. Calculate the median value of the first row")

        choice = input("Enter your choice: ")

        if choice == '1':
            while True:
                try:
                    array_ops = ArrayOperations()
                    array_ops.user_input_operations()
                    break  # Exit the loop if user input is successful
                except Exception as e:
                    print(f"An error occurred: {e}")

        elif choice == '2':
            while True:
                try:
                    # Prompt the user to enter space-separated numbers
                    data_input = input("Enter space-separated numbers: ").strip()

                    # Convert the input string into a list of integers
                    data = [int(x) for x in data_input.split()]

                    # Check if the list is not empty
                    if not data:
                        print("Invalid input. Please enter at least one number.")
                    else:
                        # Perform math and stats operations
                        math_stats_ops = MathStatsOperations()
                        mean = math_stats_ops.calculate_mean(data)
                        median = math_stats_ops.calculate_median(data)
                        print("Mean:", mean)
                        print("Median:", median)
                        break  # Exit the loop if input is valid
                except ValueError:
                    print("Invalid input. Please enter space-separated integers.")

        elif choice == '3':
            print("Exiting...")
            break

        elif choice == '4':
            while True:
                try:
                    custom_ops = CustomArrayOperations()
                    custom_ops.insert_first_row_after_min_element_and_calculate_median()
                    break  # Exit the loop if user input is successful
                except Exception as e:
                    print(f"An error occurred: {e}")

        else:
            print("Invalid choice. Please enter a valid option.")

if __name__ == "__main__":
    main()
