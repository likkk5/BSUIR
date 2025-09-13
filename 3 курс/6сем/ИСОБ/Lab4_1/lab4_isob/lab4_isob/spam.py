import socket
import threading
import time

# Адрес сервера
SERVER_HOST = 'localhost'
SERVER_PORT = 8088

# Количество клиентов, которые попытаются подключиться
CLIENTS_COUNT = 1500

# Верный пароль для аутентификации
PASSWORD = 'key'

# Функция для подключения клиента к серверу
def connect_client(client_id):
    try:
        # Создаем сокет
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((SERVER_HOST, SERVER_PORT))
        print(f"[+] [Client {client_id}] Connected to server.")

        # Получаем приветственное сообщение от сервера
        response = client_socket.recv(1024).decode().strip()
        print(f"[>] [Client {client_id}] Server: {response}")

        # Отправляем верный пароль
        client_socket.send(f"{PASSWORD}\n".encode())
        response = client_socket.recv(1024).decode().strip()
        print(f"[!] [Client {client_id}] Server Response: {response}")

        # Если аутентификация успешна, поддерживаем соединение
        if "successful" in response:
            print(f"[+] [Client {client_id}] Authentication successful. Keeping connection alive.")
            while True:
                # Получаем запрос на ввод сообщения
                response = client_socket.recv(1024).decode().strip()
                print(f"[>] [Client {client_id}] Server: {response}")

                # Отправляем сообщение
                message = f"Hello from client {client_id}"
                client_socket.send(f"{message}\n".encode())
                print(f"[<] [Client {client_id}] Sent: {message}")

                # Ждем некоторое время перед отправкой следующего сообщения
                time.sleep(15)
        else:
            print(f"[-] [Client {client_id}] Authentication failed.")

    except Exception as e:
        print(f"[!] [Client {client_id}] Error: {e}")
    finally:
        # Закрываем соединение
        client_socket.close()
        print(f"[-] [Client {client_id}] Disconnected from server.")

# Создаем и запускаем клиентов
threads = []
for i in range(CLIENTS_COUNT):
    thread = threading.Thread(target=connect_client, args=(i + 1,))
    threads.append(thread)
    thread.start()
    time.sleep(1)  # Небольшая задержка между подключениями

# Ожидаем завершения всех потоков
for thread in threads:
    thread.join()

print("[+] All clients finished.")
