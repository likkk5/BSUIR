# -*- coding: windows-1251-*-
import asyncio
import time
import ssl
import logging
from collections import defaultdict

# Конфигурация сервера
HOST = '0.0.0.0'
PORT = 8080
MAX_CONNECTIONS_PER_IP = 5
REQUEST_LIMIT_PER_SECOND = 5
IP_BLOCK_TIME = 60
BLOCK_INCREASE = 30
MAX_CONNECTION_TIME = 30
HEADER_TIMEOUT = 3
MIN_DATA_SIZE = 100

# Хранение данных о подключениях
active_connections = defaultdict(int)
request_counters = defaultdict(list)
blocked_ips = {}
failed_attempts = defaultdict(int)

# Логирование
logging.basicConfig(filename='server_security.log', level=logging.WARNING)

def log_attack(ip, reason):
    logging.warning(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] Атака с {ip}: {reason}")

async def safe_close(writer):
    """Безопасное закрытие соединения без ошибок."""
    try:
        if not writer.is_closing():
            writer.close()
            await writer.wait_closed()
    except ssl.SSLError as e:
        if "APPLICATION_DATA_AFTER_CLOSE_NOTIFY" in str(e):
            print(f"[SSL Warning] Игнорируем: {e}")  # Просто предупреждение, не критично
        else:
            logging.error(f"SSL ошибка при закрытии: {e}")
    except Exception as e:
        logging.error(f"Ошибка при закрытии соединения: {e}")

async def handle_client(reader, writer):
    addr = writer.get_extra_info('peername')
    ip = addr[0]

    # Проверка блокировки IP
    if ip in blocked_ips and time.time() < blocked_ips[ip]:
        print(f"[BLOCKED] {ip} заблокирован")
        log_attack(ip, "Доступ заблокирован")
        await safe_close(writer)
        return

    # Ограничение соединений
    if active_connections[ip] >= MAX_CONNECTIONS_PER_IP:
        print(f"[LIMIT] {ip} превышено число соединений")
        log_attack(ip, "Превышено количество соединений")
        await safe_close(writer)
        return

    active_connections[ip] += 1

    try:
        now = time.time()
        request_counters[ip] = [t for t in request_counters[ip] if now - t < 1]
        if len(request_counters[ip]) >= REQUEST_LIMIT_PER_SECOND:
            print(f"[RATE LIMIT] {ip} превышена частота запросов")
            failed_attempts[ip] += 1
            blocked_ips[ip] = time.time() + (IP_BLOCK_TIME + failed_attempts[ip] * BLOCK_INCREASE)
            log_attack(ip, "Превышение лимита запросов")
            await safe_close(writer)
            return

        request_counters[ip].append(now)

        start_time = time.time()
        while True:
            if time.time() - start_time > MAX_CONNECTION_TIME:
                print(f"[TIMEOUT] {ip} превышено максимальное время соединения")
                log_attack(ip, "Превышено максимальное время соединения")
                await safe_close(writer)
                return

            try:
                data = await asyncio.wait_for(reader.read(1024), timeout=HEADER_TIMEOUT)
            except asyncio.TimeoutError:
                print(f"[SLOWLORIS ATTEMPT] {ip}")
                log_attack(ip, "Slowloris атака")
                await safe_close(writer)
                return

            if not data:
                return

            data = data.decode('utf-8', errors='ignore')
            print(f"[REQUEST] {ip} запрос: {data}")

            data_size = len(data)
            while data_size < MIN_DATA_SIZE:
                try:
                    chunk = await asyncio.wait_for(reader.read(1024), timeout=5)
                    if not chunk:
                        break
                    data_size += len(chunk)
                except asyncio.TimeoutError:
                    print(f"[SLOWLORIS] {ip} отправил слишком мало данных")
                    log_attack(ip, "Отправил слишком мало данных")
                    await safe_close(writer)
                    return

            if '/favicon.ico' in data:
                response = b'HTTP/1.1 200 OK\r\nContent-Type: image/x-icon\r\nContent-Length: 0\r\nConnection: close\r\n\r\n'
                writer.write(response)
                await writer.drain()
                await safe_close(writer)
                return

            response = b'HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHello'
            writer.write(response)
            await writer.drain()

    except Exception as e:
        print(f"[ERROR] {ip}: {e}")
        logging.error(f"[ERROR] {ip}: {e}")

    finally:
        active_connections[ip] -= 1
        await safe_close(writer)

async def main():
    ssl_context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
    ssl_context.load_cert_chain(certfile="server_cert.pem", keyfile="server_key.pem")

    server = await asyncio.start_server(
        handle_client, HOST, PORT,
        ssl=ssl_context,
        backlog=50
    )

    addr = server.sockets[0].getsockname()
    print(f"Сервер запущен на {addr}")

    async with server:
        await server.serve_forever()

asyncio.run(main())
