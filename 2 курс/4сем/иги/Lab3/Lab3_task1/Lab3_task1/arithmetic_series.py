def arcsin_series(x, eps=1e-6, max_iterations=500):
    """
    Function to calculate arcsin(x) using series expansion
    Args:
    x (float): Argument value
    eps (float): Desired precision
    max_iterations (int): Maximum number of iterations
    Returns:
    float: Calculated value of arcsin(x)
    int: Number of terms needed for the specified precision
    """
    result = 0.0
    iteration = 0
    term = x
    while abs(term) > eps and iteration < max_iterations:
        result += term
        iteration += 1
        term *= (-1) * x**2 * (2 * iteration - 1) / (2 * iteration)
        term /= iteration
    return result, iteration

