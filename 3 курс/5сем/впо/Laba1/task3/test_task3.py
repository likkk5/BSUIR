import unittest
from io import StringIO
import sys
from unittest.mock import patch

from task3 import calculate_area

class Test_test_task3(unittest.TestCase):

    def test_valid_inputs(self):
        self.assertAlmostEqual(calculate_area(5, 10), 50)
        self.assertAlmostEqual(calculate_area(7.5, 3.2), 24.0)

    def test_non_positive_inputs(self):
        with self.assertRaises(ValueError):
            calculate_area(-5, 10)
        with self.assertRaises(ValueError):
            calculate_area(5, -10)
        with self.assertRaises(ValueError):
            calculate_area(0, 10)
        with self.assertRaises(ValueError):
            calculate_area(5, 0)

    def test_invalid_inputs(self):
        with self.assertRaises(ValueError):
            calculate_area('five', 10)
        with self.assertRaises(ValueError):
            calculate_area(5, 'ten')

    def test_edge_cases(self):
        # self.assertAlmostEqual(calculate_area(1e-10, 1e10), 1e0)
        # self.assertAlmostEqual(calculate_area(1e10, 1e-10), 1e0)  
        self.assertAlmostEqual(calculate_area(9,9), 81)

if __name__ == "__main__":
    unittest.main()