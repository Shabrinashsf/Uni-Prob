import socket
import sys
import unittest
from io import StringIO
from unittest.mock import MagicMock, patch


def check_server_status():
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.settimeout(3)

    try:
        conn.connect(('jsonplaceholder.typicode.com', 80))

        request = (
            "GET /posts HTTP/1.1\r\n"
            "Host: jsonplaceholder.typicode.com\r\n"
            "Connection: close\r\n\r\n"
        )

        conn.send(request.encode('utf-8'))

        response = b''
        while True:
            data = conn.recv(4096)
            if not data:
                break
            response += data

        res = response.decode('utf-8')

        # ambil HTTP status code
        status_code = res.split()[1]

        return status_code
    except OSError:
        return '500'
    finally:
        conn.close()


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestCheckServerStatus(unittest.TestCase):

    @patch('socket.socket')
    def test_server_up(self, mock_socket):

        mock_socket_instance = MagicMock()
        mock_socket.return_value = mock_socket_instance

        http_response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n"

        mock_socket_instance.recv.side_effect = [
            http_response.encode('utf-8'),
            b''
        ]

        print("Server is up!")

        status_code = check_server_status()

        mock_socket_instance.connect.assert_called_with(('jsonplaceholder.typicode.com', 80))
        print(f"connect called with: {mock_socket_instance.connect.call_args}")

        mock_socket_instance.send.assert_called_once()
        print(f"send called with: {mock_socket_instance.send.call_args}")

        mock_socket_instance.recv.assert_called()
        print(f"recv called with: {mock_socket_instance.recv.call_args}")

        assert_equal(status_code, '200')


    @patch('socket.socket')
    def test_server_down(self, mock_socket):

        mock_socket_instance = MagicMock()
        mock_socket.return_value = mock_socket_instance

        http_response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n"

        mock_socket_instance.recv.side_effect = [
            http_response.encode('utf-8'),
            b''
        ]

        print("Server is down!")

        status_code = check_server_status()

        mock_socket_instance.connect.assert_called_with(('jsonplaceholder.typicode.com', 80))
        print(f"connect called with: {mock_socket_instance.connect.call_args}")

        mock_socket_instance.send.assert_called_once()
        print(f"send called with: {mock_socket_instance.send.call_args}")

        mock_socket_instance.recv.assert_called()
        print(f"recv called with: {mock_socket_instance.recv.call_args}")

        assert_equal(status_code, '500')


# RUNNER
if __name__ == "__main__":

    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        status = check_server_status()

        if status == '200':
            print("Server is up!")
        else:
            print("Server is down!")

        sys.exit(0)

    # DOMJUDGE / UNIT TEST MODE
    tests = TestCheckServerStatus()
    tests.test_server_down()
    tests.test_server_up()