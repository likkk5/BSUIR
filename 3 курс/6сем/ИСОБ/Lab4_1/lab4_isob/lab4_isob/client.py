import socket
import time

def print_separator():
    print("-" * 120)  

def log(tag, message):
    """Форматированный вывод с тегами"""
    print(f" [{tag}] {message}")

def legitimate_client():
    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(('localhost', 8088))  
        
        # Получаем приветствие от сервера
        response = client.recv(1024).decode()
        print_separator()
        log("SERVER", response)
        
        # Вводим пароль
        password = input(" [INPUT] Enter password: ")
        client.send(password.encode())
        
        # Ответ от сервера
        response = client.recv(1024).decode()
        print_separator()
        log("SERVER", response)
        
        # Если вход успешен, начинаем диалог
        if "successful" in response:
            while True:
                # Получаем запрос на ввод сообщения
                response = client.recv(1024).decode()
                print_separator()
                log("SERVER", response)
                
                # Вводим сообщение
                message = input(" [MESSAGE] Your message: ")
                client.send(message.encode())

                if message.lower() == "exit":
                    log("EXIT", "Disconnecting from server...")
                    break
                
                # Ответ сервера
                response = client.recv(1024).decode()
                print_separator()
                log("SERVER", response)
                time.sleep(0.5)  

    except Exception as e:
        log("ERROR", f"{e}")
    finally:
        client.close()  
        log("CONNECTION", "Closed.")

if __name__ == "__main__":
    legitimate_client()
