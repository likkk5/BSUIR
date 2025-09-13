# -*- coding: windows-1251 -*-
import tkinter as tk
from tkinter import Label, Frame
import json
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# ���� � JSON �����
JSON_FILE = 'C:/courseworkavs/gas_data.json'

# ������� ��� �������� ������ �� JSON �����
def load_data(filename=JSON_FILE):
    try:
        with open(filename, 'r') as json_file:
            data = json.load(json_file)
            if isinstance(data, dict):  # ���� ������ ��������� ������
                return [data]  # ����������� ��� � ������ � ����� ���������
            elif isinstance(data, list):  # ���� ������ - ��� ������
                return data
            else:
                return []
    except Exception as e:
        print(f"������ �������� ������: {e}")
        return []

# ������� ��� ������� ������ �� JSON ��� �������
def clear_faults_in_json(filename=JSON_FILE):
    try:
        data = load_data(filename)
        if data:
            for entry in data:
                if isinstance(entry, dict) and 'ppm_fault' in entry:
                    entry['ppm_fault'] = None  # ������� ������ �� ������ ������
            with open(filename, 'w') as json_file:
                json.dump(data, json_file, indent=4)
            print("������ � JSON-����� �������.")
    except Exception as e:
        print(f"������ ��� ������� JSON-�����: {e}")

# ������� ��� �������� ���������� ����������� ������� ����
def count_gas_types(data):
    gas_count = {"Minimal": 0, "Methane": 0, "LPG": 0, "Critical": 0}
    for entry in data:
        if isinstance(entry, dict):  # ���������, ��� ������ - ��� �������
            gas_type = entry.get('gas_type', 'No Gas')
            if gas_type == "No Gas":
                gas_type = "Minimal"  # ����������� "No Gas" � "Minimal"
            if gas_type in gas_count:
                gas_count[gas_type] += 1
    return gas_count

# ������� ��� ��������� ������ ������ ������ ��� ������� ��������
def get_faults(data):
    faults = []
    for entry in data:
        if isinstance(entry, dict):  # ���������, ��� ������ - ��� �������
            ppm_fault = entry.get('ppm_fault', None)
            if ppm_fault:  # ��������� ������ ���� ������ ������������
                faults.append(ppm_fault)
    return faults

# ������� ��� ��������� ���������� ������������� ����
def get_last_gas_detected(data):
    if data:
        last_entry = data[-1]  # ��������� ������
        last_gas = last_entry.get('gas_type', "No Gas")
        return "Minimal" if last_gas == "No Gas" else last_gas
    return "Minimal"

# ������� ��� ���������� ���������� � �������� �������
def update_interface(root, canvas, ax, fault_label, gas_label, previous_data, last_faults):
    # ��������� ������ �� JSON
    data = load_data()

    # ���� ������ �� ���������� � �������� ����
    if data == previous_data:
        fault_label.config(
            text="\n".join(last_faults) if last_faults else "������ �� ����������."
        )
        root.after(1000, update_interface, root, canvas, ax, fault_label, gas_label, previous_data, last_faults)
        return

    # ��������� ������ ����� ������
    new_data = data[len(previous_data):]  # ������, ����������� ����� ���������� ��������

    if data:
        # ������������ ���������� ������� ���� ����
        gas_count = count_gas_types(data)

        # ��������� ���������
        ax.clear()
        gas_colors = {
            "Minimal": "gray",
            "Methane": "green",
            "LPG": "orange",
            "Critical": "red"
        }
        bar_colors = [gas_colors.get(gas, "blue") for gas in gas_count.keys()]
        ax.bar(gas_count.keys(), gas_count.values(), color=bar_colors)
        ax.set_xlabel("��� ����", fontsize=12)
        ax.set_ylabel("���-�� �����������", fontsize=12)
        ax.set_title("����������� �����", fontsize=14)
        canvas.draw()

        # ��������� ������� ����� ������
        current_faults = get_faults(new_data)

        # ���� ���� ����� ������, ��������� �����������
        if current_faults:
            last_faults[:] = current_faults  # ��������� ������� ��������� ������
        else:  # ���� ����� ������ ���, ������� �����������
            last_faults[:] = []

        fault_label.config(
            text="\n".join(last_faults) if last_faults else "������ �� ����������."
        )

        # ��������� ����� � ��������� ������������ �����
        last_gas = get_last_gas_detected(data)
        gas_label.config(text=f"��������� ���: {last_gas}")

    # ��������� ��������� ���������� ������
    previous_data[:] = data

    # ��������� ��������� ���������� ����� 1 �������
    root.after(1000, update_interface, root, canvas, ax, fault_label, gas_label, previous_data, last_faults)

# ������� ��� �������� ����������
def create_interface():
    # ������� ������ � JSON ��� ������� ���������
    clear_faults_in_json()

    # ������� ������� ����
    root = tk.Tk()
    root.title("����������� ����� - �������� �����")
    root.geometry("900x600")
    root.config(bg="#f4f4f4")

    # ������� ����� ��� �������
    graph_frame = Frame(root, bg="#f4f4f4", padx=10, pady=10)
    graph_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

    # ������� ����� ��� ��������� ����������
    info_frame = Frame(root, bg="#e8e8e8", padx=10, pady=10, relief=tk.RIDGE, borderwidth=2)
    info_frame.pack(side=tk.RIGHT, fill=tk.Y)

    # ���� ��� ������
    fault_frame = Frame(info_frame, bg="#e8e8e8", padx=5, pady=5, relief="groove", borderwidth=2)
    fault_frame.pack(fill=tk.X, pady=10)
    fault_label_title = Label(fault_frame, text="��������� ������", font=("Arial", 14, "bold"), bg="#e8e8e8")
    fault_label_title.pack(anchor="w")
    fault_label = Label(fault_frame, text="������ �� ����������.", font=("Arial", 12), justify=tk.LEFT, anchor="nw", bg="#e8e8e8", fg="red", wraplength=250)
    fault_label.pack(fill=tk.X, pady=5)

    # ���� ��� ���������� ������������� ����
    gas_frame = Frame(info_frame, bg="#e8e8e8", padx=5, pady=5, relief="groove", borderwidth=2)
    gas_frame.pack(fill=tk.X, pady=10, side=tk.BOTTOM)  # ����������� ����� �����
    gas_label_title = Label(gas_frame, text="��������� ������������ ���", font=("Arial", 14, "bold"), bg="#e8e8e8")
    gas_label_title.pack(anchor="w")
    gas_label = Label(gas_frame, text="��� ����", font=("Arial", 12, "bold"), fg="blue", bg="#e8e8e8", wraplength=250, anchor="nw")
    gas_label.pack(fill=tk.X, pady=5)

    # ������� ������ � ��� ��� ���������
    fig, ax = plt.subplots(figsize=(5, 4))
    fig.patch.set_facecolor("#f4f4f4")
    canvas = FigureCanvasTkAgg(fig, master=graph_frame)
    canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

    # ������� ������ ��� ������������ ��������� ������ � ������
    previous_data = []
    last_faults = []

    # ��������� ���������� ����������
    update_interface(root, canvas, ax, fault_label, gas_label, previous_data, last_faults)

    # ������ ����� ��������� �������
    root.mainloop()

# �������� ������ ���������
if __name__ == "__main__":
    create_interface()
