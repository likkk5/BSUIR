# -*- coding: windows-1251 -*-
import unittest
from unittest import mock
from unittest.mock import patch

from task2 import get_person_data, calculate_statistics

class TestCalculateStatistics(unittest.TestCase):
    def setUp(self):

        self.people = [
            ("Petrov", "Petr", 19),
            ("Sidorov", "Sidr", 13)
        ]

    def test_min_age(self):
        min_age, _, _ = calculate_statistics(self.people)
        self.assertEqual(min_age, 13, msg="Минимальный возраст должен быть 13.")
    
    def test_max_age(self):
        _, max_age, _ = calculate_statistics(self.people)
        self.assertEqual(max_age, 30, msg="Максимальный возраст должен быть 30.")
    
    def test_average_age(self):
        _, _, average_age = calculate_statistics(self.people)
        self.assertAlmostEqual(average_age, 26.00, places=2, 
                               msg="Средний возраст должен быть приблизительно 26.00 с точностью до двух знаков.")

class TestPeopleFunctions(unittest.TestCase):

    def test_calculate_statistics(self):
        people = [
            # ("Ivanov", "Ivan", 30),
            ("Petrov", "Petr", 19),
            ("Sidorov", "Sidr", 13)
        ]
        min_age, max_age, average_age = calculate_statistics(people)
        self.assertEqual(min_age, 19, msg="Минимальный возраст должен быть 13.")
        self.assertEqual(max_age, 33, msg="Максимальный возраст должен быть 30.") 
        self.assertAlmostEqual(average_age, 26.00, places=2, msg="Средний возраст должен быть приблизительно 26.00 с точностью до двух знаков.")

    def test_calculate_statistics2(self):
        people = [
            ("Petrov", "Petr", 19),
            ("Sidorov", "Sidr", 13)
        ]
        min_age, max_age, average_age = calculate_statistics(people)
         # Список для хранения сообщений об ошибках
        errors = []

        if min_age != 13:
            errors.append(f"Минимальный возраст должен быть 19, но получено {min_age}.")
        if max_age != 30:
            errors.append(f"Максимальный возраст должен быть 33, но получено {max_age}.")
        if not (round(average_age, 2) == 26.00):
            errors.append(f"Средний возраст должен быть приблизительно 26.00 с точностью до двух знаков, но получено {average_age}.")

        if errors:
            self.fail("Ошибки в тесте:\n" + "\n".join(errors))

    def test_calculate_statistics_empty_list(self):
        with self.assertRaises(ValueError):
            calculate_statistics([])

    def test_get_person_data_valid(self):
        """Тест с корректными значениями для всех полей."""
        inputs = ["Ivan", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs):
            result = get_person_data()
            self.assertEqual(result, ("Ivanov", "Ivan", 30))

    # Тесты для имени
    def test_get_person_data_invalid_name_short(self):
        """Тест: имя короче 2 символов."""
        inputs = ["I", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs * 2):  # Повтор для проверки повторного ввода
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_name_symbols(self):
        """Тест: имя содержит недопустимые символы."""
        inputs = ["Iv@an", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_name_digits(self):
        """Тест: имя содержит цифры."""
        inputs = ["Ivan1", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs):
            with self.assertRaises(ValueError):
                get_person_data()

    # Тесты для фамилии
    def test_get_person_data_invalid_surname_short(self):
        """Тест: фамилия короче 2 символов."""
        inputs = ["Ivan", "I", "30"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_surname_symbols(self):
        """Тест: фамилия содержит недопустимые символы."""
        inputs = ["Ivan", "Iv@nov", "30"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_surname_digits(self):
        """Тест: фамилия содержит цифры."""
        inputs = ["Ivan", "Ivan2", "30"]
        with patch('builtins.input', side_effect=inputs):
            with self.assertRaises(ValueError):
                get_person_data()

    # Тесты для возраста
    def test_get_person_data_invalid_age_non_numeric(self):
        """Тест: возраст не является числом."""
        inputs = ["Ivan", "Ivanov", "abc"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_age_negative(self):
        """Тест: возраст отрицательное число."""
        inputs = ["Ivan", "Ivanov", "-25"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_age_zero(self):
        """Тест: возраст равен нулю."""
        inputs = ["Ivan", "Ivanov", "0"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

if __name__ == "__main__":
    unittest.main()


