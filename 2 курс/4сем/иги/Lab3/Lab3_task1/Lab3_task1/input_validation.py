def validate_float_input(prompt):
    """
    Function to validate float input
    Args:
    prompt (str): Prompt message for input
    Returns:
    float: Validated float value
    """
    while True:
        try:
            value = float(input(prompt))
            return value
        except ValueError:
            print("Invalid input! Please enter a valid number.")

