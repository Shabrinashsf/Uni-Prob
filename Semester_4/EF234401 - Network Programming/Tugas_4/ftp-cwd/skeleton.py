import sys
from ftplib import FTP
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def change_directory(host, username, password, path):
    # Create FTP connection to host
    ftp = ?

    # Get and print welcome message
    welcome_msg = ?
    print(welcome_msg)

    # Login and print response
    login_msg = ?
    print(login_msg)

    # Change directory and print response
    cwd_msg = ?
    print(cwd_msg)

    # Quit and print response
    quit_msg = ?
    print(quit_msg)

    return f"Changed directory to {path} successfully."


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestChangeDirectory(unittest.TestCase):
    @patch('__main__.FTP')
    def test_change_directory(self, mock_ftp):
        host = 'localhost'
        username = 'user'
        password = '123'
        path = '/uploads'
        expected_result = "Changed directory to /uploads successfully."
        expected_welcome_msg = "220-FileZilla Server 1.7.0\r\n220 Please visit https://filezilla-project.org/"
        expected_login_msg = "230 Login successful."
        expected_cwd_msg = "250 CWD command successful."
        expected_quit_msg = "221 Goodbye."

        ftp_instance = mock_ftp.return_value
        ftp_instance.getwelcome.return_value = expected_welcome_msg
        ftp_instance.login.return_value = expected_login_msg
        ftp_instance.cwd.return_value = expected_cwd_msg
        ftp_instance.quit.return_value = expected_quit_msg

        result = change_directory(host, username, password, path)

        mock_ftp.assert_called_once_with(host)
        ftp_instance.getwelcome.assert_called_once()
        ftp_instance.login.assert_called_once_with(username, password)
        print(f"login called with {ftp_instance.login.call_args}")
        ftp_instance.cwd.assert_called_once_with(path)
        print(f"cwd called with {ftp_instance.cwd.call_args}")
        ftp_instance.quit.assert_called_once()
        assert_equal(result, expected_result)
        assert_equal(ftp_instance.getwelcome(), expected_welcome_msg)
        assert_equal(ftp_instance.login(username, password), expected_login_msg)
        assert_equal(ftp_instance.cwd(path), expected_cwd_msg)
        assert_equal(ftp_instance.quit(), expected_quit_msg)


if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        host = 'localhost'
        username = 'user'
        password = '123'
        path = '/uploads'
        result = change_directory(host, username, password, path)
        print(result)
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
