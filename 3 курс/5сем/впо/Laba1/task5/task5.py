# -*- coding: windows-1251 -*-
import os
import argparse
import sys

def find_files_with_extension(directory, extension):
    """Проходит по директориям и возвращает файлы с указанным расширением."""
    if not os.path.isdir(directory):
        raise ValueError(f"Ошибка: директория {directory} не существует.")

    if not extension.startswith('.') or len(extension) <= 1:
        raise ValueError(f"Ошибка: некорректное расширение {extension}. Оно должно начинаться с точки (например, .txt).")

    result = []
    extension = extension.lower() #Приводим к нижнему регисту
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.lower().endswith(extension):
                result.append(os.path.normpath(os.path.join(root, file)))
    return result

if __name__ == "__main__":
    # Создаем парсер для аргументов командной строки
    parser = argparse.ArgumentParser(description="Поиск файлов с указанным расширением.")
    
    # Аргумент для директории
    parser.add_argument("directory", help="Директория для поиска файлов")
    
    # Аргумент для расширения файлов
    parser.add_argument("extension", help="Расширение файлов (например, .txt)")
    
    # Получаем аргументы командной строки
    args = parser.parse_args()

    try:
        # Поиск файлов и вывод их на экран
        files = find_files_with_extension(args.directory, args.extension)
        if files:
            for file in files:
                print(file)
        else:
            print(f"Файлы с расширением '{args.extension}' не найдены в директории '{args.directory}'.")
    except ValueError as e:
        print(e)
        sys.exit(1)
