from typing import List


def extract_even(list_of_numbers: List[int]) -> List[int]:
    return list(filter(lambda x: x % 2 == 0, list_of_numbers))

