# coding: windows-1251

import csv
import numpy as np
from scipy import stats
from tabulate import tabulate
import matplotlib.pyplot as plt
import pandas as pd

# Функция для чтения данных из CSV-файла
def read_csv(file_path):
    df = pd.read_csv(file_path, encoding='ISO-8859-1')
    df["Population (2020)"] = pd.to_numeric(df["Population (2020)"], errors="coerce")
    
    df = df.dropna(subset=["Population (2020)"])  # Убираем строки с NaN
    data = df["Population (2020)"].astype(int).tolist()
    
    return data

# Функция для записи данных в CSV файл
def save_to_csv(file_path, data):
    df = pd.DataFrame(data, columns=["Population (2020)"])
    df.to_csv(file_path, index=False, encoding="utf-8")


# Function to calculate the mode
def calculate_mode(data):
    men = [item[0] for item in data]
    women = [item[1] for item in data]
    # mode_men = stats.mode(men)[0]
    # mode_women = stats.mode(women)[0]
    mode_men = stats.mode(men, keepdims=True).mode[0]
    mode_women = stats.mode(women, keepdims=True).mode[0]
    return mode_men, mode_women

# Function to calculate the median
def calculate_median(data):
    men = [item[0] for item in data]
    women = [item[1] for item in data]
    median_men = np.median(men)
    median_women = np.median(women)
    return median_men, median_women

# Function to calculate the mean
def calculate_mean(data):
    men = [item[0] for item in data]
    women = [item[1] for item in data]
    mean_men = np.mean(men)
    mean_women = np.mean(women)
    return mean_men, mean_women

# Function to calculate variance
def calculate_variance(data):
    men = [item[0] for item in data]
    women = [item[1] for item in data]
    variance_men = np.var(men)
    variance_women = np.var(women)
    return variance_men, variance_women

# Function to calculate the coefficient of variation
def calculate_cv(data):
    men = [item[0] for item in data]
    women = [item[1] for item in data]
    mean_men = np.mean(men)
    mean_women = np.mean(women)
    std_men = np.std(men)
    std_women = np.std(women)
    
    cv_men = (std_men / mean_men) * 100
    cv_women = (std_women / mean_women) * 100
    return cv_men, cv_women


def assess_homogeneity(cv_men, cv_women):
    if cv_men < 10:
        homogeneity_men = "Homogeneous"
    elif 10 <= cv_men < 20:
        homogeneity_men = "Moderately homogeneous"
    else:
        homogeneity_men = "Heterogeneous"

    if cv_women < 10:
        homogeneity_women = "Homogeneous"
    elif 10 <= cv_women < 20:
        homogeneity_women = "Moderately homogeneous"
    else:
        homogeneity_women = "Heterogeneous"

    return homogeneity_men, homogeneity_women


def remove_outliers(data, country_names):
    # Получаем данные для мужчин и женщин
    men = [item[0] for item in data]
    women = [item[1] for item in data]

    # Вычисляем медиану
    median_men = np.median(men)
    median_women = np.median(women)

    # Вычисляем межквартильный размах (IQR) для мужчин и женщин
    Q1_men = np.percentile(men, 25)
    Q3_men = np.percentile(men, 75)
    IQR_men = Q3_men - Q1_men

    Q1_women = np.percentile(women, 25)
    Q3_women = np.percentile(women, 75)
    IQR_women = Q3_women - Q1_women

    # Устанавливаем пороги для выбросов
    lower_bound_men = median_men - 1.5 * IQR_men
    upper_bound_men = median_men + 1.5 * IQR_men

    lower_bound_women = median_women - 1.5 * IQR_women
    upper_bound_women = median_women + 1.5 * IQR_women

    # Убираем выбросы
    filtered_data = [
        (country, men_count, women_count) 
        for country, men_count, women_count in zip(country_names, men, women)
        if lower_bound_men <= men_count <= upper_bound_men and lower_bound_women <= women_count <= upper_bound_women
    ]

    return filtered_data


def split_data_into_intervals(data):
    n = len(data)
    
    # Вычисляем количество интервалов по формуле s = 1 + floor(log2(n))
    s = 1 + int(np.log2(n)) 
    
    # Разбиваем данные на интервалы
    intervals, bin_edges = np.histogram(data, bins=s)
    
    return intervals, bin_edges


def plot_histogram_and_polygon(data, bins, label):

    # Строим гистограмму
    plt.hist(data, bins=bins, edgecolor='black', alpha=0.6, label=f'Histogram ({label})')
    
    # Строим полигон
    counts, bin_edges = np.histogram(data, bins=bins)
    mid_points = (bin_edges[:-1] + bin_edges[1:]) / 2  # Находим середины интервалов
    plt.plot(mid_points, counts, marker='o', color='r', label=f'Polygon ({label})')
    
    # Добавляем подписи
    plt.title(f'Histogram and Polygon for {label}')
    plt.xlabel('Data Range')
    plt.ylabel('Frequency')
    plt.legend(loc='best')
    plt.grid(True)
    plt.show()
    

def calculate_variances(file_path):
    df = pd.read_csv(file_path, sep=",")
    
    # Среднее количество мужчин и женщин по всем странам
    mean_men = df["Number of Men"].mean()
    mean_women = df["Number of Women"].mean()
    
    # Внутригрупповая дисперсия для мужчин и женщин
    men_variance = np.var(df["Number of Men"], ddof=1)
    women_variance = np.var(df["Number of Women"], ddof=1)
    
    # Расчет общей дисперсии для всего набора данных
    total_variance = np.var(pd.concat([df["Number of Men"], df["Number of Women"]]), ddof=1)

    # Межгрупповая дисперсия (расчет через различие между средними значениями групп и общим средним)
    total_mean = np.mean(pd.concat([df["Number of Men"], df["Number of Women"]]))
    
    men_between_group_variance = len(df) * (mean_men - total_mean) ** 2
    women_between_group_variance = len(df) * (mean_women - total_mean) ** 2
    
    # Проверка сложения дисперсий
    sum_variances = men_variance + women_variance + men_between_group_variance + women_between_group_variance
    rule_check = np.isclose(total_variance, sum_variances)

    result = [
            ["Men Variance", round(men_variance, 2)],
            ["Women Variance", round(women_variance, 2)],
            ["Men Between Group Variance", round(men_between_group_variance, 2)],
            ["Women Between Group Variance", round(women_between_group_variance, 2)],
            ["Rule Check (True/False)", rule_check]
    ]

    # Печать таблицы с результатами
    print("\nVariance Calculation Results:")
    print(tabulate(result, headers=["Metric", "Value"], tablefmt="pretty"))


def split_data_into_two_intervals(data, s):
    # Разбиваем данные на s-1 и s+1 интервалов
    intervals_s_minus_1, bin_edges_s_minus_1 = np.histogram(data, bins=s-1)
    intervals_s_plus_1, bin_edges_s_plus_1 = np.histogram(data, bins=s+1)
    
    # Получаем сами значения в интервалах
    mid_points_s_minus_1 = (bin_edges_s_minus_1[:-1] + bin_edges_s_minus_1[1:]) / 2
    mid_points_s_plus_1 = (bin_edges_s_plus_1[:-1] + bin_edges_s_plus_1[1:]) / 2
    
    # Вычисляем внутригрупповую дисперсию для каждого разбиения
    within_group_variance_s_minus_1 = np.var(mid_points_s_minus_1, ddof=1)
    within_group_variance_s_plus_1 = np.var(mid_points_s_plus_1, ddof=1)
    
    # Вычисляем межгрупповую дисперсию для каждого разбиения
    mean_s_minus_1 = np.mean(mid_points_s_minus_1)
    mean_s_plus_1 = np.mean(mid_points_s_plus_1)
    between_group_variance_s_minus_1 = np.var(mid_points_s_minus_1 - mean_s_minus_1, ddof=1)
    between_group_variance_s_plus_1 = np.var(mid_points_s_plus_1 - mean_s_plus_1, ddof=1)
    
    # Вычисляем общую дисперсию
    total_variance_s_minus_1 = np.var(data, ddof=1)
    total_variance_s_plus_1 = np.var(data, ddof=1)
    
    # Рассчитываем долю межгрупповой дисперсии
    ratio_s_minus_1 = between_group_variance_s_minus_1 / total_variance_s_minus_1
    ratio_s_plus_1 = between_group_variance_s_plus_1 / total_variance_s_plus_1
    
    return ratio_s_minus_1, ratio_s_plus_1

def pearson_chi_squared_test(data, expected_distribution):
    # Вычисляем количество интервалов с использованием формулы s = 1 + floor(log2(n))
    n = len(data)
    s = 1 + int(np.log2(n))  # Количество интервалов
    
    # Разбиваем данные на интервалы
    observed_frequencies, bin_edges = np.histogram(data, bins=s)
    
    # Рассчитываем ожидаемую частоту для каждого интервала, предполагая экспоненциальное распределение
    if expected_distribution == 'exponential':
        lambda_param = 1 / np.mean(data)  # Параметр экспоненциального распределения
        expected_frequencies = np.diff(stats.expon.cdf(bin_edges, scale=1/lambda_param)) * n
        
        # Нормализация ожидаемых частот, чтобы их сумма равнялась n
        expected_frequencies *= sum(observed_frequencies) / sum(expected_frequencies)
    else:
        raise ValueError("Unsupported distribution")
    
    # Применяем критерий Пирсона
    chi2_stat, p_value = stats.chisquare(observed_frequencies, expected_frequencies)
    
    return chi2_stat, p_value

def kolmogorov_smirnov_test(data, expected_distribution):
    # Преобразуем данные в numpy массив
    data = np.array(data)
    
    # Проводим тест Колмогорова-Смирнова
    if expected_distribution == 'exponential':
        # Параметр для экспоненциального распределения (обратная величина к среднему)
        lambda_param = 1 / np.mean(data)
        
        # Экспоненциальное распределение с параметром lambda_param
        cdf_values = stats.expon.cdf(data, scale=1/lambda_param)
        
        # Статистика теста Колмогорова-Смирнова
        ks_stat, p_value = stats.kstest(data, 'expon', args=(0, 1/lambda_param))
    else:
        raise ValueError("Unsupported distribution")
    
    return ks_stat, p_value


def get_country_names(file_path):
    with open(file_path, newline='', encoding='ISO-8859-1') as csvfile:
        reader = csv.DictReader(csvfile)
        country_names = [row['Country of Citizenship'] for row in reader]
    return country_names


# Main function
def main(file_path):
    
    # Data
    data = read_csv(file_path)
    country_names = get_country_names(file_path)
    
    # Task 1
    mode_men, mode_women = calculate_mode(data)
    median_men, median_women = calculate_median(data)
    mean_men, mean_women = calculate_mean(data)
    variance_men, variance_women = calculate_variance(data)
    cv_men, cv_women = calculate_cv(data)

    table = [
        ['Mode', mode_men, mode_women],
        ['Median', median_men, median_women],
        ['Mean', mean_men, mean_women],
        ['Variance', variance_men, variance_women],
        ['Coefficient of Variation', f'{cv_men}%', f'{cv_women}%']
    ]
    print("\nStatistics Table:")
    print(tabulate(table, headers=['Metric', 'Men', 'Women'], tablefmt='pretty'))
    
    # Task 2
    homogeneity_men, homogeneity_women = assess_homogeneity(cv_men, cv_women)
    print(f"Homogeneity (Men): {homogeneity_men}")
    print(f"Homogeneity (Women): {homogeneity_women}")
    
    # Task 3: Remove outliers and save to CSV
    filtered_data = remove_outliers(data, country_names)
    save_to_csv('data/filtered_data.csv', filtered_data)
    print("Filtered data saved to 'filtered_data.csv'")
    
    # Task 4
    men_data = [item[0] for item in data] # item[1] for item in filtered_data
    intervals_men, bin_edges_men = split_data_into_intervals(men_data)
    
    print("Men Data Intervals (using log2 method):")
    for i in range(len(intervals_men)):
        print(f"Interval {i+1}: {bin_edges_men[i]} - {bin_edges_men[i+1]}, Frequency: {intervals_men[i]}")
        
    women_data = [item[1] for item in data] #item[2] for item in filtered_data
    intervals_women, bin_edges_women = split_data_into_intervals(women_data)
        
    print("\nWomen Data Intervals (using log2 method):")
    for i in range(len(intervals_women)):
        print(f"Interval {i+1}: {bin_edges_women[i]} - {bin_edges_women[i+1]}, Frequency: {intervals_women[i]}")   

    # Task 5
    plot_histogram_and_polygon(men_data, bins=bin_edges_men, label='Men')
    plot_histogram_and_polygon(women_data, bins=bin_edges_women, label='Women')
    
    # Task 6
    calculate_variances(file_path)
    
    # Task 7
    men_data = [item[0] for item in data]  # Количества мужчин
    women_data = [item[1] for item in data]  # Количества женщин

    # Количество интервалов
    n=len(data)
    s = 1 + int(np.log2(n))

    # Применяем функцию для мужчин и женщин
    ratio_men_s_minus_1, ratio_men_s_plus_1 = split_data_into_two_intervals(men_data, s)
    ratio_women_s_minus_1, ratio_women_s_plus_1 = split_data_into_two_intervals(women_data, s)

    # Выводим результаты
    print(f"Для мужчин, доля межгрупповой дисперсии при разбиении на {s-1} интервалов: {ratio_men_s_minus_1:.4f}")
    print(f"Для мужчин, доля межгрупповой дисперсии при разбиении на {s+1} интервалов: {ratio_men_s_plus_1:.4f}")
    print(f"Для женщин, доля межгрупповой дисперсии при разбиении на {s-1} интервалов: {ratio_women_s_minus_1:.4f}")
    print(f"Для женщин, доля межгрупповой дисперсии при разбиении на {s+1} интервалов: {ratio_women_s_plus_1:.4f}")


    # Task 8
    chi2_stat_men, p_value_men = pearson_chi_squared_test(men_data, 'exponential')
    print(f"Критерий Пирсона: {chi2_stat_men:.4f}, p-value: {p_value_men:.4f}") # соответствует
    
    ks_stat_men, p_value_men = kolmogorov_smirnov_test(men_data, 'exponential')
    print(f"Критерий Колмогорова: {ks_stat_men:.4f}, p-value: {p_value_men:.4f}")

# Specify the file path
file_path = 'data/population_by_country_2020.csv'

main(file_path)

