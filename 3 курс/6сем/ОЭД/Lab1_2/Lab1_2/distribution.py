import math

import numpy as np
from scipy.stats import norm

from characteristics import *


def chi2_critical(df, alpha=0.05):
    """Приближенно находит критическое значение χ² по числу степеней свободы."""
    return norm.ppf(1 - alpha, df, np.sqrt(2 * df))  # Аппроксимация критического значения


def chi_square_test(height_data, s):
    """Реализует критерий хи-квадрат Пирсона для проверки нормального распределения."""

    # 1. Определяем границы интервалов
    min_value, max_value = min(height_data), max(height_data)
    interval_width = (max_value - min_value) / s
    intervals = [min_value + i * interval_width for i in range(s + 1)]

    # 2. Считаем наблюдаемые частоты (гистограмма)
    observed_frequencies = [0] * s
    for value in height_data:
        for i in range(s):
            if i == s - 1:  # Последний интервал
                if intervals[i] <= value <= intervals[i + 1]:
                    observed_frequencies[i] += 1
                    break
            else:  # Остальные интервалы
                if intervals[i] <= value < intervals[i + 1]:
                    observed_frequencies[i] += 1
                    break

    # 3. Вычисляем теоретические частоты (из нормального распределения)
    mean_value = np.mean(height_data)
    std_dev = np.std(height_data)
    expected_frequencies = []

    for i in range(s):
        p_i = norm.cdf(intervals[i + 1], mean_value, std_dev) - norm.cdf(intervals[i], mean_value, std_dev)
        expected_frequencies.append(p_i * len(height_data))

    # 4. Вычисляем статистику χ²
    chi_square_stat = sum((observed_frequencies[i] - expected_frequencies[i]) ** 2 / expected_frequencies[i]
                          for i in range(s) if expected_frequencies[i] != 0)

    # 5. Степени свободы (df = число интервалов - 1 - число оцениваемых параметров)
    df = s - 1 - 2  # Вычитаем 2 параметра: среднее и стандартное отклонение
    critical_value = chi2_critical(df)

    # 6. Вывод результатов
    print("\nХи-квадрат Пирсона:")
    print(f"   - χ²-статистика = {chi_square_stat:.4f}")
    print(f"   - Критическое значение (α=0.05) = {critical_value:.4f}")
    print(
        f"   - Вывод: {'Соответствует нормальному распределению' if chi_square_stat < critical_value else 'НЕ соответствует'}")

    return chi_square_stat, critical_value


def normal_cdf(x, mu, sigma):
    """ Функция нормального распределения (CDF) """
    return (1 + math.erf((x - mu) / (sigma * math.sqrt(2)))) / 2


def kolmogorov_smirnov_test(data, alpha=0.05):
    """
    Критерий Колмогорова-Смирнова для проверки нормальности выборки
    """
    mean = calculate_mean(data)
    variance = calculate_variance(data, mean)
    std_dev = calculate_std_dev(variance)

    n = len(data)
    mu = mean
    sigma = std_dev

    # Сортируем данные
    data_sorted = sorted(data)

    # Вычисляем ECDF
    ecdf = [i / n for i in range(1, n + 1)]

    # Вычисляем CDF для нормального распределения
    cdf = [normal_cdf(x, mu, sigma) for x in data_sorted]

    # Вычисляем статистику Колмогорова-Смирнова
    ks_stat = max(abs(ecdf[i] - cdf[i]) for i in range(n))

    # Критическое значение для alpha=0.05
    critical_value = 1.36 / math.sqrt(n)

    print("\nКритерий Колмогорова-Смирнова")
    print("=" * 50)
    print(f"Размер выборки: {n}")
    print(f"Среднее: {mu:.2f}")
    print(f"Стандартное отклонение: {sigma:.2f}")
    print("-" * 50)
    print(f"D-статистика: {ks_stat:.5f}")
    print(f"Критическое значение (α={alpha}): {critical_value:.5f}")
    print("=" * 50)

    # Проверка гипотезы
    if ks_stat > critical_value:
        print("Распределение не является нормальным")
    else:
        print("Распределение можно считать нормальным")

    return ks_stat, critical_value