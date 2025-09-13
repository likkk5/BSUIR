import zipfile
import os

class FileArchiver:
    """A class to create a zip archive."""
    @staticmethod
    def create_archive(source_filename, target_filename):
        """
        Create a zip archive containing the source file.

        Parameters:
        source_filename (str): The name of the source file to be archived.
        target_filename (str): The name of the target zip archive file to create.

        Returns:
        None
        """
        with zipfile.ZipFile(target_filename, 'w') as archive:
            archive.write(source_filename, os.path.basename(source_filename))