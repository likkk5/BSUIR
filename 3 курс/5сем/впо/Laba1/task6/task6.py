#-*- coding: windows-1251 -*-
import os
import requests
from urllib.parse import urlparse
import argparse

def download_file(url, save_folder):
    try:
        # Проверяем, что URL начинается с "http" или "https"
        if not url.startswith(('http://', 'https://')):
            raise ValueError("Некорректный URL. Используйте URL, начинающийся с http:// или https://")

        # Извлекаем имя файла из URL
        parsed_url = urlparse(url)
        file_name = os.path.basename(parsed_url.path)

        # Проверяем, что файл имеет имя
        if not file_name:
            raise ValueError("Невозможно определить имя файла из URL")

        # Создаем папку, если она не существует
        if not os.path.exists(save_folder):
            os.makedirs(save_folder)

        # Полный путь для сохранения файла
        file_path = os.path.join(save_folder, file_name)

        # Скачиваем файл
        print(f"Загрузка файла с {url}...")
        response = requests.get(url, stream=True)

        # Проверка успешности запроса
        if response.status_code != 200:
            raise Exception(f"Ошибка при загрузке файла: статус {response.status_code}")

        # Записываем файл на диск по частям
        with open(file_path, 'wb') as file:
            for chunk in response.iter_content(chunk_size=8192):
                if chunk:
                    file.write(chunk)
        
        print(f"Файл успешно сохранен по пути: {file_path}")
    except Exception as e:
        print(f"Ошибка: {e}")

if __name__ == "__main__":
    # Создаем парсер для командной строки
    parser = argparse.ArgumentParser(description="Скачивание файла с URL и сохранение его в указанную папку.")
    parser.add_argument("url", help="URL для скачивания файла")
    parser.add_argument("save_folder", help="Папка для сохранения файла")

    # Парсим аргументы
    args = parser.parse_args()

    # Вызываем функцию загрузки файла с аргументами
    download_file(args.url, args.save_folder)

