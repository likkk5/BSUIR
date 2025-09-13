import socket
import threading
from collections import defaultdict

# Конфигурация сервера
HOST = '0.0.0.0'  # Сервер слушает все IP-интерфейсы
PORT = 8088       # Порт для прослушивания
MAX_CONNECTIONS = 10  # Максимальное количество одновременных подключений
BACKLOG = 10      # Размер очереди соединений

# Глобальные переменные для управления подключениями
current_connections = 0  # Счетчик активных подключений
connection_lock = threading.Lock()  # Блокировка для работы с подключениями
failed_attempts = defaultdict(int)  # Счетчик неудачных попыток по IP
failed_lock = threading.Lock()  # Блокировка для работы с failed_attempts

def print_separator():
    print("-" * 120)

def handle_client(client_socket, addr):
    global current_connections
    try:
        with failed_lock:
            if failed_attempts[addr[0]] >= 3:
                client_socket.send("Your IP is blocked due to too many failed attempts.\n".encode())
                print(f"[-] {addr} is BLOCKED.")
                return

        client_socket.send("Enter password: ".encode())
        password = client_socket.recv(1024).decode().strip()

        if password == "key":
            client_socket.send("Login successful!\n".encode())
            print(f"[+] {addr} logged in successfully.")
            
            while True:
                client_socket.send("Enter message (or 'exit' to quit): ".encode())
                message = client_socket.recv(1024).decode().strip()

                if message.lower() == "exit":
                    client_socket.send("Goodbye!\n".encode())
                    print(f"[-] {addr} disconnected.")
                    break
                
                response = f"Server received: {message}\n"
                client_socket.send(response.encode())
                print(f"[>] {addr} sent: {message}")
        else:
            with failed_lock:
                failed_attempts[addr[0]] += 1
                if failed_attempts[addr[0]] >= 3:
                    client_socket.send("Too many failed attempts. Your IP is now blocked.\n".encode())
                    print(f"[-] {addr} is now BLOCKED due to repeated failures.")
                else:
                    client_socket.send("Invalid password.\n".encode())
                    print(f"[!] {addr} failed login attempt {failed_attempts[addr[0]]}.")

    except Exception as e:
        print(f"[!] Error handling {addr}: {e}")
    finally:
        client_socket.close()
        with connection_lock:
            current_connections -= 1
        print(f"[-] Connection closed from {addr}. Active connections: {current_connections}")

def main():
    global current_connections
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen(BACKLOG)
    print_separator()
    print(f"[+] Server is listening on {HOST}:{PORT}")
    print_separator()

    while True:
        client, addr = server.accept()
        print(f"[+] Connection accepted from {addr}")
        
        with connection_lock:
            if current_connections >= MAX_CONNECTIONS:
                print(f"[-] Too many connections! Rejecting {addr}")
                client.close()
                continue
            current_connections += 1
            print(f"[>] Active connections: {current_connections}")
        
        client_thread = threading.Thread(target=handle_client, args=(client, addr))
        client_thread.start()

if __name__ == "__main__":
    main()
