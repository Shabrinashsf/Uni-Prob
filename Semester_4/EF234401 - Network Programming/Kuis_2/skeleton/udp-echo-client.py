import sys
import socket
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def udp_echo(host, port, message):
    with socket.socket(?, ?) as s:
        s.sendto(?, ?)
        data, _ = s.recvfrom(?)
        return ?


def main():
    reply = ?
    print(?)


class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestUDPEchoClient(unittest.TestCase):

    @patch('socket.socket')
    def test_udp_echo(self, mock_socket_class):
        mock_sock = MagicMock()
        mock_socket_class.return_value.__enter__.return_value = mock_sock
        mock_sock.recvfrom.return_value = (b'Hello UDP', ('localhost', 9999))

        main()

        mock_sock.sendto.assert_called_once_with(b'Hello UDP', ('localhost', 9999))
        sent = mock_sock.sendto.call_args[0][0]
        assert_equal(sent.decode('utf-8'), 'Hello UDP')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        main()
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
