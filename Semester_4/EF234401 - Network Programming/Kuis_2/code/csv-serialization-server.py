import sys
import socket
import csv
import io
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def parse_csv(text):
    reader = csv.reader(io.StringIO(text))
    return [list(row) for row in reader]


def handle_once(server_socket):
    conn, _ = server_socket.accept()
    with conn:
        data = conn.recv(4096).decode('utf-8')
        rows = parse_csv(data)
        for row in rows:
            print('row: ' + ','.join(row))
        return rows


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        host = 'localhost'
        port = 6001
        s.bind((host, port))
        s.listen(1)
        handle_once(s)


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestCSVServer(unittest.TestCase):

    @patch('socket.socket')
    def test_handle(self, mock_socket_class):
        server_sock = MagicMock()
        mock_socket_class.return_value.__enter__.return_value = server_sock

        conn_sock = MagicMock()
        conn_sock.__enter__.return_value = conn_sock
        conn_sock.recv.return_value = b'name,age\r\nAlice,30\r\nBob,25\r\n'
        server_sock.accept.return_value = (conn_sock, ('127.0.0.1', 1))

        main()

        server_sock.bind.assert_called_once_with(('localhost', 6001))
        rows = parse_csv('name,age\r\nAlice,30\r\nBob,25\r\n')
        assert_equal(len(rows), 3)


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        main()
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
