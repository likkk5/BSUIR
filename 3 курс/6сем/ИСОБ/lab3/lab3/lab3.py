# -*- coding: windows-1251 -*-

import hashlib
import os
import random
import time

# Конфигурация системы
TGS_KEY = "tgs_secret_key"
SERVICE_KEY = "service_secret_key"

# База данных пользователей
USER_DB = {
    "ksusha": "password123",
    "admin": "securepass"
}

SESSIONS = {}  # {username: session_key}
TICKETS = {}   # {ticket_id: ticket_data}

# Хранилище файлов для чтения
PROTECTED_FILES = {"protected_file.txt": "Это содержимое защищенного файла.\n" * 10}

# Доступные сервисы
SERVICES = {"file_access", "service1", "service2"}

# Создаём файлы, если их нет
for filename, content in PROTECTED_FILES.items():
    if not os.path.exists(filename):
        with open(filename, "w", encoding="windows-1251") as file:
            file.write(content)

def hash_value(data):
    return hashlib.sha256(data.encode()).hexdigest()

def generate_session_key(prefix="key_"):
    return f"{prefix}{random.randint(1000, 9999)}"

def authenticate(username, password):
    # Сначала проверяем наличие логина
    if username not in USER_DB:
        print("Ошибка: Указанный логин не существует.")
        return None
    
    # Если логин существует, проверяем пароль
    if USER_DB[username] != password:
        print("Ошибка: Неверные учетные данные.")
        return None

    # Генерируем сессионный ключ для аутентификации
    session_key = generate_session_key("auth_")
    SESSIONS[username] = session_key
    tgt = {"user": username, "key": session_key, "time": time.time()}
    encrypted_tgt = hash_value(f"{tgt}{TGS_KEY}")
    TICKETS[f"{username}_tgt"] = encrypted_tgt
    print(f"Успешная аутентификация. Ваш TGT: {encrypted_tgt[:10]}...")
    print(f"Ваш сессионный ключ для аутентификации: {session_key}")
    return encrypted_tgt

def get_service_ticket(username, tgt, service):
    if username not in SESSIONS or TICKETS.get(f"{username}_tgt") != tgt:
        print("Ошибка: Недействительный TGT. Повторите аутентификацию.")
        return None
    
    # Проверяем, существует ли такой сервис
    if service not in SERVICES:
        print(f"Ошибка: Сервис '{service}' не существует. Попробуйте снова.")
        return None
    
    # Генерируем сессионный ключ для сервиса
    service_key = generate_session_key("service_")
    ticket = {"user": username, "service": service, "key": service_key, "time": time.time()}
    encrypted_ticket = hash_value(f"{ticket}{SERVICE_KEY}")
    TICKETS[f"{username}_{service}"] = ticket
    print(f"Сервисный билет успешно выдан для '{service}'. Билет: {encrypted_ticket[:10]}...")
    print(f"Ваш сессионный ключ для сервиса '{service}': {service_key}")
    return encrypted_ticket

def access_service(username, service, ticket):
    stored_ticket = TICKETS.get(f"{username}_{service}")
    if not stored_ticket or hash_value(f"{stored_ticket}{SERVICE_KEY}") != ticket:
        print("Ошибка: Билет недействителен или отсутствует. Запросите новый.")
        return False
    print(f"Доступ к сервису '{service}' разрешен!")
    if service == "file_access":
        read_protected_file(username)
    return True

def read_protected_file(username):
    # Проверяем, есть ли у пользователя доступ к сервису "file_access"
    if f"{username}_file_access" not in TICKETS:
        print("Ошибка: У вас нет доступа к сервису чтения файлов. Запросите сервисный билет.")
        return

    print("Доступные файлы:", ", ".join(PROTECTED_FILES.keys()))
    filename = input("Введите имя файла для чтения: ").strip()
    if filename not in PROTECTED_FILES:
        print("Ошибка: Доступ к указанному файлу запрещён!")
        return
    print(f"\nЧТЕНИЕ ФАЙЛА: {filename}\n")
    try:
        with open(filename, "r", encoding="windows-1251") as file:
            for line in file:
                print(line.strip())
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")

def system_statistics():
    print("\nСТАТИСТИКА СИСТЕМЫ:")
    print(f"Авторизованные пользователи: {list(SESSIONS.keys())}")
    print(f"Выданные сервисные билеты: {TICKETS}")

def get_input(prompt, valid_values=None):
    while True:
        user_input = input(prompt).strip()
        if user_input.lower() == "exit":
            print("Выход из программы.")
            exit()  # Завершаем программу
        if valid_values:
            if user_input in valid_values:
                return user_input
            else:
                print(f"Ошибка: Ввод должен быть одним из следующих значений: {', '.join(valid_values)}.")
        elif user_input != "":
            return user_input
        else:
            print("Ошибка: Ввод не может быть пустым. Попробуйте снова.")

def main():
    username = None
    while True:
        print("\nГЛАВНОЕ МЕНЮ")
        print("1. Аутентификация пользователя")
        print("2. Запрос сервисного билета")
        print("3. Доступ к сервису")
        print("4. Пакетное чтение файла")
        print("5. Статистика системы")
        print("6. Выход")
        print("\nЧтобы выйти из программы введите 'exit' в любой момент.")
        choice = get_input("Выберите действие (1-6): ", valid_values=["1", "2", "3", "4", "5", "6", "exit"])

        if choice == "exit":
            print("Выход из программы...")
            break
        
        if choice == "1":
            user = None
            while user not in USER_DB:
                user = get_input("Введите логин: ")
                if user == "exit":
                    print("Выход из программы...")
                    return
                if user not in USER_DB:
                    print("Ошибка: Указанный логин не существует.")
            
            pwd = get_input("Введите пароль: ")
            tgt = authenticate(user, pwd)
            if tgt:
                username = user
                # Выводим сессионный ключ
                session_key = SESSIONS.get(username)
                print(f"Ваш сессионный ключ: {session_key}")
        elif choice == "2":
            if not username:  # Если пользователь не аутентифицирован, запрашиваем логин
                print("Ошибка: Сначала выполните аутентификацию.")
                continue  # Возвращаемся к меню
            while True:  # Зацикливаем запрос логина до правильного ввода
                user = get_input("Введите логин для запроса сервисного билета: ")
                if user != username:
                    print("Ошибка: Логин не совпадает с текущим пользователем. Попробуйте снова.")
                else:
                    break  # Если логин правильный, выходим из цикла
            while True:  # Запрашиваем название сервиса до правильного ввода
                service = get_input("Введите название сервиса: ")
                if service not in SERVICES:
                    print(f"Ошибка: Сервис '{service}' не существует. Попробуйте снова.")
                else:
                    break  # Если сервис существует, выходим из цикла
            tgt = TICKETS.get(f"{username}_tgt")
            if tgt:
                encrypted_ticket = get_service_ticket(username, tgt, service)
                if encrypted_ticket:
                    # Выводим сессионный ключ
                    session_key = SESSIONS.get(username)
                    print(f"Ваш сессионный ключ: {session_key}")
            else:
                print("Ошибка: Сначала получите TGT.")
        elif choice == "3":
            if not username:  # Если пользователь не аутентифицирован, запрашиваем логин
                print("Ошибка: Сначала выполните аутентификацию.")
                continue  # Возвращаемся к меню

            # Проверяем, что логин совпадает с текущим
            while True:
                user = get_input("Введите логин для доступа к сервису: ")
                if user != username:
                    print("Ошибка: Логин не совпадает с текущим пользователем. Попробуйте снова.")
                else:
                    break  # Если логин правильный, выходим из цикла

            # Попросим ввести сервис
            service = get_input("Введите название сервиса: ")

            # Проверяем, существует ли сервис в списке
            if service not in SERVICES:
                print(f"Ошибка: Сервис '{service}' не существует. Попробуйте снова.")
                continue  # Возвращаемся к меню

            # Проверяем, был ли выдан сервисный билет
            if f"{username}_tgt" not in TICKETS:
                print("Ошибка: Сначала получите TGT (пункт 1).")
                continue  # Возвращаемся к меню

            if f"{username}_{service}" not in TICKETS:
                print("Ошибка: Сначала получите сервисный билет (пункт 2).")
                continue  # Возвращаемся к меню

            # Если все условия выполнены, можно работать с сервисом
            ticket = TICKETS.get(f"{username}_{service}")
            encrypted_ticket = hash_value(f"{ticket}{SERVICE_KEY}") if ticket else None
            access_service(username, service, encrypted_ticket)
        elif choice == "4":
            if not username:  # Если пользователь не аутентифицирован, запрашиваем логин
                print("Ошибка: Сначала выполните аутентификацию.")
                continue  # Возвращаемся к меню
            while True:  # Зацикливаем запрос логина до правильного ввода
                user = get_input("Введите логин для чтения файла: ")
                if user != username:
                    print("Ошибка: Логин не совпадает с текущим пользователем. Попробуйте снова.")
                else:
                    break  # Если логин правильный, выходим из цикла
            read_protected_file(username)
        elif choice == "5":
            system_statistics()
        elif choice == "6":
            print("Выход из программы...")
            break
        else:
            print("Ошибка: Некорректный ввод. Введите число от 1 до 6.")

if __name__ == "__main__":
    main()

