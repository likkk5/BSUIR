import pandas as pd

from analysis import *
from characteristics import *
from distribution import chi_square_test, kolmogorov_smirnov_test
from graphics import plot_histogram_and_polygon


def load_population_data(csv_file="population_by_country_2020.csv"):
    """Загружает данные из CSV-файла."""
    try:
        df = pd.read_csv(csv_file)
        if "Population (2020)" not in df.columns:
            raise ValueError("В файле отсутствует столбец 'Population (2020)'.")
        return (df["Population (2020)"]).tolist() 
    except FileNotFoundError:
        print(f"Файл '{csv_file}' не найден.")
    except Exception as e:
        print(f"Произошла ошибка при загрузке данных: {e}")


def display_variance_analysis(s, variances):
    group_vars, within_var, between_var, total_var, between_ratio, check = variances

    print(f"\nАнализ дисперсий для {s} интервалов:")
    print(f"   - Групповые дисперсии: {[round(var, 2) for var in group_vars]}")
    print(f"   - Внутригрупповая дисперсия: {within_var:.2f}")
    print(f"   - Межгрупповая дисперсия: {between_var:.2f}")
    print(f"   - Общая дисперсия: {total_var:.2f}")
    print(f"   - Доля межгрупповой дисперсии: {between_ratio:.4f} ({between_ratio*100:.2f}%)")
    print(f"   - Итог: {'✔ Правило сложения выполнено' if check else '✖ Ошибка в расчётах'}")
    print("=" * 50)


def calculate_mad(data):
    """Вычисляет медианное абсолютное отклонение (MAD)."""
    median = calculate_median(data)
    absolute_deviations = [abs(x - median) for x in data]
    return calculate_median(absolute_deviations)


def remove_outliers_mad(data, threshold=2.5):
    median = calculate_median(data)
    mad = calculate_mad(data)

    # Рассчитываем границы
    lower_bound = median - threshold * mad
    upper_bound = median + threshold * mad

    # Фильтруем данные
    cleaned_data = []
    for x in data:
        if lower_bound <= x <= upper_bound:
            cleaned_data.append(x)

    return cleaned_data

if __name__ == '__main__':
    # Загружаем данные
    population_data = load_population_data("population_by_country_2020.csv")

    if population_data:
        population_data = population_data[:500]
        # Рассчитываем статистические показатели
        mean_value = calculate_mean(population_data)
        median_value = calculate_median(population_data)
        variance_value = calculate_variance(population_data, mean_value)
        coefficient_of_variation = calculate_coefficient_of_variation(variance_value, mean_value)
        mode_values = calculate_mode(population_data)

        # Выводим результаты
        print(f"\nСтатистические показатели для исходных данных:\n")
        print(f"   - Среднее: {mean_value:.2f}")
        print(f"   - Медиана: {median_value:.2f}")
        print(f"   - Дисперсия: {variance_value:.2f}")
        print(f"   - Коэффициент вариации: {coefficient_of_variation:.2f}%")
        print(f"   - Мода(-ы): {mode_values}")
        print(f"   - Оценка однородности выборки: {evaluate_homogeneity(coefficient_of_variation)}")

        # Удаляем выбросы
        filtered_population = remove_outliers(population_data)
        print(f"\nДанные после удаления выбросов:\n")
        print(f"   - Количество элементов после фильтрации: {len(filtered_population)}")


        # Разбиение на s-1, s, s+1 интервалов
        s = int(1 + math.log2(len(filtered_population)))

        # Основные числовые характеристики после удаления выбросов
        filtered_mean, filtered_variance, filtered_std_dev = calculate_mean_variance_std(filtered_population, s)  # s - количество интервалов

        # Выводим статистику после удаления выбросов
        print(f"\nСтатистические показатели для данных без выбросов:\n")
        print(f"   - Среднее: {filtered_mean:.2f}")
        print(f"   - Дисперсия: {filtered_variance:.2f}")
        print(f"   - Стандартное отклонение: {filtered_std_dev:.2f}")

        variances_s_minus_1 = compute_variances(filtered_population, s - 1)
        variances_s = compute_variances(filtered_population, s)
        variances_s_plus_1 = compute_variances(filtered_population, s + 1)

        # Вывод результатов
        display_variance_analysis(s - 1, variances_s_minus_1)
        display_variance_analysis(s, variances_s)
        display_variance_analysis(s + 1, variances_s_plus_1)

        # Оценка лучшего разбиения
        best_partition = max(
            (variances_s_minus_1 + (s - 1,)),
            (variances_s + (s,)),
            (variances_s_plus_1 + (s + 1,)),
            key=lambda x: x[4]
        )
        print(f"Лучшее разбиение: {best_partition[6]} интервалов с долей межгрупповой дисперсии {best_partition[4]:.4f}")

        chi_square_test(filtered_population, s)
        kolmogorov_smirnov_test(filtered_population)
        plot_histogram_and_polygon(filtered_population, s)

        # Доказательство состоятельности
        plot_statistics(filtered_population, filtered_mean, filtered_variance, step=10)

        # Доказательство несмещенности
        np.random.seed(42)
        true_mean = filtered_mean  # Истинное среднее значение роста
        true_variance = filtered_variance  # Истинная дисперсия роста
        sample_sizes = np.arange(1, 500, 10)

        sample_sizes, mean_errors, var_errors = prove_unbiasedness(true_mean, true_variance, sample_sizes)

        # Визуализация
        plt.figure(figsize=(12, 6))
        plt.plot(sample_sizes, mean_errors, label='Ошибка среднего', color='blue', marker='o')
        plt.plot(sample_sizes, var_errors, label='Ошибка дисперсии', color='red', marker='s')
        plt.xlabel('Размер выборки')
        plt.ylabel('Ошибка оценки')
        plt.legend()
        plt.title('Сходимость несмещённых оценок среднего и дисперсии')
        plt.grid()
        plt.show()


        # Доказательство эффективности
        sample1 = load_population_data("population_by_country_2020.csv")[:500]
        sample2 = load_population_data("population_by_country_2020.csv")
        t_stat, p_value, result = student_t_test(sample1, sample2)

        print(f"T-статистика: {t_stat}")
        print(f"p-значение: {p_value}")
        print(result)


        lower1, upper1 = confidence_interval(sample1)
        print(f"Доверительный интервал для подвыборки: ({lower1}, {upper1})")

        # Строим доверительный интервал для полной выборки
        lower2, upper2 = confidence_interval(sample2)
        print(f"Доверительный интервал для полной выборки: ({lower2}, {upper2})")
