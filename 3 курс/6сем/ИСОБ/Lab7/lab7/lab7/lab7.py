#coding: windows-1251
import re
import random
import string
import keyword
import builtins
import base64
import os

def encode_variables(code):
    reserved = set(keyword.kwlist) | set(dir(builtins))
    code_clean = re.sub(r'(\"|\').*?(\1)', '', code, flags=re.DOTALL) #удаление строковых литералов в идент
    code_clean = re.sub(r'#.*', '', code_clean) #удаление комментариев
    identifiers = re.findall(r'\b(?!def\b|class\b)([a-zA-Z_][a-zA-Z0-9_]*)\b', code_clean) #поиск идентификаторов(переменных,функций)
    identifiers = {name for name in identifiers if name not in reserved} 
    replacements = {name: ''.join(random.choices(string.ascii_letters, k=8)) for name in identifiers}
    for old, new in replacements.items():
        code = re.sub(r'\b{}\b'.format(re.escape(old)), new, code) #замена идентификаторов в коде
    return code


def add_junk_code(code):
    junk_templates = [
        '    z = sum([i for i in range(100)])\n',
        '    y = [i**3 for i in range(50)]\n',
    ]
    lines = code.split('\n')
    num_junk = random.randint(2, 5) 
    for _ in range(num_junk):
        pos = random.randint(0, len(lines))
        lines.insert(pos, random.choice(junk_templates))
    return '\n'.join(lines)


def encode_string_literals(code):
    strings = re.findall(r'"(.*?)"', code)
    for s in strings:
        encoded = base64.b64encode(s.encode()).decode()
        code = code.replace(f'"{s}"', f'base64.b64decode("{encoded}").decode()')
    return code


def obfuscate(code):
    code = encode_variables(code)
    code = add_junk_code(code)
    code = encode_string_literals(code)
    return code

def obfuscate_file(input_file, output_file):
    if not os.path.exists(input_file):
        print(f"Файл {input_file} не найден.")
        return

    with open(input_file, 'r', encoding='utf-8') as f:
        code = f.read()

    obfuscated_code = obfuscate(code)

    with open(output_file, 'w', encoding='utf-8') as f:
        f.write("import base64\n\n" + obfuscated_code)

    print(f"Обфускация завершена. Файл сохранен как: {output_file}")

obfuscate_file("source.py", "source_obfuscated.py")
