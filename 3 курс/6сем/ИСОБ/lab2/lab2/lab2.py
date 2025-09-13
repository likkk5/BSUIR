import string

def caesar_cipher(text, shift, decrypt=False, alphabet=None):
    if alphabet is None:
        alphabet = string.ascii_lowercase + string.ascii_uppercase
    shift = -shift if decrypt else shift
    result = []
    
    for char in text:
        if char.lower() in alphabet.lower():
            is_upper = char.isupper()
            new_char = alphabet[(alphabet.lower().index(char.lower()) + shift) % (len(alphabet) // 2)]
            result.append(new_char.upper() if is_upper else new_char)
        else:
            result.append(char)
    
    return "".join(result)

def vigenere_cipher(text, key, decrypt=False, alphabet=None):
    if alphabet is None:
        alphabet = string.ascii_lowercase + string.ascii_uppercase
    if not key:
        raise ValueError("Ошибка: Ключ для шифра Виженера не может быть пустым.")
    
    result = []
    key_index = 0
    key_shifts = [alphabet.lower().index(k.lower()) for k in key if k.lower() in alphabet.lower()]
    
    for char in text:
        if char.lower() in alphabet.lower():
            is_upper = char.isupper()
            shift = key_shifts[key_index % len(key_shifts)]
            shift = -shift if decrypt else shift
            new_char = alphabet[(alphabet.lower().index(char.lower()) + shift) % (len(alphabet) // 2)]
            result.append(new_char.upper() if is_upper else new_char)
            key_index += 1
        else:
            result.append(char)
    
    return "".join(result)

def detect_language(text):
    en_alphabet = set(string.ascii_letters)
    ru_alphabet = set("абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ")
    
    text_chars = set(text)
    if text_chars & en_alphabet and text_chars & ru_alphabet:
        raise ValueError("Ошибка: В файле обнаружены символы нескольких языков.")
    elif text_chars & en_alphabet:
        return "en"
    elif text_chars & ru_alphabet:
        return "ru"
    else:
        raise ValueError("Ошибка: Не удалось определить язык текста.")

def process_file(input_file, output_file, key, cipher_type, decrypt=False):
    alphabets = {
        "en": string.ascii_lowercase + string.ascii_uppercase,
        "ru": "абвгдеёжзийклмнопрстуфхцчшщъыьэюя" + "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
    }
    
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            text = f.read()
    except FileNotFoundError:
        error_msg = f"Ошибка: Файл '{input_file}' не найден."
        print(error_msg)
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(error_msg)
        return
    except Exception as e:
        error_msg = f"Ошибка при чтении файла '{input_file}': {e}"
        print(error_msg)
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(error_msg)
        return
    
    try:
        language = detect_language(text)
        alphabet = alphabets[language]
        
        if cipher_type == "caesar":
            if not key.isdigit():
                raise ValueError("Ошибка: Для шифра Цезаря ключ должен быть целым числом.")
            shift = int(key)
            cipher_name = "Шифр Цезаря"
        elif cipher_type == "vigenere":
            key_language = detect_language(key)
            if key_language != language:
                raise ValueError("Ошибка: Язык ключа не совпадает с языком текста.")
            cipher_name = "Шифр Виженера"
        else:
            raise ValueError("Ошибка: Неизвестный тип шифра.")
    except ValueError as e:
        error_msg = str(e)
        print(error_msg)
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(error_msg)
        return
    
    try:
        if cipher_type == "caesar":
            result = caesar_cipher(text, shift, decrypt, alphabet)
        elif cipher_type == "vigenere":
            result = vigenere_cipher(text, key, decrypt, alphabet)
    except Exception as e:
        error_msg = f"Ошибка обработки данных: {e}"
        print(error_msg)
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(error_msg)
        return
    
    try:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(result)

        operation = "Шифрования" if not decrypt else "Дешифрования"

        print(f"\n Успешно: {cipher_name} обработал данные!")
        print(f"Файл сохранён: {output_file}")
        print(f"Используемый язык: {'Русский' if language == 'ru' else 'Английский'}")
        print("-" * 50)
        print("Исходный текст:")
        print(text[:500] + ("..." if len(text) > 500 else ""))
        print(f"\nРезультат {operation.lower()}:")
        print(result[:500] + ("..." if len(result) > 500 else ""))
        print("-" * 50)
    except Exception as e:
        error_msg = f"Ошибка записи в файл '{output_file}': {e}"
        print(error_msg)
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(error_msg)
        return

if __name__ == "__main__":
    process_file("input.txt", "output_caesar.txt", "1", "caesar")  # Шифрование Цезаря
    process_file("output_caesar.txt", "decrypted_caesar.txt", "1", "caesar", decrypt=True)  # Дешифровка Цезаря
    process_file("input.txt", "output_vigenere.txt", "world", "vigenere")  # Шифрование Виженера
    process_file("output_vigenere.txt", "decrypted_vigenere.txt", "world", "vigenere", decrypt=True)  # Дешифровка Виженера
    process_file("input_ru.txt", "output_caesar_ru.txt", "3", "caesar")  # Шифрование Цезаря (русский)
    process_file("output_caesar_ru.txt", "decrypted_caesar_ru.txt", "3", "caesar", decrypt=True)  # Дешифровка Цезаря (русский)
    process_file("input_ru.txt", "output_vigenere_ru.txt", "КЛЮЧ", "vigenere")  # Шифрование Виженера (русский)
    process_file("output_vigenere_ru.txt", "decrypted_vigenere_ru.txt", "КЛЮЧ", "vigenere", decrypt=True)  # Дешифровка Виженера (русский)
