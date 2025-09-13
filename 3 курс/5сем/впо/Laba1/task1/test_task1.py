import random
import unittest
from unittest.mock import patch
from io import StringIO
from task1 import generate_exclamation_string, main

class TestGenerateExclamationString(unittest.TestCase):

    def test_generate_exclamation_string_length(self):
        """Test if the length of the generated string is within the expected range."""
        result = generate_exclamation_string()
        self.assertTrue(5 <= len(result) <= 50, "Length of string should be between 5 and 50.")

    def test_generate_exclamation_string_content(self):
        """Test if the generated string only contains exclamation marks."""
        result = generate_exclamation_string()
        self.assertTrue(all(char == '!' for char in result), "String should only contain exclamation marks.")

    def test_generate_exclamation_string_output_type(self):
        """Test if the output is a string."""
        result = generate_exclamation_string()
        self.assertIsInstance(result, str, "Output should be a string.")

class TestMainFunction(unittest.TestCase):

    @patch('sys.stdout', new_callable=StringIO)
    def test_main_output(self, mock_stdout):
        """Test the output of the main function."""
        main()
        output = mock_stdout.getvalue().strip().splitlines()
        
        # Check if the first line is "Hello, world!"
        self.assertEqual(output[0], "Hello, world!")
        
        # Check if the second line is "Andhiagain!"
        self.assertEqual(output[1], "Andhiagain!")
        
        # Check if the third line is the exclamation string
        exclamation_string = output[2]
        self.assertTrue(5 <= len(exclamation_string) <= 50, "Exclamation string should be between 5 and 50 characters long.")
        self.assertTrue(all(char == '!' for char in exclamation_string), "Exclamation string should only contain '!'.")

if __name__ == '__main__':
    unittest.main()
