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
        Тестирует, что download_file корректно загружает файл и сохраняет его
        в указанную папку.
        """
        # Мокаем успешный ответ от requests.get
        mock_response = mock_requests_get.return_value
        mock_response.status_code = 200
        mock_response.iter_content = lambda chunk_size: [b'data_chunk']

        # Тестируем функцию download_file
        url = 'http://validurl.com/file.txt'
        save_folder = '/valid/folder'
        download_file(url, save_folder)

        # Проверяем, что requests.get был вызван с правильным URL
        mock_requests_get.assert_called_once_with(url, stream=True)

        # Проверяем, что была создана папка
        mock_makedirs.assert_called_once_with(save_folder)

        # Проверяем, что файл был записан в указанное место
        mock_open_file.assert_called_once_with(os.path.join(save_folder, 'file.txt'), 'wb')

        # Проверяем, что содержимое было записано в файл
        mock_open_file().write.assert_called_with(b'data_chunk')

    @patch('requests.get')
    def test_download_file_invalid_status_code(self, mock_requests_get):
        """
        Тестирует, что download_file выводит ошибку, если код ответа от сервера
        не равен 200.
        """
        # Мокаем неуспешный ответ от requests.get
        mock_response = mock_requests_get.return_value
        mock_response.status_code = 404

        # Перехватываем вывод через print
        with patch('builtins.print') as mock_print:
            url = 'http://invalidurl.com/file.txt'
            save_folder = '/valid/folder'
            download_file(url, save_folder)

            # Проверяем, что выводится сообщение об ошибке
            mock_print.assert_any_call("Ошибка: Ошибка при загрузке файла: статус 404")

    @patch('requests.get', side_effect=requests.exceptions.RequestException)
    def test_download_file_request_exception(self, mock_requests_get):
        """
        Тестирует, что download_file выводит сообщение об ошибке при возникновении
        исключения в запросе.
        """
        # Перехватываем вывод через print
        with patch('builtins.print') as mock_print:
            url = 'http://invalidurl.com/file.txt'
            save_folder = '/valid/folder'
            download_file(url, save_folder)

            # Проверяем, что выводится сообщение об ошибке
            mock_print.assert_any_call("Ошибка: ")

if __name__ == '__main__':
    unittest.main()
