# -*- coding: windows-1251 -*-

import hashlib
import os
import random
import time

# ������������ �������
TGS_KEY = "tgs_secret_key"
SERVICE_KEY = "service_secret_key"

# ���� ������ �������������
USER_DB = {
    "ksusha": "password123",
    "admin": "securepass"
}

SESSIONS = {}  # {username: session_key}
TICKETS = {}   # {ticket_id: ticket_data}

# ��������� ������ ��� ������
PROTECTED_FILES = {"protected_file.txt": "��� ���������� ����������� �����.\n" * 10}

# ��������� �������
SERVICES = {"file_access", "service1", "service2"}

# ������ �����, ���� �� ���
for filename, content in PROTECTED_FILES.items():
    if not os.path.exists(filename):
        with open(filename, "w", encoding="windows-1251") as file:
            file.write(content)

def hash_value(data):
    return hashlib.sha256(data.encode()).hexdigest()

def generate_session_key(prefix="key_"):
    return f"{prefix}{random.randint(1000, 9999)}"

def authenticate(username, password):
    # ������� ��������� ������� ������
    if username not in USER_DB:
        print("������: ��������� ����� �� ����������.")
        return None
    
    # ���� ����� ����������, ��������� ������
    if USER_DB[username] != password:
        print("������: �������� ������� ������.")
        return None

    # ���������� ���������� ���� ��� ��������������
    session_key = generate_session_key("auth_")
    SESSIONS[username] = session_key
    tgt = {"user": username, "key": session_key, "time": time.time()}
    encrypted_tgt = hash_value(f"{tgt}{TGS_KEY}")
    TICKETS[f"{username}_tgt"] = encrypted_tgt
    print(f"�������� ��������������. ��� TGT: {encrypted_tgt[:10]}...")
    print(f"��� ���������� ���� ��� ��������������: {session_key}")
    return encrypted_tgt

def get_service_ticket(username, tgt, service):
    if username not in SESSIONS or TICKETS.get(f"{username}_tgt") != tgt:
        print("������: ���������������� TGT. ��������� ��������������.")
        return None
    
    # ���������, ���������� �� ����� ������
    if service not in SERVICES:
        print(f"������: ������ '{service}' �� ����������. ���������� �����.")
        return None
    
    # ���������� ���������� ���� ��� �������
    service_key = generate_session_key("service_")
    ticket = {"user": username, "service": service, "key": service_key, "time": time.time()}
    encrypted_ticket = hash_value(f"{ticket}{SERVICE_KEY}")
    TICKETS[f"{username}_{service}"] = ticket
    print(f"��������� ����� ������� ����� ��� '{service}'. �����: {encrypted_ticket[:10]}...")
    print(f"��� ���������� ���� ��� ������� '{service}': {service_key}")
    return encrypted_ticket

def access_service(username, service, ticket):
    stored_ticket = TICKETS.get(f"{username}_{service}")
    if not stored_ticket or hash_value(f"{stored_ticket}{SERVICE_KEY}") != ticket:
        print("������: ����� �������������� ��� �����������. ��������� �����.")
        return False
    print(f"������ � ������� '{service}' ��������!")
    if service == "file_access":
        read_protected_file(username)
    return True

def read_protected_file(username):
    # ���������, ���� �� � ������������ ������ � ������� "file_access"
    if f"{username}_file_access" not in TICKETS:
        print("������: � ��� ��� ������� � ������� ������ ������. ��������� ��������� �����.")
        return

    print("��������� �����:", ", ".join(PROTECTED_FILES.keys()))
    filename = input("������� ��� ����� ��� ������: ").strip()
    if filename not in PROTECTED_FILES:
        print("������: ������ � ���������� ����� ��������!")
        return
    print(f"\n������ �����: {filename}\n")
    try:
        with open(filename, "r", encoding="windows-1251") as file:
            for line in file:
                print(line.strip())
    except Exception as e:
        print(f"������ ��� ������ �����: {e}")

def system_statistics():
    print("\n���������� �������:")
    print(f"�������������� ������������: {list(SESSIONS.keys())}")
    print(f"�������� ��������� ������: {TICKETS}")

def get_input(prompt, valid_values=None):
    while True:
        user_input = input(prompt).strip()
        if user_input.lower() == "exit":
            print("����� �� ���������.")
            exit()  # ��������� ���������
        if valid_values:
            if user_input in valid_values:
                return user_input
            else:
                print(f"������: ���� ������ ���� ����� �� ��������� ��������: {', '.join(valid_values)}.")
        elif user_input != "":
            return user_input
        else:
            print("������: ���� �� ����� ���� ������. ���������� �����.")

def main():
    username = None
    while True:
        print("\n������� ����")
        print("1. �������������� ������������")
        print("2. ������ ���������� ������")
        print("3. ������ � �������")
        print("4. �������� ������ �����")
        print("5. ���������� �������")
        print("6. �����")
        print("\n����� ����� �� ��������� ������� 'exit' � ����� ������.")
        choice = get_input("�������� �������� (1-6): ", valid_values=["1", "2", "3", "4", "5", "6", "exit"])

        if choice == "exit":
            print("����� �� ���������...")
            break
        
        if choice == "1":
            user = None
            while user not in USER_DB:
                user = get_input("������� �����: ")
                if user == "exit":
                    print("����� �� ���������...")
                    return
                if user not in USER_DB:
                    print("������: ��������� ����� �� ����������.")
            
            pwd = get_input("������� ������: ")
            tgt = authenticate(user, pwd)
            if tgt:
                username = user
                # ������� ���������� ����
                session_key = SESSIONS.get(username)
                print(f"��� ���������� ����: {session_key}")
        elif choice == "2":
            if not username:  # ���� ������������ �� ����������������, ����������� �����
                print("������: ������� ��������� ��������������.")
                continue  # ������������ � ����
            while True:  # ����������� ������ ������ �� ����������� �����
                user = get_input("������� ����� ��� ������� ���������� ������: ")
                if user != username:
                    print("������: ����� �� ��������� � ������� �������������. ���������� �����.")
                else:
                    break  # ���� ����� ����������, ������� �� �����
            while True:  # ����������� �������� ������� �� ����������� �����
                service = get_input("������� �������� �������: ")
                if service not in SERVICES:
                    print(f"������: ������ '{service}' �� ����������. ���������� �����.")
                else:
                    break  # ���� ������ ����������, ������� �� �����
            tgt = TICKETS.get(f"{username}_tgt")
            if tgt:
                encrypted_ticket = get_service_ticket(username, tgt, service)
                if encrypted_ticket:
                    # ������� ���������� ����
                    session_key = SESSIONS.get(username)
                    print(f"��� ���������� ����: {session_key}")
            else:
                print("������: ������� �������� TGT.")
        elif choice == "3":
            if not username:  # ���� ������������ �� ����������������, ����������� �����
                print("������: ������� ��������� ��������������.")
                continue  # ������������ � ����

            # ���������, ��� ����� ��������� � �������
            while True:
                user = get_input("������� ����� ��� ������� � �������: ")
                if user != username:
                    print("������: ����� �� ��������� � ������� �������������. ���������� �����.")
                else:
                    break  # ���� ����� ����������, ������� �� �����

            # �������� ������ ������
            service = get_input("������� �������� �������: ")

            # ���������, ���������� �� ������ � ������
            if service not in SERVICES:
                print(f"������: ������ '{service}' �� ����������. ���������� �����.")
                continue  # ������������ � ����

            # ���������, ��� �� ����� ��������� �����
            if f"{username}_tgt" not in TICKETS:
                print("������: ������� �������� TGT (����� 1).")
                continue  # ������������ � ����

            if f"{username}_{service}" not in TICKETS:
                print("������: ������� �������� ��������� ����� (����� 2).")
                continue  # ������������ � ����

            # ���� ��� ������� ���������, ����� �������� � ��������
            ticket = TICKETS.get(f"{username}_{service}")
            encrypted_ticket = hash_value(f"{ticket}{SERVICE_KEY}") if ticket else None
            access_service(username, service, encrypted_ticket)
        elif choice == "4":
            if not username:  # ���� ������������ �� ����������������, ����������� �����
                print("������: ������� ��������� ��������������.")
                continue  # ������������ � ����
            while True:  # ����������� ������ ������ �� ����������� �����
                user = get_input("������� ����� ��� ������ �����: ")
                if user != username:
                    print("������: ����� �� ��������� � ������� �������������. ���������� �����.")
                else:
                    break  # ���� ����� ����������, ������� �� �����
            read_protected_file(username)
        elif choice == "5":
            system_statistics()
        elif choice == "6":
            print("����� �� ���������...")
            break
        else:
            print("������: ������������ ����. ������� ����� �� 1 �� 6.")

if __name__ == "__main__":
    main()

