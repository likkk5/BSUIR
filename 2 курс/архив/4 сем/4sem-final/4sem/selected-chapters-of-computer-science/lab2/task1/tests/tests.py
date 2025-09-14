import unittest

from ..src.helpers import (
    calculate_amount_of_sentences,
    calculate_amount_of_non_declarative_sentences,
    calculate_average_length_of_words,
    calculate_average_length_of_sentences
)


class TestCalculateAmountOfSentences(unittest.TestCase):
    def test_1(self):
        self.assertEqual(calculate_amount_of_sentences('Hello, world!'), 1)

    def test_2(self):
        self.assertEqual(calculate_amount_of_sentences('Sentence. Another sentence...'), 2)

    def test_3(self):
        self.assertEqual(calculate_amount_of_sentences(''), 0)

    def test_4(self):
        self.assertEqual(calculate_amount_of_sentences('Is this a sentence?'), 1)


class TestCalculateAmountOfNonDeclarativeSentences(unittest.TestCase):
    def test_1(self):
        self.assertEqual(calculate_amount_of_non_declarative_sentences('Hello, world!'), 1)

    def test_2(self):
        self.assertEqual(calculate_amount_of_non_declarative_sentences('Sentence. Another sentence...'), 0)

    def test_3(self):
        self.assertEqual(calculate_amount_of_non_declarative_sentences('Is this a declarative sentence?'), 1)


class TestCalculateAverageLengthOfWords(unittest.TestCase):
    def test_1(self):
        self.assertEqual(calculate_average_length_of_words('Word word 1'), 4)  # 1 is not a word

    def test_2(self):
        self.assertEqual(calculate_average_length_of_words('W'), 1)

    def test_3(self):
        self.assertEqual(calculate_average_length_of_words(''), 0)

    def test_4(self):
        self.assertAlmostEqual(calculate_average_length_of_words('Some words'), 4.5)


class TestCalculateAverageLengthOfSentences(unittest.TestCase):
    def test_1(self):
        self.assertEqual(calculate_average_length_of_sentences('Word word 1'), 8)  # 1 is not a word

    def test_2(self):
        self.assertEqual(calculate_average_length_of_sentences('W'), 1)

    def test_3(self):
        self.assertEqual(calculate_average_length_of_sentences(''), 0)

    def test_4(self):
        self.assertAlmostEqual(calculate_average_length_of_sentences('Word word. Hey!'), 5.5)


if __name__ == "__main__":
    unittest.main()
