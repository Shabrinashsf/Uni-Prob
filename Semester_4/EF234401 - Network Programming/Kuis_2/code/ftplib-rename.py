import sys
import unittest
from ftplib import FTP
from unittest.mock import patch, MagicMock
from io import StringIO


def rename_file(host, username, password, old_name, new_name):
    ftp = FTP(host)
    try:
        ftp.login(username, password)
        ftp.rename(old_name, new_name)
        print(f"Renamed '{old_name}' to '{new_name}' successfully.")
    except Exception as e:
        print(f"Failed to rename file: {e}")
    ftp.quit()


class NullWriter(StringIO):
    def write(self, txt):
        pass


class TestRenameFile(unittest.TestCase):

    @patch('__main__.FTP')
    def test_rename_success(self, mock_ftp_class):
        mock_ftp = MagicMock()
        mock_ftp_class.return_value = mock_ftp

        rename_file('localhost', 'hudan', '123', '/old.txt', '/new.txt')

        mock_ftp.login.assert_called_once_with('hudan', '123')
        print(f"login called with {mock_ftp.login.call_args}")
        mock_ftp.rename.assert_called_once_with('/old.txt', '/new.txt')
        print(f"rename called with {mock_ftp.rename.call_args}")
        mock_ftp.quit.assert_called_once()
        print(f"quit called with {mock_ftp.quit.call_args}")

    @patch('__main__.FTP')
    def test_rename_failure(self, mock_ftp_class):
        mock_ftp = MagicMock()
        mock_ftp_class.return_value = mock_ftp
        mock_ftp.rename.side_effect = Exception('cannot rename')

        rename_file('localhost', 'hudan', '123', '/old.txt', '/new.txt')

        mock_ftp.login.assert_called_once_with('hudan', '123')
        print(f"login called with {mock_ftp.login.call_args}")
        mock_ftp.rename.assert_called_once_with('/old.txt', '/new.txt')
        print(f"rename called with {mock_ftp.rename.call_args}")
        mock_ftp.quit.assert_called_once()
        print(f"quit called with {mock_ftp.quit.call_args}")


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        rename_file('localhost', 'hudan', '123', '/old.txt', '/new.txt')
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)