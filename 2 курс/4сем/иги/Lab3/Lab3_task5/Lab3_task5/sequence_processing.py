def product_of_positive_numbers(lst):
    """
    Function to calculate the product of positive elements in the list
    Args:
    lst (list): List of real numbers
    Returns:
    float: Product of positive elements
    """
    product = 1
    for num in lst:
        if num > 0:
            product *= num
    return product

def sum_of_elements_before_min_abs(lst):
    """
    Function to calculate the sum of elements before the minimum absolute element in the list
    Args:
    lst (list): List of real numbers
    Returns:
    float: Sum of elements before the minimum absolute element
    """
    min_abs_index = lst.index(min(lst, key=abs)) #находит индекс элемента в списке lst, который имеет минимальное по модулю значение
    sum_before_min_abs = sum(lst[:min_abs_index]) #вычисляет сумму всех элементов списка lst, расположенных до элемента с минимальным по модулю значением. 
    return sum_before_min_abs

