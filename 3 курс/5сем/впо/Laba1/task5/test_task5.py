# -*- coding: windows-1251 -*-
import unittest
import os
from unittest.mock import patch
from task5 import find_files_with_extension

class TestFindFilesWithExtension(unittest.TestCase):

    def setUp(self):
        # Создаем временную тестовую директорию с файлами
        self.test_dir = 'test_dir'
        os.makedirs(self.test_dir, exist_ok=True)
        self.test_file_1 = os.path.join(self.test_dir, 'file1.txt')
        self.test_file_2 = os.path.join(self.test_dir, 'file2.py')
        self.test_file_3 = os.path.join(self.test_dir, 'subdir/file3.txt')
        os.makedirs(os.path.dirname(self.test_file_3), exist_ok=True)
        with open(self.test_file_1, 'w') as f:
            f.write("Test file 1")
        with open(self.test_file_2, 'w') as f:
            f.write("Test file 2")
        with open(self.test_file_3, 'w') as f:
            f.write("Test file 3")

    def tearDown(self):
        # Удаляем временную директорию после тестов
        for root, dirs, files in os.walk(self.test_dir, topdown=False):
            for name in files:
                os.remove(os.path.join(root, name))
            for name in dirs:
                os.rmdir(os.path.join(root, name))
        os.rmdir(self.test_dir)

    def test_find_txt_files(self):
        result = find_files_with_extension(self.test_dir, '.txt')
        self.assertIn(os.path.normpath(self.test_file_1), map(os.path.normpath, result))
        self.assertIn(os.path.normpath(self.test_file_3), map(os.path.normpath, result))
        self.assertNotIn(os.path.normpath(self.test_file_2), map(os.path.normpath, result))

    def test_find_py_files(self):
        result = find_files_with_extension(self.test_dir, '.py')
        self.assertIn(os.path.normpath(self.test_file_2), map(os.path.normpath, result))
        self.assertNotIn(os.path.normpath(self.test_file_1), map(os.path.normpath, result))
        self.assertNotIn(os.path.normpath(self.test_file_3), map(os.path.normpath, result))

    def test_invalid_directory(self):
        with self.assertRaises(ValueError):
            find_files_with_extension('invalid_dir', '.txt')

    def test_invalid_extension(self):
        with self.assertRaises(ValueError):
            find_files_with_extension(self.test_dir, 'txt')  # Ошибочное расширение без точки

if __name__ == "__main__":
    unittest.main()
