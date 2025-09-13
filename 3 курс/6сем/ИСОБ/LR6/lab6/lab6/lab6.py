#coding: windows-1251
import sqlite3
from contextlib import closing


def create_database():
    conn = sqlite3.connect(':memory:')
    with closing(conn.cursor()) as c:
        c.execute('''CREATE TABLE users (
                    id INTEGER PRIMARY KEY,
                    login TEXT NOT NULL,
                    password TEXT NOT NULL)''')
        c.execute("INSERT INTO users (login, password) VALUES ('admin', 'key')")
        c.execute("INSERT INTO users (login, password) VALUES ('user', 'lishykksu')")
        conn.commit()
    return conn

def unsafe_login(conn, login, password):
    query = f"SELECT * FROM users WHERE login = '{login}' AND password = '{password}'"
    print(f"Выполненный SQL запрос: {query}")
    with closing(conn.cursor()) as c:
        c.execute(query)
        return c.fetchall()

def safe_login(conn, login, password):
    query = "SELECT * FROM users WHERE login = ? AND password = ?"
    print(f"Выполненный SQL запрос: {query}")
    with closing(conn.cursor()) as c:
        c.execute(query, (login, password))
        return c.fetchall()

def show_result(users):
    if users:
        print("[+]Успешный вход! Найден пользователь(и):")
        for user in users:
            print(f"ID: {user[0]}\nЛогин: {user[1]}\n")
    else:
        print("[!]Ошибка входа: неверные учетные данные")


def main():
    conn = create_database()

    while True:
        print("Примеры для тестирования:")
        print("Внутриполосная инъекция(всегда верный запрос): ' OR '1'='1' --")
        print("Внутриполосная инъекция: admin' --")
        print("Error-based инъекция(внутриполосная): some' AND LENGTH(passport)>0 --")
        print("UNION-инъекция(внутриполосная): ' UNION SELECT id, login, password FROM users --")
        print("Булевая слепая(инференциальная) инъекция: some' OR LENGTH(password)>3 --")
        print("Успешное распознавание пароля(инференциальная): user' AND SUBSTRING(password,1,1)='l' --")

        
        login = input("\nВведите логин: ")
        password = input("Введите пароль: ")
        
        print("\nВыберите режим:")
        print("1. Небезопасный режим")
        print("2. Безопасный режим")
        mode = input("Введите номер режима: ")
        
        try:
            if mode == '1':
                user = unsafe_login(conn, login, password)
            elif mode == '2':
                user = safe_login(conn, login, password)
            else:
                print("Некорректный выбор режима.")
                continue

            show_result(user)

        except Exception as e:
            print(f"Ошибка: {e}")
        
        cont = input("\nХотите попробовать снова? (да/нет): ").strip().lower()
        if cont != 'да':
            print("Выход из программы.")
            break

if __name__ == "__main__":
    main()
