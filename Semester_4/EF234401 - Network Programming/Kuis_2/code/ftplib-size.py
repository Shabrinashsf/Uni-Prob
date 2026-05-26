import sys
import unittest
from ftplib import FTP
from unittest.mock import patch, MagicMock
from io import StringIO
# from debugpy._vendored.pydevd._pydevd_frame_eval.pydevd_frame_evaluator import success


def get_file_size(host, username, password, filename):
    ftp = FTP(host)
    ftp.login(username, password)
    try:
        size = ftp.size(filename)
        mesage = f"Size of '{filename}': {size} bytes"
        print(mesage)
    except Exception as e:
        print(f"Failed to get file size: {e}")
    ftp.quit()


class NullWriter(StringIO):
    def write(self, txt):
        pass


class TestFileSize(unittest.TestCase):

    @patch('__main__.FTP')
    def test_size_success(self, mock_ftp_class):
        mock_ftp = MagicMock()
        mock_ftp_class.return_value = mock_ftp
        mock_ftp.size.return_value = 2048

        get_file_size('localhost', 'hudan', '123', '/data.bin')

        mock_ftp.login.assert_called_once_with('hudan', '123')
        print(f"login called with {mock_ftp.login.call_args}")
        mock_ftp.size.assert_called_once_with('/data.bin')
        print(f"size called with {mock_ftp.size.call_args}")
        mock_ftp.quit.assert_called_once()
        print(f"quit called with {mock_ftp.quit.call_args}")

    @patch('__main__.FTP')
    def test_size_failure(self, mock_ftp_class):
        mock_ftp = MagicMock()
        mock_ftp_class.return_value = mock_ftp
        mock_ftp.size.side_effect = Exception('not found')

        get_file_size('localhost', 'hudan', '123', '/data.bin')

        mock_ftp.login.assert_called_once_with('hudan', '123')
        print(f"login called with {mock_ftp.login.call_args}")
        mock_ftp.size.assert_called_once_with('/data.bin')
        print(f"size called with {mock_ftp.size.call_args}")
        mock_ftp.quit.assert_called_once()
        print(f"quit called with {mock_ftp.quit.call_args}")


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        get_file_size('localhost', 'hudan', '123', '/data.bin')
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
