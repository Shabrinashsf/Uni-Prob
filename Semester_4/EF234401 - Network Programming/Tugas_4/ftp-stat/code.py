import sys
from ftplib import FTP
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def get_status(host, username, password):
    # Create FTP connection to host
    ftp = FTP(host)

    # Get and print welcome message
    welcome_msg = ftp.getwelcome()
    print(welcome_msg)

    # Login and print response
    login_msg = ftp.login(username, password)
    print(login_msg)

    # Send STAT command and print response
    stat_msg = ftp.voidcmd('STAT')
    print(stat_msg)

    # Quit and print response
    quit_msg = ftp.quit()
    print(quit_msg)

    return stat_msg


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestGetStatus(unittest.TestCase):
    @patch('__main__.FTP')
    def test_get_status(self, mock_ftp):
        host = 'localhost'
        username = 'user'
        password = '123'
        expected_welcome_msg = "220-FileZilla Server 1.7.0\r\n220 Please visit https://filezilla-project.org/"
        expected_login_msg = "230 Login successful."
        expected_stat_msg = "211-FTP server status\r\n211 End of status."
        expected_quit_msg = "221 Goodbye."

        ftp_instance = mock_ftp.return_value
        ftp_instance.getwelcome.return_value = expected_welcome_msg
        ftp_instance.login.return_value = expected_login_msg
        ftp_instance.voidcmd.return_value = expected_stat_msg
        ftp_instance.quit.return_value = expected_quit_msg

        result = get_status(host, username, password)

        mock_ftp.assert_called_once_with(host)
        ftp_instance.getwelcome.assert_called_once()
        ftp_instance.login.assert_called_once_with(username, password)
        print(f"login called with {ftp_instance.login.call_args}")
        ftp_instance.voidcmd.assert_called_once_with('STAT')
        print(f"voidcmd called with {ftp_instance.voidcmd.call_args}")
        ftp_instance.quit.assert_called_once()
        assert_equal(result, expected_stat_msg)
        assert_equal(ftp_instance.getwelcome(), expected_welcome_msg)
        assert_equal(ftp_instance.login(username, password), expected_login_msg)
        assert_equal(ftp_instance.voidcmd('STAT'), expected_stat_msg)
        assert_equal(ftp_instance.quit(), expected_quit_msg)


if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        host = 'localhost'
        username = 'user'
        password = '123'
        result = get_status(host, username, password)
        print(result)
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
