# -*- coding: windows-1251 -*-
import re
from matplotlib import pyplot as plt
import math
from tkinter import *
from tkinter import ttk
from matplotlib.backends.backend_tkagg import NavigationToolbar2Tk, FigureCanvasTkAgg
from matplotlib.figure import Figure

def count_operators(groovy_code):
    # Регулярное выражение для поиска всех операторов программы
    operator_pattern = (r'(\+=|-=|\*=|/=|\+\+|--|&&|\|\||==|!=|>=|<=|<<|>>|\+|-|<|>|\*|/|%|&|\||\^|=|\.|;|\^|\b'
                        r'in\b|\bforeach\b|\bbreak\b|\bcontinue\b|\bgoto\b\s+\w+'
                        r'|println|if|while|switch|for|'
                        r'\bthrow\b|\bprint\b|\btry\b|\bnew\b|\bimport\b|\[)')
    function_name_pattern = r'\b\w+\b(?=\s*\([^()]*\)\s*\{)'
    method_pattern = r'\.\s*\w+\s*\([^()]*\)'
    str_literal_pattern = r'("[^"]*"|\'[^\']*\')'
    dollar_pattern = r'\$\w+|\$\{'
    #round_brackets_pattern = r'\((?:\w+\s*[+*\/-]\s*\w+\s*)+\)'
    
    dollars = re.findall(dollar_pattern, groovy_code)
    
    operands = re.findall(str_literal_pattern, groovy_code)
    groovy_code = re.sub(str_literal_pattern, '', groovy_code)
    
    # Ищем все вхождения регулярного выражения в коде Groovy
    #matches = re.findall(pattern, groovy_code)
    operators = re.findall(operator_pattern, groovy_code)
    methods = re.findall(method_pattern, groovy_code)
    for method in methods:
        method_name = method.split('.')[1]
        method_name += '()'
        operators.append(method_name)
        
    length = len(operators) + len(dollars)
    
    return length

def count_conditional_operators(groovy_code):
    # Регулярное выражение для поиска условных операторов if-else и циклов
    pattern = r'if|for|while|case|default'
    # Ищем все вхождения регулярного выражения в коде Groovy
    matches = re.findall(pattern, groovy_code, flags=re.DOTALL)

    return len(matches)

def calculate_cl(cl, total_operators):
    return cl / total_operators if total_operators > 0 else 0

def calc_cli(groovy_code):
    items = groovy_code.split()
    isCondition = False
    open_scopes = 0
    close_scopes = 0
    depth_level = -1
    levels = []
    cases_kol = [] #количество case в каждом switch
    
    counter = 0 #max kol cases in branch
    cases = re.findall(r'\bswitch\b|\bcase\b', groovy_code)
    i = 0
    for case in cases:
        if case == 'switch':
            cases_kol.append(i)
            i = 0
        else:
            i += 1
    cases_kol.append(i)
    #print(cases_kol)

    num_of_case = 0
    num_of_switch = 0
    isSwitch = False
    for item in items:
        if item == 'if' or item == 'else' or item == 'for' or item == 'while' or item == 'switch' or item == 'do' or item == 'case':
            isCondition = True
        if item == 'switch':
            isSwitch = True
            num_of_switch += 1
        if isCondition:     
            if item == '{' or item == 'case':
                if isSwitch:
                    isSwitch = False
                    continue
                if item == case:
                    num_of_case += 1
                open_scopes += 1
                depth_level += 1
            elif item == '}' or item == 'break':
                if item == 'break' and cases_kol[num_of_switch] != num_of_case:
                    continue
                levels.append(depth_level)
                depth_level -= 1
                close_scopes += 1
                if (open_scopes == close_scopes):
                    open_scopes = close_scopes = 0
                    isCondition = False                 
    levels.append(counter)
    #print(levels)
    max_depth = max(levels)

    return max_depth

def calculate_metrics(groovy_code):
    total_operators = count_operators(groovy_code)
    conditional_operators = count_conditional_operators(groovy_code)
    cl = conditional_operators
    cli = calc_cli(groovy_code)
    cl_ratio = calculate_cl(cl, total_operators)

    return total_operators, cl, cli, cl_ratio

def output(total_operators, cl, cli, cl_ratio):
    # Создаем главное окно
    root = Tk()
    root.title("Tables")
    root.geometry("800x600")

    notebook = ttk.Notebook(root)
    frame3 = Frame(root)
    frame3.pack(side=LEFT, fill=BOTH, expand=1)

    data = [["Общее количество операторов:", total_operators],
            ["Количество условных операторов (CL)-абсолютная сложность:", cl],
            ["Максимальный уровень вложенности условного оператора (CLI)-расширенная метрика:", cli],
            ["Насыщенность программы условными операторами (cl)-отностельная сложность:", cl_ratio]
            ]

    notebook.add(frame3, text='Program Metrics')
    notebook.pack(side=TOP, fill=BOTH, expand=1)
    # Добавление меток для отображения данных
    for i, (label_text, value) in enumerate(data):
        label = Label(frame3, text=label_text, anchor="w", justify="left")
        label.grid(row=i, column=0, sticky="w", padx=10, pady=5)
        
        value_label = Label(frame3, text=str(value), anchor="w", justify="left")
        value_label.grid(row=i, column=1, sticky="w", padx=10, pady=5)
    # Отображаем окно
    root.mainloop()

file_path = r"C:\Users\lishy\IdeaProjects\lab2part1\src\Main.groovy"

with open(file_path, "r", encoding="utf-8") as file:
    groovy_code = file.read()

total_operators, cl, cli, cl_ratio = calculate_metrics(groovy_code)

output(total_operators, cl, cli, cl_ratio)

print("Общее количество операторов:", total_operators)
print("Количество условных операторов (CL)-абсолютная сложность:", cl)
print("Максимальный уровень вложенности условного оператора (CLI)-расширенная метрика:", cli)
print("Насыщенность программы условными операторами (cl)-отностельная сложность:", cl_ratio)