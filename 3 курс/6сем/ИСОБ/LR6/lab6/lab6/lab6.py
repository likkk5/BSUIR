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
    print(f"����������� SQL ������: {query}")
    with closing(conn.cursor()) as c:
        c.execute(query)
        return c.fetchall()

def safe_login(conn, login, password):
    query = "SELECT * FROM users WHERE login = ? AND password = ?"
    print(f"����������� SQL ������: {query}")
    with closing(conn.cursor()) as c:
        c.execute(query, (login, password))
        return c.fetchall()

def show_result(users):
    if users:
        print("[+]�������� ����! ������ ������������(�):")
        for user in users:
            print(f"ID: {user[0]}\n�����: {user[1]}\n")
    else:
        print("[!]������ �����: �������� ������� ������")


def main():
    conn = create_database()

    while True:
        print("������� ��� ������������:")
        print("�������������� ��������(������ ������ ������): ' OR '1'='1' --")
        print("�������������� ��������: admin' --")
        print("Error-based ��������(��������������): some' AND LENGTH(passport)>0 --")
        print("UNION-��������(��������������): ' UNION SELECT id, login, password FROM users --")
        print("������� ������(���������������) ��������: some' OR LENGTH(password)>3 --")
        print("�������� ������������� ������(���������������): user' AND SUBSTRING(password,1,1)='l' --")

        
        login = input("\n������� �����: ")
        password = input("������� ������: ")
        
        print("\n�������� �����:")
        print("1. ������������ �����")
        print("2. ���������� �����")
        mode = input("������� ����� ������: ")
        
        try:
            if mode == '1':
                user = unsafe_login(conn, login, password)
            elif mode == '2':
                user = safe_login(conn, login, password)
            else:
                print("������������ ����� ������.")
                continue

            show_result(user)

        except Exception as e:
            print(f"������: {e}")
        
        cont = input("\n������ ����������� �����? (��/���): ").strip().lower()
        if cont != '��':
            print("����� �� ���������.")
            break

if __name__ == "__main__":
    main()
