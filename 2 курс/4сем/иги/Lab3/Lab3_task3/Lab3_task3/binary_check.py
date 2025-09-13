def is_binary_number(input_str):
    """
    Function to check if the input string is a binary number
    Args:
    input_str (str): Input string to be checked
    Returns:
    bool: True if the input string is a binary number, False otherwise
    """
    for char in input_str:
        if char != '0' and char != '1':
            return False
    return True

