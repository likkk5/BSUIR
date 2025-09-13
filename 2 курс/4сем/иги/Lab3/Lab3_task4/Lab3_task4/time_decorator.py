import time

def measure_time(func):
    """
    Decorator for measuring function execution time
    Args:
    func (function): The function to be measured
    Returns:
    function: Wrapped function
    """
    def wrapper(*args, **kwargs):
        """
        Wrapper function to measure execution time of a function
        Args:
        *args: Positional arguments passed to the wrapped function
        **kwargs: Keyword arguments passed to the wrapped function
        Returns:
        Any: Result of the wrapped function
        """
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print(f"Execution time: {end_time - start_time} seconds")
        return result
    return wrapper

