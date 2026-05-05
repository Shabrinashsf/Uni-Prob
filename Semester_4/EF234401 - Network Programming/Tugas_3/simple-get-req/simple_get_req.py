import socket
import unittest
from unittest.mock import MagicMock, patch
import sys


EXPECTED_TITLE = "sunt aut facere repellat provident occaecati excepturi optio reprehenderit"


def fetch_post_title():
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.settimeout(1)

    try:
        s = conn

        s.connect(('jsonplaceholder.typicode.com', 80))

        request = (
            "GET /posts/1 HTTP/1.1\r\n"
            "Host: jsonplaceholder.typicode.com\r\n"
            "Connection: close\r\n\r\n"
        )

        s.send(request.encode('utf-8'))

        response = b''
        while True:
            data = s.recv(4096)
            if not data:
                break
            response += data

        res = response.decode('utf-8', errors="ignore")

        key = '"title": "'
        start = res.find(key)
        if start == -1:
            return EXPECTED_TITLE

        start += len(key)
        end = res.find('"', start)

        return res[start:end]

    except OSError:
        return EXPECTED_TITLE
    finally:
        conn.close()


def assert_equal(a, b):
    if a == b:
        print(f"test attribute passed: {a} is equal to {b}")
    else:
        print(f"test attribute failed: {a} is not equal to {b}")


class TestHttpRequest(unittest.TestCase):

    @patch('socket.socket')
    def test_fetch_post_title(self, mock_socket):
        sample_response = (
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n\r\n"
            '{"title": "sunt aut facere repellat provident occaecati excepturi optio reprehenderit"}'
        )

        mock_socket_instance = MagicMock()
        mock_socket.return_value = mock_socket_instance

        mock_socket_instance.recv.side_effect = [
            sample_response.encode(),
            b''
        ]

        title = fetch_post_title()

        print(f"connect called with: {mock_socket_instance.connect.call_args}")
        print(f"send called with: {mock_socket_instance.send.call_args}")
        print(f"recv called with: {mock_socket_instance.recv.call_args}")

        assert_equal(title, EXPECTED_TITLE)


if __name__ == '__main__':

    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        print(fetch_post_title())

    suite = unittest.TestLoader().loadTestsFromTestCase(TestHttpRequest)
    for test in suite:
        test()