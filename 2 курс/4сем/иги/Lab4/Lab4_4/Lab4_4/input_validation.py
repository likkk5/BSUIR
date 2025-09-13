def validate_input(value):
    """Validate user input."""
    try:
        value = float(value)
        if value <= 0:
            raise ValueError("Value must be greater than 0")
        return value
    except ValueError:
        print("Invalid input. Please enter a valid numeric value.")
        return None

def validate_color(color):
    """Validate user input for color."""
    valid_colors = ['red', 'green', 'blue', 'yellow', 'orange', 'purple', 'pink', 'brown', 'black', 'white']
    if color.lower() in valid_colors:
        return color.lower()
    else:
        print("Invalid color. Please enter one of the following colors: ", valid_colors)
        return None
