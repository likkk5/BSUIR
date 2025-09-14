import re
from collections import Counter
from itertools import tee


def calculate_amount_of_sentences(text: str) -> int:
    regex = r'(\.|\?|!)+'
    return len([*re.finditer(regex, text)])


def calculate_amount_of_non_declarative_sentences(text: str) -> int:
    regex = r'\.+'
    return calculate_amount_of_sentences(text) - len([*re.finditer(regex, text)])


def mean(list_of_numbers: list[float]) -> float:
    if not list_of_numbers:
        return 0

    return sum(list_of_numbers) / len(list_of_numbers)


def calculate_length_of_each_word(text: str) -> list[int]:
    words = extract_words(text)
    return list(map(lambda word: len(word), words))


def extract_words(text: str) -> list[str]:
    regex = f'\w*[a-zA-Z]\w*'
    words = re.findall(regex, text)
    return words


def calculate_average_length_of_words(text: str) -> float:
    return mean(calculate_length_of_each_word(text))


def contains_words(text: str) -> bool:
    return bool(extract_words(text))


def calculate_average_length_of_sentences(text: str) -> float:
    regex = r'(\.|\?|!)+'
    sentences = filter(contains_words, re.split(regex, text))
    return mean(list(map(lambda word: sum(calculate_length_of_each_word(word)), sentences)))


def get_ngrams(words: list[str], n: int):
    iterables = tee(words, n)

    for i, sub_iterable in enumerate(iterables):
        for _ in range(i):
            next(sub_iterable, None)

    return zip(*iterables)


def get_k_repeated_ngrams(text: str, k: int = 10, n: int = 4) -> list[tuple[tuple, int]]:
    words = extract_words(text)
    ngrams = get_ngrams(words, n)
    k_repeated_ngrams = Counter(ngrams).most_common(k)
    return k_repeated_ngrams
