from matplotlib import pyplot as plt


def plot_histogram_and_polygon(data, s):
    """Строит гистограмму и полигон распределения для роста (см)."""

    min_value, max_value = min(data), max(data)
    interval_width = (max_value - min_value) / s
    intervals = [min_value + i * interval_width for i in range(s + 1)]

    histogram_data = [0] * s
    for value in data:
        for i in range(s):
            if intervals[i] <= value < intervals[i + 1]:
                histogram_data[i] += 1
                break

    # Вычисление середины интервалов для полигона частот
    midpoints = [(intervals[i] + intervals[i + 1]) / 2 for i in range(s)]

    # Визуализация гистограммы и полигона частот
    plt.figure(figsize=(10, 5))

    # Гистограмма (оттенок синего)
    plt.bar(midpoints, histogram_data, width=interval_width, edgecolor="black",
            alpha=0.7, color="#4A90E2", align='center', label="Гистограмма")

    # Полигон частот (фиолетовый)
    plt.plot(midpoints, histogram_data, marker="o", linestyle="-", color="#8E44AD",
             linewidth=2, markersize=6, label="Полигон частот")

    # Настройки графика
    plt.xlabel("Рост (см)", fontsize=12)
    plt.ylabel("Частота", fontsize=12)
    plt.title(f"Гистограмма и полигон распределения роста ({s} интервалов)", fontsize=14)
    plt.legend(fontsize=10)
    plt.grid(axis='y', linestyle='--', alpha=0.7)

    # Отображаем график
    plt.show()