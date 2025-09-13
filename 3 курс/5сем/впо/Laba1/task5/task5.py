# -*- coding: windows-1251 -*-
import os
import argparse
import sys

def find_files_with_extension(directory, extension):
    """�������� �� ����������� � ���������� ����� � ��������� �����������."""
    if not os.path.isdir(directory):
        raise ValueError(f"������: ���������� {directory} �� ����������.")

    if not extension.startswith('.') or len(extension) <= 1:
        raise ValueError(f"������: ������������ ���������� {extension}. ��� ������ ���������� � ����� (��������, .txt).")

    result = []
    extension = extension.lower() #�������� � ������� �������
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.lower().endswith(extension):
                result.append(os.path.normpath(os.path.join(root, file)))
    return result

if __name__ == "__main__":
    # ������� ������ ��� ���������� ��������� ������
    parser = argparse.ArgumentParser(description="����� ������ � ��������� �����������.")
    
    # �������� ��� ����������
    parser.add_argument("directory", help="���������� ��� ������ ������")
    
    # �������� ��� ���������� ������
    parser.add_argument("extension", help="���������� ������ (��������, .txt)")
    
    # �������� ��������� ��������� ������
    args = parser.parse_args()

    try:
        # ����� ������ � ����� �� �� �����
        files = find_files_with_extension(args.directory, args.extension)
        if files:
            for file in files:
                print(file)
        else:
            print(f"����� � ����������� '{args.extension}' �� ������� � ���������� '{args.directory}'.")
    except ValueError as e:
        print(e)
        sys.exit(1)
