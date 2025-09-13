def input_string():
    """
    Function to take user input string
    Returns:
    str: User input string
    """
    while True:
        input_str = input("Enter a string to check if it's a binary number: ")
        if input_str.isdigit():
            return input_str
        else:
            print("Invalid input! Please enter only digits.")

