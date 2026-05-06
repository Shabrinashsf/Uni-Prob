import socket
import sys
import unittest
from io import StringIO
from unittest.mock import MagicMock, patch


def get_status_code(response: str) -> int:
    status_code = response.split()[1]
    return int(status_code) 

def make_request() -> int:
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect(('httpbin.org', 80))
    
    request = (
        "GET /status/200 HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
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
    
    status = get_status_code(res)
    return status

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestGetStatusCode(unittest.TestCase):
    def test_get_status_code(self):
        print('Testing get_status_code ...')
        response = 'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'
        assert_equal(get_status_code(response), 200)
        response404 = 'HTTP/1.1 404 Not Found\r\n\r\n'
        assert_equal(get_status_code(response404), 404)

    @patch('socket.socket')
    def test_make_request(self, mock_socket):
        print('Testing make_request ...')
        mock_sock_instance = MagicMock()
        mock_socket.return_value = mock_sock_instance
        # mock_socket.return_value.__enter__.return_value = mock_sock_instance
        mock_sock_instance.recv.side_effect = [b'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n', b'']

        result = make_request()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        self.assertGreaterEqual(mock_sock_instance.recv.call_count, 1)
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, 200)


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        status = make_request()
        print(status)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
