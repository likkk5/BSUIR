# -*- coding: windows-1251 -*-
import unittest
from unittest.mock import patch, mock_open, MagicMock
import os
import requests

from task6 import download_file

class TestDownloadFile(unittest.TestCase):

    @patch('os.makedirs')
    @patch('os.path.exists', return_value=False)
    @patch('requests.get')
    @patch('builtins.open', new_callable=mock_open)
    def test_download_file(self, mock_open_file, mock_requests_get, mock_exists, mock_makedirs):
        """
        ���������, ��� download_file ��������� ��������� ���� � ��������� ���
        � ��������� �����.
        """
        # ������ �������� ����� �� requests.get
        mock_response = mock_requests_get.return_value
        mock_response.status_code = 200
        mock_response.iter_content = lambda chunk_size: [b'data_chunk']

        # ��������� ������� download_file
        url = 'http://validurl.com/file.txt'
        save_folder = '/valid/folder'
        download_file(url, save_folder)

        # ���������, ��� requests.get ��� ������ � ���������� URL
        mock_requests_get.assert_called_once_with(url, stream=True)

        # ���������, ��� ���� ������� �����
        mock_makedirs.assert_called_once_with(save_folder)

        # ���������, ��� ���� ��� ������� � ��������� �����
        mock_open_file.assert_called_once_with(os.path.join(save_folder, 'file.txt'), 'wb')

        # ���������, ��� ���������� ���� �������� � ����
        mock_open_file().write.assert_called_with(b'data_chunk')

    @patch('requests.get')
    def test_download_file_invalid_status_code(self, mock_requests_get):
        """
        ���������, ��� download_file ������� ������, ���� ��� ������ �� �������
        �� ����� 200.
        """
        # ������ ���������� ����� �� requests.get
        mock_response = mock_requests_get.return_value
        mock_response.status_code = 404

        # ������������� ����� ����� print
        with patch('builtins.print') as mock_print:
            url = 'http://invalidurl.com/file.txt'
            save_folder = '/valid/folder'
            download_file(url, save_folder)

            # ���������, ��� ��������� ��������� �� ������
            mock_print.assert_any_call("������: ������ ��� �������� �����: ������ 404")

    @patch('requests.get', side_effect=requests.exceptions.RequestException)
    def test_download_file_request_exception(self, mock_requests_get):
        """
        ���������, ��� download_file ������� ��������� �� ������ ��� �������������
        ���������� � �������.
        """
        # ������������� ����� ����� print
        with patch('builtins.print') as mock_print:
            url = 'http://invalidurl.com/file.txt'
            save_folder = '/valid/folder'
            download_file(url, save_folder)

            # ���������, ��� ��������� ��������� �� ������
            mock_print.assert_any_call("������: ")

if __name__ == '__main__':
    unittest.main()
