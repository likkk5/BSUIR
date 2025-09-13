import re

class TextProcessor:
    """
    A parent class to process text data.
    """
    def __init__(self, text):
        """
        Initialize the TextProcessor object with the given text.

        Parameters:
        text (str): The text to process.

        Returns:
        None
        """
        self.text = text

    def find_sentences(self):
        """
        Find sentences in the text.

        Returns:
        list: A list of sentences found in the text.
        """
        text_without_smileys = re.sub(r'[:;]-*[\(\[\)\]]+', '', self.text)
        #* 0>, + 1>, \экранирование для вопринятия как символа
        sentences = re.split(r'[.!?...]', text_without_smileys)
        return [sentence.strip() for sentence in sentences if sentence.strip()]

    def find_smileys(self):
        """
        Find smileys in the text.

        Returns:
        list: A list of smileys found in the text.
        """
        smileys = re.findall(r'[:;]-*[\(\[\)\]]+', self.text)
        return smileys

    def find_words_start_end_vowels(self):
        """
        Find words with vowels at the start and end in the text.

        Returns:
        tuple: A tuple containing lists of words with vowels at the start and end, respectively.
        """
        start_vowel_words = re.findall(r'\b[aeiouAEIOU]\w*\b', self.text)
        #начало и конец слова b, w* ищет отдельые слова(сначала гласные потом символы)
        end_vowel_words = re.findall(r'\b\w*[aeiouAEIOU]\b', self.text)
        return start_vowel_words, end_vowel_words
