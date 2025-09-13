from collections import defaultdict

from matplotlib import pyplot as plt

from characteristics import calculate_mean, calculate_variance

import numpy as np

import scipy.stats as stats


def evaluate_homogeneity(coefficient_of_variation):
    """Оценивает однородность выборки по коэффициенту вариации."""
    if coefficient_of_variation < 33:
        return "Выборка однородна"
    else:
        return "Выборка неоднородна"


def remove_outliers(data):
    sorted_data = sorted(data)
    n = len(sorted_data)

    Q1 = sorted_data[n // 4]  # Первый квартиль (25-й процентиль)
    Q3 = sorted_data[(3 * n) // 4]  # Третий квартиль (75-й процентиль)
    IQR = Q3 - Q1  # Межквартильный размах

    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR

    return [x for x in data if lower_bound <= x <= upper_bound]


# Функция для расчета дисперсий при разбиении на s интервалов
def compute_variances(filtered_height, s):
    min_value, max_value = min(filtered_height), max(filtered_height)
    interval_width = (max_value - min_value) / s
    intervals = [min_value + i * interval_width for i in range(s + 1)]

    # Группируем рост по интервалам
    groups = defaultdict(list)
    for j in range(len(filtered_height)):
        for i in range(s):
            if i == s - 1:  # Проверяем, если это последний интервал
                if intervals[i] <= filtered_height[j] <= intervals[i + 1]:
                    groups[i].append(filtered_height[j])
            elif intervals[i] <= filtered_height[j] < intervals[i + 1]:  # Для остальных интервалов
                groups[i].append(filtered_height[j])
                break

    # Вычисляем дисперсии для каждой группы
    group_variances = []
    within_group_variance_sum = 0
    total_n = len(filtered_height)

    for group in groups.values():
        if len(group) > 1:
            group_mean = calculate_mean(group)
            group_variance = calculate_variance(group, group_mean)
            group_variances.append(group_variance)
            within_group_variance_sum += (len(group) - 1) * group_variance
        else:
            group_variances.append(0)  # Если в группе 1 элемент, дисперсия = 0

    # Внутригрупповая дисперсия (взвешенная сумма групповых дисперсий)
    within_group_variance = within_group_variance_sum / (total_n - 1)

    # Межгрупповая дисперсия
    overall_mean = calculate_mean(filtered_height)
    overall_variance = calculate_variance(filtered_height, overall_mean)
    between_group_variance_sum = sum(
        len(groups[i]) * (calculate_mean(groups[i]) - overall_mean) ** 2
        for i in groups
    )
    between_group_variance = between_group_variance_sum / (total_n - 1)

    # Общая дисперсия
    total_variance = within_group_variance + between_group_variance

    between_ratio = between_group_variance / total_variance

    check = abs(overall_variance - total_variance) < 0.01 * overall_variance

    return group_variances, within_group_variance, between_group_variance, total_variance, between_ratio, check


def plot_statistics(data, true_mean, true_variance, step=10):
    """
    Функция для построения графика изменения среднего и дисперсии в зависимости от объёма выборки.

    :param data: Исходные данные (список значений).
    :param true_mean: Истинное значение среднего.
    :param true_variance: Истинное значение дисперсии.
    :param step: Шаг увеличения объёма выборки.
    """
    # Списки для хранения данных для графика
    sample_sizes = []  # Объёмы выборки
    mean_values = []  # Средние значения
    variance_values = []  # Дисперсии

    max_size = len(data)  # Максимальный объём выборки
    current_size = step  # Начинаем с объёма выборки, равного шагу

    while current_size <= max_size:
        subset = data[:current_size]  # Берём подмножество данных
        mean_value = calculate_mean(subset)  # Рассчитываем среднее
        variance_value = calculate_variance(subset, mean_value)  # Рассчитываем дисперсию

        # Сохраняем данные для графика
        sample_sizes.append(current_size)
        mean_values.append(mean_value)
        variance_values.append(variance_value)

        current_size += step  # Увеличиваем объём выборки на шаг

    # Построение графика
    plt.figure(figsize=(12, 6))

    # График для вычисленных средних значений
    plt.plot(sample_sizes, mean_values, label="Вычисленное среднее", color="blue", marker="o", linestyle="-")

    # График для истинного среднего значения
    plt.axhline(y=true_mean, color="green", linestyle="--", label="Истинное среднее")

    # График для вычисленных дисперсий
    plt.plot(sample_sizes, variance_values, label="Вычисленная дисперсия", color="red", marker="s", linestyle="-")

    # График для истинной дисперсии
    plt.axhline(y=true_variance, color="purple", linestyle="--", label="Истинная дисперсия")

    # Настройка графика
    plt.title("Изменение среднего значения и дисперсии в зависимости от объёма выборки")
    plt.xlabel("Объём выборки")
    plt.ylabel("Значение")
    plt.grid(True)
    plt.legend()
    plt.show()



def prove_unbiasedness(true_mean, true_variance, sample_sizes):
    mean_errors = []
    var_errors = []
    
    for n in sample_sizes:
        sample = np.random.normal(true_mean, np.sqrt(true_variance), n)  # Выборка из нормального распределения
        mean_estimate = np.mean(sample)
        var_estimate = calculate_unbiased_variance(sample, unbiased=True)
        
        mean_errors.append(abs(mean_estimate - true_mean))  # Ошибка оценки среднего
        var_errors.append(abs(var_estimate - true_variance))  # Ошибка оценки дисперсии
    
    return sample_sizes, mean_errors, var_errors

def calculate_unbiased_variance(data, unbiased=True):
    return np.var(data, ddof=1 if unbiased else 0)  # ddof=1 делает оценку несмещённой



def student_t_test(sample1, sample2):
    """
    Выполняет t-тест для сравнения средних двух выборок.
    
    :param sample1: Первая выборка данных (например, полная выборка).
    :param sample2: Вторая выборка данных (например, подвыборка).
    :return: t-статистика и p-значение.
    """
    t_stat, p_value = stats.ttest_ind(sample1, sample2)
    
    if p_value < 0.05:
        result = "Выборки имеют статистически значимые различия (отвергаем нулевую гипотезу о равенстве средних)."
    else:
        result = "Нет статистически значимых различий между выборками (не отвергаем нулевую гипотезу)."
    
    return t_stat, p_value, result


def confidence_interval(sample, confidence=0.95):
    """
    Строит доверительный интервал для среднего значения выборки.
    
    :param sample: Входная выборка (например, подвыборка или полная выборка).
    :param confidence: Уровень доверия (по умолчанию 95%).
    :return: Нижняя и верхняя границы доверительного интервала.
    """
    # Среднее значение выборки
    mean = np.mean(sample)
    
    # Стандартная ошибка среднего
    sem = stats.sem(sample)
    
    # Критическое значение для t-распределения
    t_critical = stats.t.ppf((1 + confidence) / 2, df=len(sample) - 1)
    
    # Доверительный интервал
    margin_of_error = t_critical * sem
    lower_bound = mean - margin_of_error
    upper_bound = mean + margin_of_error
    
    return lower_bound, upper_bound