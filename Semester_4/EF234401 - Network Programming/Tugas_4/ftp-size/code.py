import sys
from ftplib import FTP
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def get_file_size(host, username, password, filename):
    ftp = FTP(host)
    welcome_msg = ftp.getwelcome()
    print(welcome_msg)
    login_msg = ftp.login(username, password)
    print(login_msg)
    size = ftp.size(filename)
    quit_msg = ftp.quit()
    print(quit_msg)
    return f"File {filename} has size {size} bytes."


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestGetFileSize(unittest.TestCase):
    @patch('__main__.FTP')
    def test_get_file_size(self, mock_ftp):
        host = 'localhost'
        username = 'user'
        password = '123'
        filename = 'report.txt'
        expected_size = 1024
        expected_result = "File report.txt has size 1024 bytes."
        expected_welcome_msg = "220-FileZilla Server 1.7.0\r\n220 Please visit https://filezilla-project.org/"
        expected_login_msg = "230 Login successful."
        expected_quit_msg = "221 Goodbye."

        ftp_instance = mock_ftp.return_value
        ftp_instance.getwelcome.return_value = expected_welcome_msg
        ftp_instance.login.return_value = expected_login_msg
        ftp_instance.size.return_value = expected_size
        ftp_instance.quit.return_value = expected_quit_msg

        result = get_file_size(host, username, password, filename)

        mock_ftp.assert_called_once_with(host)
        ftp_instance.getwelcome.assert_called_once()
        ftp_instance.login.assert_called_once_with(username, password)
        print(f"login called with {ftp_instance.login.call_args}")
        ftp_instance.size.assert_called_once_with(filename)
        print(f"size called with {ftp_instance.size.call_args}")
        ftp_instance.quit.assert_called_once()
        assert_equal(result, expected_result)
        assert_equal(ftp_instance.getwelcome(), expected_welcome_msg)
        assert_equal(ftp_instance.login(username, password), expected_login_msg)
        assert_equal(ftp_instance.size(filename), expected_size)
        assert_equal(ftp_instance.quit(), expected_quit_msg)


if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        host = 'localhost'
        username = 'user'
        password = '123'
        filename = 'report.txt'
        result = get_file_size(host, username, password, filename)
        print(result)
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
