# -*- coding: windows-1251 -*-
import re
import pandas as pd
from matplotlib import pyplot as plt
import math
from tkinter import *
from tkinter import ttk
from matplotlib.backends.backend_tkagg import NavigationToolbar2Tk, FigureCanvasTkAgg
from matplotlib.figure import Figure

class Scrollable(Frame):
    """
       Make a frame scrollable with scrollbar on the right.
       After adding or removing widgets to the scrollable frame,
       call the update() method to refresh the scrollable area.
    """

    def __init__(self, frame, width=16):

        scrollbar = Scrollbar(frame, width=width)
        scrollbar.pack(side=RIGHT, fill=Y, expand=False)

        self.canvas = Canvas(frame, yscrollcommand=scrollbar.set)
        self.canvas.pack(side=LEFT, fill=BOTH, expand=True)

        scrollbar.config(command=self.canvas.yview)

        self.canvas.bind('<Configure>', self.__fill_canvas)

        # base class initialization
        Frame.__init__(self, frame)

        # assign this obj (the inner frame) to the windows item of the canvas
        self.windows_item = self.canvas.create_window(0,0, window=self, anchor=NW)


    def __fill_canvas(self, event):
        "Enlarge the windows item to the canvas width"

        canvas_width = event.width
        self.canvas.itemconfig(self.windows_item, width = canvas_width)

    def update(self):
        "Update the canvas and the scrollregion"

        self.update_idletasks()
        self.canvas.config(scrollregion=self.canvas.bbox(self.windows_item))
        
def calculate_holsted_metrics(code, excluded_words=None, words_to_delete=None):
    
    # счетчики
    unique_operators = set()
    unique_operands = set()
    operator_count = 0
    operand_count = 0
    operator_occurrences = {}
    operand_occurrences = {}

    # регулярки
    operator_pattern = (r'(\+=|-=|\*=|/=|\+\+|--|&&|\|\||==|!=|>=|<=|<<|>>|\+|-|<|>|\*|/|%|&|\||\^|=|\.|;|\^|\b'
                        r'in\b|\belse if\b|\belse\b|\bforeach\b|\bbreak\b|\bcontinue\b|\bgoto\b\s+\w+'
                        r'|\bdo\b|println|\[|'
                        r'throw\b|\bprint\b|\btry\b|\bnew\b|\bimport\b)')
    str_literal_pattern = r'("[^"]*"|\'[^\']*\')'
    operand_pattern = r'\b(?!(?:' + '|'.join(excluded_words) + r'))\w+\b'
    method_pattern = r'\b\w+\b\s*\.\s*\w+\s*\([^()]*\)'
    method_pattern2 = r'(\w+)\.(\w+)\s*{[^}]*}'
    method_pattern3 = r'(\w+)\.(\w+)\s*{[^}]*}\.(\w+)\s*\([^()]*\)'
    function_name_pattern = r'\b\w+\b(?=\s*\([^()]*\)\s*\{)'
    call_constructor_pattern =  r'new\s+\b\w+\b(?=\s*\([^()]*\))'
    #round_brackets_pattern = r'(?<![\w\?])(\s*\()'
    round_brackets_pattern = r'\((?:\w+\s*[+*\/-]\s*\w+\s*)+\)'
    dollar_pattern = r'\$\w+|\$\{'
    
    delete_pattern = r'\b(?:{})\b'.format('|'.join(map(re.escape, words_to_delete)))
    delete_marks_pattern = r'\bcase\b\s+.+'
    
    code = re.sub(r'//.*', '', code) #удаляем комментарии
    code = re.sub(delete_pattern, '', code)
    code = re.sub(delete_marks_pattern, '', code)
    #print(re.findall(delete_marks_pattern, code))
    #print(code)
    code = re.sub(r'\bList\b\s*\<\w+\>|\bCollection\b\s*\<\w+\>', '', code)

    operators = re.findall(dollar_pattern, code)
    for operator in operators:
        if len(operator) == 2:
            operator = '$'
        else:    
            operand = operator[1:]
            unique_operands.add(operand)
            operand_occurrences[operand] = operand_occurrences.get(operand, 0) + 1
            operand_count += 1
            operator = '$'
        unique_operators.add(operator)
        operator_occurrences[operator] = operator_occurrences.get(operator, 0) + 1
        operator_count += 1
    
    operands = re.findall(str_literal_pattern, code)
    code = re.sub(str_literal_pattern, '', code)
    #print(code)
    #code = re.sub(operand_pattern, '', code)
    for operand in operands:
        unique_operands.add(operand)
        operand_occurrences[operand] = operand_occurrences.get(operand, 0) + 1
        operand_count += 1
    
    # поиск операторов
    operators = re.findall(operator_pattern, code)
    #print(operators)
    #code = re.sub(operator_pattern, '', code)
    i = 0
    while i < len(operators):
        operator = operators[i]
        if operator == 'else':
            operator = 'if-else()'
            operator_occurrences['if()'] = operator_occurrences.get('if()', 0) - 1
            operator_count -= 1
        elif operator == 'do':
            operator = 'do-while()'
        elif operator == 'println' or operator == 'print':
            operator += '()'
        elif operator == '[':
            operator = '[]'
        unique_operators.add(operator)
        operator_occurrences[operator] = operator_occurrences.get(operator, 0) + 1
        operator_count += 1
        i += 1
        
    operators = re.findall(round_brackets_pattern, code)
    for operator in operators:
        operator = re.sub(r'[^()]', '', operator)#удаляем все символы из строки кроме скобок
        unique_operators.add(operator)
        operator_occurrences[operator] = operator_occurrences.get(operator, 0) + 1
        operator_count += 1
        
    #print(code)
    # поиск методов
    methods = re.findall(method_pattern, code)
    code = re.sub(method_pattern, '', code)
    for method in methods:
        method_name = method.split('.')[-1].split('(')[0].strip()
        method_name += '()'
        unique_operators.add(method_name)
        operator_occurrences[method_name] = operator_occurrences.get(method_name, 0) + 1
        operator_count += 1
        
    methods = re.findall(method_pattern2, code)
    #code = re.sub(method_pattern2, '', code)
    for method in methods:
        method_name = method[1]
        method_name += '{}'
        unique_operators.add(method_name)
        operator_occurrences[method_name] = operator_occurrences.get(method_name, 0) + 1
        operator_count += 1
        unique_operators.add('{}')
        operator_occurrences['{}'] = operator_occurrences.get('{}', 0) + 1
        operator_count += 1
        
    methods = re.findall(method_pattern3, code)
    code = re.sub(method_pattern3, '', code)
    for method in methods:
        method_name = method[2]
        method_name += '()'
        unique_operators.add(method_name)
        operator_occurrences[method_name] = operator_occurrences.get(method_name, 0) + 1
        operator_count += 1

    # поиск функций
    functions = re.findall(function_name_pattern, code)
    code = re.sub(function_name_pattern, '', code)
    for function in functions:
        if function != 'println':
            if function == 'switch':
                function = 'switch-case-default'
            function += '()'
            unique_operators.add(function)
            operator_occurrences[function] = operator_occurrences.get(function, 0) + 1
            operator_count += 1
            
    functions = re.findall(call_constructor_pattern, code)
    for function in functions:
        function = function.replace('new ', '')
        function += '()'
        unique_operators.add(function)
        operator_occurrences[function] = operator_occurrences.get(function, 0) + 1
        operator_count += 1

    # поиск операндов      
    operands = re.findall(operand_pattern, code)
    #code = re.sub(operand_pattern, '', code)
    for operand in operands:
        if operand not in unique_operators:
            if '||' in operand:
                continue
            unique_operands.add(operand)
            operand_occurrences[operand] = operand_occurrences.get(operand, 0) + 1
            operand_count += 1

    print("Dictionary of operators:", len(unique_operators))
    print("Dictionary of operands:", len(unique_operands))
    print("Total number of operators:", operator_count)
    print("Total number of operands:", operand_count)
    print("Occurrences of operators:")
    for operator, count in operator_occurrences.items():
        print(operator, ":", count)
    print("Occurrences of operands:")
    for operand, count in operand_occurrences.items():
        print(operand, ":", count)
 
    # Создаем главное окно
    root = Tk()
    root.title("Tables")
    root.geometry("800x600")

    notebook = ttk.Notebook(root)

    frame1 = ttk.Frame(root)
    frame1.pack(side=LEFT, fill=BOTH, expand=1)

    scrollable1 = Scrollable(frame1, width=32)
    for index, i in enumerate(operator_occurrences.items()):
        ttk.Button(scrollable1, text= i[0]).grid(row=index, column=0, sticky=NSEW)
        ttk.Button(scrollable1, text= i[1]).grid(row=index, column=1, sticky=NSEW)

    frame2 = Frame(root)
    frame2.pack(side=LEFT, fill=BOTH, expand=1)
    
    scrollable2 = Scrollable(frame2, width=32)
    for index, i in enumerate(operand_occurrences.items()):
        ttk.Button(scrollable2, text= i[0]).grid(row=index, column=0, sticky=NSEW)
        ttk.Button(scrollable2, text= i[1]).grid(row=index, column=1, sticky=NSEW)

    frame3 = Frame(root)
    frame3.pack(side=LEFT, fill=BOTH, expand=1)

    Dictionary_of_program = f"{len(unique_operators)} + {len(unique_operands)} = {len(unique_operators) + len(unique_operands)}"
    Length_of_program = f"{operator_count} + {operand_count} = {operator_count + operand_count}"
    Scope_of_program = f"{(operator_count + operand_count)} * log2({len(unique_operators) + len(unique_operands)}) = {int((operator_count + operand_count) * math.log2(len(unique_operators) + len(unique_operands)))}"

    data = [["Program vocabulary n =", Dictionary_of_program],
            ["Program length N =", Length_of_program],
            ["Program volume V =", Scope_of_program]
            ]

    scrollable3 = Scrollable(frame3, width=32)
    for index, i in enumerate(data):
        ttk.Button(scrollable3, text= i[0]).grid(row=index, column=0, sticky=NSEW)
        ttk.Button(scrollable3, text= i[1]).grid(row=index, column=1, sticky=NSEW)

    notebook.add(frame1, text='Operators')
    notebook.add(frame2, text='Operands')
    notebook.add(frame3, text='Program Metrics')
    
    
    notebook.pack(side=TOP, fill=BOTH, expand=1)
    
    scrollable1.update()
    scrollable2.update()
    scrollable3.update()
    
    # Отображаем окно
    root.mainloop()

    print("Total number of operators:", operator_count)
    print("Total number of operands:", operand_count)


file_path = r"C:\Users\lishy\IdeaProjects\groovy\src\Main.groovy"

with open(file_path, "r", encoding="utf-8") as file:
    groovy_code = file.read()

excluded_words = ['assert', 'break', 'case', 'catch', 'class', 'const', 'continue', 
                  'def', 'default', 'do', 'else', 'enum', 'extends', 'final', 'finally', 
                  'for', 'foreach', 'goto', 'if', 'implements', 'import', 'instanceof', 'interface', 
                  'native', 'new', 'null', 'non-sealed', 'package', 'public', 'protected', 
                  'private', 'return', 'static', 'strictfp', 'super', 'switch', 'synchronized', 
                  'threadsafe', 'throw', 'throws', 'transient', 'try', 'while', 'as', 
                  'in', 'permits', 'record', 'sealed', 'trait', 'var', 'yields', 'null', 'true', 
                  'false', 'boolean', 'char', 'byte', 'short', 'int', 'long', 'float', 'double', 'void',
                 'print', 'String']

words_to_delete = ['const', 'enum', 'interface', 'public', 'protected', 'class', 'def',
                  'private', 'static', 'var', 'boolean', 'char', 'byte', 'short',
                  'int', 'long', 'float', 'double', 'void', 'String']

# Вызов функции для парсинга кода Groovy
calculate_holsted_metrics(groovy_code, excluded_words, words_to_delete)
print(groovy_code)