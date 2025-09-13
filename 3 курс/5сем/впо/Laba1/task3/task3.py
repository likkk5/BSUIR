# -*- coding: windows-1251 -*-
def calculate_area(length, width):
    # ��������, ��� ������� ������ � ��� �����
    if not isinstance(length, (int, float)) or not isinstance(width, (int, float)):
        raise ValueError("����� � ������ ������ ���� �������.")
    if length <= 0 or width <= 0:
        raise ValueError("����� � ������ ������ ���� �������������� �������.")
    
    return length * width

def main():
    while True:
        try:

            # ���� ����� � ������ 
            length_input = input("������� ����� ��������������: ").strip()
            if not length_input:
                raise ValueError("����� �� ����� ���� ������ �������.")
            length = float(length_input)
            
            width_input = input("������� ������ ��������������: ").strip()
            if not width_input:
                raise ValueError("������ �� ����� ���� ������ �������.")
            width = float(width_input)
            
            # ���������� �������
            area = calculate_area(length, width)
            print(f"������� ��������������: {area}")
            break 
        
        except ValueError as e:
            print(f"������: {e}. ����������, ������� ���������� �������� ��������.")

if __name__ == "__main__":
    main()

