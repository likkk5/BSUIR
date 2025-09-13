def count_uppercase_letters(text):
    """
    Function to count the number of uppercase letters in the text
    Args:
    text (str): Input text
    Returns:
    int: Number of uppercase letters
    """
    count = sum(1 for char in text if char.isupper()) #подсчитывает количество заглавных букв в строке text и возвращает это количество.
    return count

def find_first_word_with_z(text):
    """
    Function to find the first word containing the letter 'z' and its position
    Args:
    text (str): Input text
    Returns:
    tuple: First word containing 'z' and its position (word, position)
    """
    #ищет первое слово в строке text, содержащее символ 'z'(преобразует слово в нижний регистр ), и возвращает это слово
    #enumerate используется для перебора элементов последовательности (например, списка, кортежа, строки и т. д.) и возвращает кортежи, содержащие индекс элемента и сам элемент
    words = text.split()
    for i, word in enumerate(words, 1): #итерируясь с помощью enumerate. Каждое слово сохраняется в переменной word, а его индекс (с 1) сохраняется в переменной i
        if 'z' in word.lower():
            return word, i 
    return None, None

def exclude_words_starting_with_a(text):
    """
    Function to exclude words starting with 'a' from the text
    Args:
    text (str): Input text
    Returns:
    str: Text with words starting with 'a' excluded
    """
    words = text.split()
    filtered_words = [word for word in words if not word.lower().startswith('a')]
    return ' '.join(filtered_words)

