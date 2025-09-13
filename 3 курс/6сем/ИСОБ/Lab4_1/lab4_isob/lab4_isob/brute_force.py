import socket
import time

def brute_force_attack():
    for attempt in range(1, 6):
        try:
            # Создаем новое подключение
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.connect(('localhost', 8088))
            
            # Получаем приветственное сообщение от сервера
            response = client.recv(1024).decode()
            print(f"[{attempt}] Server: {response.strip()}")

            # Отправляем неправильный пароль
            client.send(b"password\n")
            
            # Получаем ответ от сервера
            response = client.recv(1024).decode()
            print(f"[{attempt}] Server Response: {response.strip()}")

            # Закрываем соединение
            client.close()
            
            # Добавляем задержку между попытками
            time.sleep(1)
            
        except ConnectionAbortedError:
            print(f"[{attempt}] Connection aborted by the server!")
        except ConnectionResetError:
            print(f"[{attempt}] Connection reset by the server!")
        except Exception as e:
            print(f"[{attempt}] Error: {e}")
        finally:
            if 'client' in locals():
                client.close()

brute_force_attack()
