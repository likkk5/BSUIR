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
        self.assertEqual(min_age, 13, msg="����������� ������� ������ ���� 13.")
    
    def test_max_age(self):
        _, max_age, _ = calculate_statistics(self.people)
        self.assertEqual(max_age, 30, msg="������������ ������� ������ ���� 30.")
    
    def test_average_age(self):
        _, _, average_age = calculate_statistics(self.people)
        self.assertAlmostEqual(average_age, 26.00, places=2, 
                               msg="������� ������� ������ ���� �������������� 26.00 � ��������� �� ���� ������.")

class TestPeopleFunctions(unittest.TestCase):

    def test_calculate_statistics(self):
        people = [
            # ("Ivanov", "Ivan", 30),
            ("Petrov", "Petr", 19),
            ("Sidorov", "Sidr", 13)
        ]
        min_age, max_age, average_age = calculate_statistics(people)
        self.assertEqual(min_age, 19, msg="����������� ������� ������ ���� 13.")
        self.assertEqual(max_age, 33, msg="������������ ������� ������ ���� 30.") 
        self.assertAlmostEqual(average_age, 26.00, places=2, msg="������� ������� ������ ���� �������������� 26.00 � ��������� �� ���� ������.")

    def test_calculate_statistics2(self):
        people = [
            ("Petrov", "Petr", 19),
            ("Sidorov", "Sidr", 13)
        ]
        min_age, max_age, average_age = calculate_statistics(people)
         # ������ ��� �������� ��������� �� �������
        errors = []

        if min_age != 13:
            errors.append(f"����������� ������� ������ ���� 19, �� �������� {min_age}.")
        if max_age != 30:
            errors.append(f"������������ ������� ������ ���� 33, �� �������� {max_age}.")
        if not (round(average_age, 2) == 26.00):
            errors.append(f"������� ������� ������ ���� �������������� 26.00 � ��������� �� ���� ������, �� �������� {average_age}.")

        if errors:
            self.fail("������ � �����:\n" + "\n".join(errors))

    def test_calculate_statistics_empty_list(self):
        with self.assertRaises(ValueError):
            calculate_statistics([])

    def test_get_person_data_valid(self):
        """���� � ����������� ���������� ��� ���� �����."""
        inputs = ["Ivan", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs):
            result = get_person_data()
            self.assertEqual(result, ("Ivanov", "Ivan", 30))

    # ����� ��� �����
    def test_get_person_data_invalid_name_short(self):
        """����: ��� ������ 2 ��������."""
        inputs = ["I", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs * 2):  # ������ ��� �������� ���������� �����
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_name_symbols(self):
        """����: ��� �������� ������������ �������."""
        inputs = ["Iv@an", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_name_digits(self):
        """����: ��� �������� �����."""
        inputs = ["Ivan1", "Ivanov", "30"]
        with patch('builtins.input', side_effect=inputs):
            with self.assertRaises(ValueError):
                get_person_data()

    # ����� ��� �������
    def test_get_person_data_invalid_surname_short(self):
        """����: ������� ������ 2 ��������."""
        inputs = ["Ivan", "I", "30"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_surname_symbols(self):
        """����: ������� �������� ������������ �������."""
        inputs = ["Ivan", "Iv@nov", "30"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_surname_digits(self):
        """����: ������� �������� �����."""
        inputs = ["Ivan", "Ivan2", "30"]
        with patch('builtins.input', side_effect=inputs):
            with self.assertRaises(ValueError):
                get_person_data()

    # ����� ��� ��������
    def test_get_person_data_invalid_age_non_numeric(self):
        """����: ������� �� �������� ������."""
        inputs = ["Ivan", "Ivanov", "abc"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_age_negative(self):
        """����: ������� ������������� �����."""
        inputs = ["Ivan", "Ivanov", "-25"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

    def test_get_person_data_invalid_age_zero(self):
        """����: ������� ����� ����."""
        inputs = ["Ivan", "Ivanov", "0"]
        with patch('builtins.input', side_effect=inputs * 2):
            with self.assertRaises(ValueError):
                get_person_data()

if __name__ == "__main__":
    unittest.main()


