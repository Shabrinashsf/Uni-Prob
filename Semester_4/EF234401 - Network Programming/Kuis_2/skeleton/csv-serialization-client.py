import sys
import socket
import csv
import io
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def serialize_csv(rows, header):
    buf = io.StringIO()
    writer = csv.writer(?)
    writer.writerow(?)
    writer.writerows(?)
    return ?


def main():
    rows = [['Alice', '30'], ['Bob', '25']]
    header = ['name', 'age']
    payload = ?
    with socket.socket(?, ?) as s:
        s.connect(?)
        s.sendall(?)
        print(?)


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestCSVClient(unittest.TestCase):

    @patch('socket.socket')
    def test_sends_csv(self, mock_socket_class):
        mock_sock = MagicMock()
        mock_socket_class.return_value.__enter__.return_value = mock_sock

        main()

        mock_sock.connect.assert_called_once_with(('localhost', 6000))
        sent = mock_sock.sendall.call_args[0][0].decode('utf-8').splitlines()
        assert_equal(sent[0], 'name,age')
        assert_equal(sent[1], 'Alice,30')
        assert_equal(sent[2], 'Bob,25')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        main()
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
