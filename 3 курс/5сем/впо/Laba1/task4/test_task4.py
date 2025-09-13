# -*- coding: windows-1251 -*-
import unittest

from task4 import generate_html_table

class Test_test_task4(unittest.TestCase):

    def test_table_structure(self):
        """Test if the HTML content is generated correctly for a small table"""
        html = generate_html_table(rows=3, cols=2)
        self.assertIn('<html>', html)
        self.assertIn('<head>', html)
        self.assertIn('<body>', html)
        self.assertIn("<table>", html)
        self.assertIn("<tr style=", html)
        self.assertIn("<td>Row 1, Col 1</td>", html)
        self.assertIn("</table>", html)
        self.assertIn('</html>', html)
        
    def test_correct_number_of_rows(self):
        # Проверяем, что генерируется правильное количество строк
        rows = 4
        cols = 3
        html = generate_html_table(rows=rows, cols=cols)
        
        # Подсчитываем количество строк <tr>
        self.assertEqual(html.count('<tr '), rows)
    
    def test_correct_number_of_columns(self):
        # Проверяем, что в каждой строке правильное количество столбцов
        rows = 3
        cols = 4
        html = generate_html_table(rows=rows, cols=cols)
        
        # Подсчитываем количество столбцов <td> на каждую строку
        self.assertEqual(html.count('<td>'), rows * cols)

    def test_invalid_input(self):
        """Test if invalid input raises ValueError"""
        with self.assertRaises(ValueError):
            generate_html_table(-1, 5)  # Invalid number of rows
        with self.assertRaises(ValueError):
            generate_html_table(5, 0)   # Invalid number of columns
        with self.assertRaises(ValueError):
            generate_html_table("ten", 5)  # Non-integer input for rows

    def test_minimum_table(self):
        """Test the smallest possible valid table"""
        html = generate_html_table(1, 1)
        self.assertIn("<td>Row 1, Col 1</td>", html)
        self.assertIn("<tr style=", html)    
        
    def test_variable_size(self):
        #Проверяем корректную работу с разными размерами таблицы
        html_small = generate_html_table(rows=2, cols=2)
        self.assertIn('<td>Row 1, Col 1</td>', html_small)
        self.assertIn('<td>Row 2, Col 2</td>', html_small)

        html_large = generate_html_table(rows=5, cols=3)
        self.assertIn('<td>Row 5, Col 3</td>', html_large)

    def test_single_row_color(self):
        """Test if the color does not change for a single row"""
        html = generate_html_table(1, 3)
        self.assertIn('background-color: rgb(255, 255, 255);', html)  # Only white

if __name__ == '__main__':
    unittest.main()



