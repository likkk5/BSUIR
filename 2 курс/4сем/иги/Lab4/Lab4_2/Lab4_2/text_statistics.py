import re
from text_processor import TextProcessor

class TextStatistics(TextProcessor):
    """
    A class to perform statistical analysis on text data.
    
    Inherits from TextProcessor class.
    """

    def __init__(self, text):
        """
        Initializes a TextStatistics object.

        Parameters:
            text (str): The text for analysis.
        """
        super().__init__(text)

    def count_sentences(self):
        """
        Counts the number of sentences in the text.

        Returns:
            int: The number of sentences in the text.
        """
        text_without_smileys = re.sub(r'[:;]-*[\(\[\)\]]+','', self.text)
        sentences = re.split(r'[.!?...](?:\s+|\n+)[A-Z]', text_without_smileys)
        # for i, sentence in enumerate(sentences, 1):  # Ќачинаем считать с 1
        #   print(f"Sentence {i}: {sentence.strip()}")
        return len(sentences)

    def count_sentence_types(self):
        """
        Counts the number of narrative, interrogative, and imperative sentences in the text.

        Returns:
            tuple: A tuple containing the counts of narrative, interrogative, and imperative sentences.
        """
        narr_count = len(re.findall(r'[.!?]\s*[A-Z]', self.text))
        interrog_count = len(re.findall(r'\?\s*[A-Z]', self.text))
        imper_count = len(re.findall(r'!\s*[A-Z]', self.text))
        #\s* ноль или более пробельных символов
        return narr_count, interrog_count, imper_count

    def average_sentence_length(self):
        """
        Calculates the average length of sentences in the text.

        Returns:
            float: The average length of sentences in the text.
        """
        words = re.findall(r'\b\w+\b', self.text)
        total_chars = sum(len(word) for word in words)
        sentence_count = self.count_sentences()
        return total_chars / sentence_count if sentence_count > 0 else 0

    def average_word_length(self):
        """
        Calculates the average length of words in the text.

        Returns:
            float: The average length of words in the text.
        """
        words = re.findall(r'\b\w+\b', self.text)
        total_chars = sum(len(word) for word in words)
        word_count = len(words)
        return total_chars / word_count if word_count > 0 else 0

    def count_smileys(self):
        """
        Counts the number of smileys in the text.

        Returns:
            int: The number of smileys in the text.
        """
        smileys = self.find_smileys()
        return len(smileys)
    
    def count_words_start_end_vowels(self):
        """
        Counts the number of words that start and end with vowels in the text.

        Returns:
            tuple: A tuple containing the counts of words starting and ending with vowels.
        """
        start_vowel_words, end_vowel_words = self.find_words_start_end_vowels()
        start_vowel_count = len(start_vowel_words)
        end_vowel_count = len(end_vowel_words)
        return start_vowel_count, end_vowel_count

    def count_character_occurrences(self):
        """
        Counts the occurrences of each character in the text.

        Returns:
            dict: A dictionary containing characters as keys and their occurrences as values.
        """
        char_counts = {}
        for char in self.text:
            if char.isalpha(): #встроенный метод проверки, состоит ли данна€ строка только из букв алфавита.
                char = char.lower()
                char_counts[char] = char_counts.get(char, 0) + 1
        return char_counts
