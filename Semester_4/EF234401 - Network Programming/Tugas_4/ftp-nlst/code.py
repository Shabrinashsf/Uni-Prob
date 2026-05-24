import sys
from ftplib import FTP
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def list_files(host, username, password):
    # Create FTP connection to host
    ftp = FTP(host)

    # Get and print welcome message
    welcome_msg = ftp.getwelcome()
    print(welcome_msg)

    # Login and print response
    login_msg = ftp.login(username, password)
    print(login_msg)

    # Get list of files and print
    files = ftp.nlst()
    print(f"Files: {files}")

    # Quit and print response
    quit_msg = ftp.quit()
    print(quit_msg)

    return files


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestListFiles(unittest.TestCase):
    @patch('__main__.FTP')
    def test_list_files(self, mock_ftp):
        host = 'localhost'
        username = 'user'
        password = '123'
        expected_files = ['file1.txt', 'file2.pdf', 'file3.png']
        expected_welcome_msg = "220-FileZilla Server 1.7.0\r\n220 Please visit https://filezilla-project.org/"
        expected_login_msg = "230 Login successful."
        expected_quit_msg = "221 Goodbye."

        ftp_instance = mock_ftp.return_value
        ftp_instance.getwelcome.return_value = expected_welcome_msg
        ftp_instance.login.return_value = expected_login_msg
        ftp_instance.nlst.return_value = expected_files
        ftp_instance.quit.return_value = expected_quit_msg

        result = list_files(host, username, password)

        mock_ftp.assert_called_once_with(host)
        ftp_instance.getwelcome.assert_called_once()
        ftp_instance.login.assert_called_once_with(username, password)
        print(f"login called with {ftp_instance.login.call_args}")
        ftp_instance.nlst.assert_called_once()
        print(f"nlst called with {ftp_instance.nlst.call_args}")
        ftp_instance.quit.assert_called_once()
        assert_equal(result, expected_files)
        assert_equal(ftp_instance.getwelcome(), expected_welcome_msg)
        assert_equal(ftp_instance.login(username, password), expected_login_msg)
        assert_equal(ftp_instance.nlst(), expected_files)
        assert_equal(ftp_instance.quit(), expected_quit_msg)


if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        host = 'localhost'
        username = 'user'
        password = '123'
        result = list_files(host, username, password)
        print(result)
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
