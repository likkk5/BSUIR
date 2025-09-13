class FileReader:
    """A class to read text from a file."""
    def __init__(self, filename):
        """
        Initialize the FileReader object with the given filename.

        Parameters:
        filename (str): The name of the file to read.

        Returns:
        None
        """
        self.filename = filename

    def read_text(self):
        """
        Read the text from the file.

        Returns:
        str: The text read from the file.
        None: If the file is not found or an error occurs.
        """
        try:
            with open(self.filename, 'r', encoding='utf-8') as file: #менеджер контекста, объект реализующий одноименный протокол, что позвол€ют использовать такой синтаксис
                text = file.read()
            return text
        except FileNotFoundError:
            print("File not found!")
            return None
        except Exception as e:
            print("An error occurred:", e)
            return None

