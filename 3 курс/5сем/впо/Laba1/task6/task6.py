#-*- coding: windows-1251 -*-
import os
import requests
from urllib.parse import urlparse
import argparse

def download_file(url, save_folder):
    try:
        # ���������, ��� URL ���������� � "http" ��� "https"
        if not url.startswith(('http://', 'https://')):
            raise ValueError("������������ URL. ����������� URL, ������������ � http:// ��� https://")

        # ��������� ��� ����� �� URL
        parsed_url = urlparse(url)
        file_name = os.path.basename(parsed_url.path)

        # ���������, ��� ���� ����� ���
        if not file_name:
            raise ValueError("���������� ���������� ��� ����� �� URL")

        # ������� �����, ���� ��� �� ����������
        if not os.path.exists(save_folder):
            os.makedirs(save_folder)

        # ������ ���� ��� ���������� �����
        file_path = os.path.join(save_folder, file_name)

        # ��������� ����
        print(f"�������� ����� � {url}...")
        response = requests.get(url, stream=True)

        # �������� ���������� �������
        if response.status_code != 200:
            raise Exception(f"������ ��� �������� �����: ������ {response.status_code}")

        # ���������� ���� �� ���� �� ������
        with open(file_path, 'wb') as file:
            for chunk in response.iter_content(chunk_size=8192):
                if chunk:
                    file.write(chunk)
        
        print(f"���� ������� �������� �� ����: {file_path}")
    except Exception as e:
        print(f"������: {e}")

if __name__ == "__main__":
    # ������� ������ ��� ��������� ������
    parser = argparse.ArgumentParser(description="���������� ����� � URL � ���������� ��� � ��������� �����.")
    parser.add_argument("url", help="URL ��� ���������� �����")
    parser.add_argument("save_folder", help="����� ��� ���������� �����")

    # ������ ���������
    args = parser.parse_args()

    # �������� ������� �������� ����� � �����������
    download_file(args.url, args.save_folder)

