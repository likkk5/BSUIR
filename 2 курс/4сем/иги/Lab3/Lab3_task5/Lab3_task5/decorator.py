#функция которая принимает другую функцию в качестве аргумента, расширяет ее функциональность и возвращает измененную функцию.
def pow_result(func):
    """
    Decorator to pow the result of the function
    """
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        return result ** 2
        #return pow(result, 2)
    return wrapper
