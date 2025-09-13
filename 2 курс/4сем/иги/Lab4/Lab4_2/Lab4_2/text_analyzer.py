import re
from text_processor import TextProcessor

class TextAnalyzer(TextProcessor):
    """
    A class to analyze text data for specific patterns.

    Inherits from TextProcessor class.
    """

    def __init__(self, text):
        """
        Initializes a TextAnalyzer object.

        Parameters:
            text (str): The text for analysis.
        """
        super().__init__(text)

    def find_binary_numbers(self):
        """
        Finds binary numbers in the text.

        Returns:
            list: A list containing binary numbers found in the text.
        """
        binary_numbers = re.findall(r'\b[01]+\b', self.text)
        #отделяет слова b
        return binary_numbers

    def find_vowel_consonant_words(self):
        """
        Finds words that start with a vowel, followed by a consonant, in the text.

        Returns:
            list: A list containing words that match the pattern.
        """
        words = re.findall(r'\b([aeiou][^aeiou\s][a-z]*)\b', self.text, flags=re.IGNORECASE)
        #^ все кроме того что написаноб \s пробел 
        return words

    def find_words_after_comma(self):
        """
        Finds words that appear after a comma in the text, sorted alphabetically.

        Returns:
            list: A list containing words found after commas, sorted alphabetically.
        """
        words = re.findall(r'(?<=,\s)([a-zA-Z]+)', self.text)
        #(?<=,\s): "позитивное lookbehind" и используется для поиска слов, которые следуют за запятой и пробелом, но сама запятая и пробел не включаются в результат.
        return sorted(words)
