# -*- coding: windows-1251 -*-
import tkinter as tk
from tkinter import Label, Frame
import json
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Путь к JSON файлу
JSON_FILE = 'C:/courseworkavs/gas_data.json'

# Функция для загрузки данных из JSON файла
def load_data(filename=JSON_FILE):
    try:
        with open(filename, 'r') as json_file:
            data = json.load(json_file)
            if isinstance(data, dict):  # Если данные одиночный объект
                return [data]  # Преобразуем его в список с одним элементом
            elif isinstance(data, list):  # Если данные - это список
                return data
            else:
                return []
    except Exception as e:
        print(f"Ошибка загрузки данных: {e}")
        return []

# Функция для очистки ошибок из JSON при запуске
def clear_faults_in_json(filename=JSON_FILE):
    try:
        data = load_data(filename)
        if data:
            for entry in data:
                if isinstance(entry, dict) and 'ppm_fault' in entry:
                    entry['ppm_fault'] = None  # Убираем ошибки из каждой записи
            with open(filename, 'w') as json_file:
                json.dump(data, json_file, indent=4)
            print("Ошибки в JSON-файле очищены.")
    except Exception as e:
        print(f"Ошибка при очистке JSON-файла: {e}")

# Функция для подсчета количества обнаружений каждого газа
def count_gas_types(data):
    gas_count = {"Minimal": 0, "Methane": 0, "LPG": 0, "Critical": 0}
    for entry in data:
        if isinstance(entry, dict):  # Проверяем, что объект - это словарь
            gas_type = entry.get('gas_type', 'No Gas')
            if gas_type == "No Gas":
                gas_type = "Minimal"  # Преобразуем "No Gas" в "Minimal"
            if gas_type in gas_count:
                gas_count[gas_type] += 1
    return gas_count

# Функция для получения списка ошибок только для текущей итерации
def get_faults(data):
    faults = []
    for entry in data:
        if isinstance(entry, dict):  # Проверяем, что объект - это словарь
            ppm_fault = entry.get('ppm_fault', None)
            if ppm_fault:  # Добавляем только если ошибка присутствует
                faults.append(ppm_fault)
    return faults

# Функция для получения последнего обнаруженного газа
def get_last_gas_detected(data):
    if data:
        last_entry = data[-1]  # Последняя запись
        last_gas = last_entry.get('gas_type', "No Gas")
        return "Minimal" if last_gas == "No Gas" else last_gas
    return "Minimal"

# Функция для обновления интерфейса в реальном времени
def update_interface(root, canvas, ax, fault_label, gas_label, previous_data, last_faults):
    # Загружаем данные из JSON
    data = load_data()

    # Если данные не изменились с прошлого раза
    if data == previous_data:
        fault_label.config(
            text="\n".join(last_faults) if last_faults else "Ошибок не обнаружено."
        )
        root.after(1000, update_interface, root, canvas, ax, fault_label, gas_label, previous_data, last_faults)
        return

    # Вычисляем только новые записи
    new_data = data[len(previous_data):]  # Данные, добавленные после предыдущей итерации

    if data:
        # Подсчитываем количество каждого типа газа
        gas_count = count_gas_types(data)

        # Обновляем диаграмму
        ax.clear()
        gas_colors = {
            "Minimal": "gray",
            "Methane": "green",
            "LPG": "orange",
            "Critical": "red"
        }
        bar_colors = [gas_colors.get(gas, "blue") for gas in gas_count.keys()]
        ax.bar(gas_count.keys(), gas_count.values(), color=bar_colors)
        ax.set_xlabel("Тип газа", fontsize=12)
        ax.set_ylabel("Кол-во обнаружений", fontsize=12)
        ax.set_title("Обнаружение газов", fontsize=14)
        canvas.draw()

        # Проверяем наличие новых ошибок
        current_faults = get_faults(new_data)

        # Если есть новые ошибки, обновляем отображение
        if current_faults:
            last_faults[:] = current_faults  # Сохраняем текущее состояние ошибок
        else:  # Если новых ошибок нет, очищаем отображение
            last_faults[:] = []

        fault_label.config(
            text="\n".join(last_faults) if last_faults else "Ошибок не обнаружено."
        )

        # Обновляем текст с последним обнаруженным газом
        last_gas = get_last_gas_detected(data)
        gas_label.config(text=f"Последний газ: {last_gas}")

    # Обновляем состояние предыдущих данных
    previous_data[:] = data

    # Планируем следующее обновление через 1 секунду
    root.after(1000, update_interface, root, canvas, ax, fault_label, gas_label, previous_data, last_faults)

# Функция для создания интерфейса
def create_interface():
    # Очищаем ошибки в JSON при запуске программы
    clear_faults_in_json()

    # Создаем главное окно
    root = tk.Tk()
    root.title("Обнаружение газов - Реальное время")
    root.geometry("900x600")
    root.config(bg="#f4f4f4")

    # Создаем фрейм для графика
    graph_frame = Frame(root, bg="#f4f4f4", padx=10, pady=10)
    graph_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

    # Создаем фрейм для текстовой информации
    info_frame = Frame(root, bg="#e8e8e8", padx=10, pady=10, relief=tk.RIDGE, borderwidth=2)
    info_frame.pack(side=tk.RIGHT, fill=tk.Y)

    # Поле для ошибок
    fault_frame = Frame(info_frame, bg="#e8e8e8", padx=5, pady=5, relief="groove", borderwidth=2)
    fault_frame.pack(fill=tk.X, pady=10)
    fault_label_title = Label(fault_frame, text="Возможные ошибки", font=("Arial", 14, "bold"), bg="#e8e8e8")
    fault_label_title.pack(anchor="w")
    fault_label = Label(fault_frame, text="Ошибок не обнаружено.", font=("Arial", 12), justify=tk.LEFT, anchor="nw", bg="#e8e8e8", fg="red", wraplength=250)
    fault_label.pack(fill=tk.X, pady=5)

    # Поле для последнего обнаруженного газа
    gas_frame = Frame(info_frame, bg="#e8e8e8", padx=5, pady=5, relief="groove", borderwidth=2)
    gas_frame.pack(fill=tk.X, pady=10, side=tk.BOTTOM)  # Располагаем фрейм снизу
    gas_label_title = Label(gas_frame, text="Последний обнаруженный газ", font=("Arial", 14, "bold"), bg="#e8e8e8")
    gas_label_title.pack(anchor="w")
    gas_label = Label(gas_frame, text="Нет газа", font=("Arial", 12, "bold"), fg="blue", bg="#e8e8e8", wraplength=250, anchor="nw")
    gas_label.pack(fill=tk.X, pady=5)

    # Создаем фигуру и ось для диаграммы
    fig, ax = plt.subplots(figsize=(5, 4))
    fig.patch.set_facecolor("#f4f4f4")
    canvas = FigureCanvasTkAgg(fig, master=graph_frame)
    canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

    # Создаем списки для отслеживания состояния данных и ошибок
    previous_data = []
    last_faults = []

    # Запускаем обновление интерфейса
    update_interface(root, canvas, ax, fault_label, gas_label, previous_data, last_faults)

    # Запуск цикла обработки событий
    root.mainloop()

# Основная логика программы
if __name__ == "__main__":
    create_interface()
