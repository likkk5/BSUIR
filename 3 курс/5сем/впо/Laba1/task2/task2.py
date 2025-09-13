# -*- coding: windows-1251 -*-
import re
def get_person_data():

    # ���� ����� � ���������
    while True:
        name = input("������� ���: ").strip()
        if name == "":
            print("���� '���' �� ����� ���� ������. ����������, ������� ���.")
        elif not re.match(r"^[A-Za-z�-��-���]{2,}$", name):  # �������� �� ����� �������� ��� ���������� �������� ������ 2+
            if len(name) < 2:
                print("��� ������ ��������� �� ����� 2 ����.")
            else:
                print("��� ������ ��������� ������ ����� � �� ��������� ����������� ��������.")
        else:
            break

    # ���� ������� � ���������
    while True:
        surname = input("������� �������: ").strip()
        if surname == "":
            print("���� '�������' �� ����� ���� ������. ����������, ������� �������.")
        elif not re.match(r"^[A-Za-z�-��-���]{2,}$", surname):  # �������� ���������� �����
            if len(surname) < 2:
                print("������� ������ ��������� �� ����� 2 ����.")
            else:
                print("������� ������ ��������� ������ ����� � �� ��������� ����������� ��������.")
        else:
            break

    # ���� �������� � ���������
    while True:
        age = input("������� �������: ").strip()
        if age == "":
            print("���� '�������' �� ����� ���� ������. ����������, ������� �������.")
        elif not re.match(r"^-?\d+$", age):  # �������� �� ����� ����� (����� ���� �������������)
            print("������� ������ ���� ����� ������.")
        else:
            age = int(age)
            if age <= 0:
                print("������� ������ ���� ������������� ������ ������ 0.")
            else:
                break

    return surname, name, age


def calculate_statistics(people):
    if not people:
        raise ValueError("��� ������ ��� ���������� ����������.")
    
    ages = [age for _, _, age in people]
    min_age = min(ages)
    max_age = max(ages)
    average_age = sum(ages) / len(ages)
    
    return min_age, max_age, average_age

def main():
    while True:
        people = []

        while True:
            try:
                person_data = get_person_data()
                people.append(person_data)
            except ValueError as e:
                print(e)
                continue

            exit_choice = input("������� 'e' ��� ���������� ����� ��� '�' ��� �����������: ").lower()
            if exit_choice == 'e':
                break
            elif exit_choice != '�':
                print("���������� ���� ������.")

        if not people:
            print("�� ���� ������� �� ������ ��������.")
            return

        print("\n������ �����:")
        for surname, name, age in people:
            print(f"{surname} {name} {age}")

        try:
            min_age, max_age, average_age = calculate_statistics(people)
            print("\n����������:")
            print(f"����� ����� �������: {min_age}")
            print(f"����� ������� �������: {max_age}")
            print(f"������� �������: {average_age:.2f}")
        except ValueError as e:
            print(e)

        choice = input("\n������ ������ ������ ����� (Y/N)? ").upper()
        if choice != 'Y':
            break

if __name__ == "__main__":
    main()
