import math
from collections import defaultdict


def calculate_mean(data):
    """Вычисляет среднее арифметическое."""
    return sum(data) / len(data)


def calculate_median(data):
    """Вычисляет медиану."""
    sorted_data = sorted(data)
    n = len(sorted_data)
    if n % 2 == 1:
        return sorted_data[n // 2]
    else:
        return (sorted_data[n // 2 - 1] + sorted_data[n // 2]) / 2


def calculate_variance(data, mean_value):
    """Вычисляет несмещенную дисперсию."""
    n = len(data)
    return sum((x - mean_value) ** 2 for x in data) / (n - 1)


def calculate_std_dev(variance):
    return math.sqrt(variance)


def calculate_coefficient_of_variation(variance_value, mean_value):
    """Вычисляет коэффициент вариации (в %)."""
    return (variance_value ** 0.5 / mean_value) * 100


def calculate_mode(data):
    """Вычисляет моду (самое часто встречающееся значение)."""
    freq_dict = {}
    for num in data:
        freq_dict[num] = freq_dict.get(num, 0) + 1
    max_frequency = max(freq_dict.values())
    return [k for k, v in freq_dict.items() if v == max_frequency]


def calculate_mean_variance_std(data, s):
    min_value, max_value = min(data), max(data)
    interval_width = (max_value - min_value) / s
    intervals = [(min_value + i * interval_width, min_value + (i + 1) * interval_width) for i in range(s)]

    # Группируем данные по интервалам
    groups = defaultdict(int)
    for value in data:
        for i, (start, end) in enumerate(intervals):
            if start <= value < end:
                groups[i] += 1
                break
        else:
            # Если значение равно максимальному, добавляем его в последний интервал
            if value == max_value:
                groups[s - 1] += 1

    # Вычисляем середины интервалов и количество элементов в каждом интервале
    midpoints = [(start + end) / 2 for start, end in intervals]
    counts = [groups[i] for i in range(s)]

    # Общее количество элементов
    n = len(data)

    # Вычисляем среднее
    mean = sum(midpoints[i] * counts[i] for i in range(s)) / n

    # Вычисляем дисперсию
    variance = sum(counts[i] * (midpoints[i] - mean) ** 2 for i in range(s)) / n

    # Вычисляем стандартное отклонение
    std_deviation = variance ** 0.5

    return mean, variance, std_deviation