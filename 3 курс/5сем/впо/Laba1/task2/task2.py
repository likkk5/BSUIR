# -*- coding: windows-1251 -*-
import re
def get_person_data():

    # Ввод имени с проверкой
    while True:
        name = input("Введите имя: ").strip()
        if name == "":
            print("Поле 'Имя' не может быть пустым. Пожалуйста, введите имя.")
        elif not re.match(r"^[A-Za-zА-Яа-яЁё]{2,}$", name):  # Проверка на буквы русского или латинского алфавита длиной 2+
            if len(name) < 2:
                print("Имя должно содержать не менее 2 букв.")
            else:
                print("Имя должно содержать только буквы и не содержать специальных символов.")
        else:
            break

    # Ввод фамилии с проверкой
    while True:
        surname = input("Введите фамилию: ").strip()
        if surname == "":
            print("Поле 'Фамилия' не может быть пустым. Пожалуйста, введите фамилию.")
        elif not re.match(r"^[A-Za-zА-Яа-яЁё]{2,}$", surname):  # Проверка аналогична имени
            if len(surname) < 2:
                print("Фамилия должна содержать не менее 2 букв.")
            else:
                print("Фамилия должна содержать только буквы и не содержать специальных символов.")
        else:
            break

    # Ввод возраста с проверкой
    while True:
        age = input("Введите возраст: ").strip()
        if age == "":
            print("Поле 'Возраст' не может быть пустым. Пожалуйста, введите возраст.")
        elif not re.match(r"^-?\d+$", age):  # Проверка на целое число (может быть отрицательным)
            print("Возраст должен быть целым числом.")
        else:
            age = int(age)
            if age <= 0:
                print("Возраст должен быть положительным числом больше 0.")
            else:
                break

    return surname, name, age


def calculate_statistics(people):
    if not people:
        raise ValueError("Нет данных для вычисления статистики.")
    
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

            exit_choice = input("Введите 'e' для завершения ввода или 'с' для продолжения: ").lower()
            if exit_choice == 'e':
                break
            elif exit_choice != 'с':
                print("Продолжаем ввод данных.")

        if not people:
            print("Не было введено ни одного человека.")
            return

        print("\nСписок людей:")
        for surname, name, age in people:
            print(f"{surname} {name} {age}")

        try:
            min_age, max_age, average_age = calculate_statistics(people)
            print("\nСтатистика:")
            print(f"Самый малый возраст: {min_age}")
            print(f"Самый большой возраст: {max_age}")
            print(f"Средний возраст: {average_age:.2f}")
        except ValueError as e:
            print(e)

        choice = input("\nХотите ввести данные снова (Y/N)? ").upper()
        if choice != 'Y':
            break

if __name__ == "__main__":
    main()
