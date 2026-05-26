import sys
import socket
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def handle_once(server_socket):
    data, addr = server_socket.recvfrom(?)
    print(?)
    server_socket.sendto(?, ?)
    return data, addr


def main():
    with socket.socket(?, ?) as s:
        s.bind(?)
        handle_once(s)


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestUDPEchoServer(unittest.TestCase):

    @patch('socket.socket')
    def test_handle_once(self, mock_socket_class):
        mock_sock = MagicMock()
        mock_socket_class.return_value.__enter__.return_value = mock_sock
        mock_sock.recvfrom.return_value = (b'Ping', ('127.0.0.1', 5050))

        main()

        mock_sock.bind.assert_called_once_with(('localhost', 9999))
        mock_sock.sendto.assert_called_once_with(b'Ping', ('127.0.0.1', 5050))
        sent = mock_sock.sendto.call_args[0][0]
        assert_equal(sent.decode('utf-8'), 'Ping')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        main()
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
