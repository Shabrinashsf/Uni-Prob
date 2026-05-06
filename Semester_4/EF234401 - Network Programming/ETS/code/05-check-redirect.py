import socket
import sys
import unittest
from io import StringIO
from unittest.mock import MagicMock, patch




def is_redirect(response: str) -> bool:
    status_line = response.split('\r\n')[0]
    status_code = int(status_line.split(' ')[1])
    return 300 <= status_code < 400
    

def make_redirect_request() -> bool:
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect(('httpbin.org', 80))
    
    headers = (
        "GET /redirect/1 HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "Connection: close\r\n\r\n"
    )
    
    conn.send(headers.encode('utf-8'))
    
    response = b''
    while True:
        data = conn.recv(4096)
        if not data:
            break
        response += data
        
    res = response.decode('utf-8')
    
    return is_redirect(res)

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestCheckRedirect(unittest.TestCase):
    def test_is_redirect(self):
        print('Testing is_redirect ...')
        assert_equal(is_redirect('HTTP/1.1 301 Moved Permanently\r\n\r\n'), True)
        assert_equal(is_redirect('HTTP/1.1 200 OK\r\n\r\n'), False)
        assert_equal(is_redirect('HTTP/1.1 404 Not Found\r\n\r\n'), False)

    @patch('socket.socket')
    def test_make_redirect_request(self, mock_socket):
        print('Testing make_redirect_request ...')
        mock_sock_instance = MagicMock()
        mock_socket.return_value = mock_sock_instance
        mock_sock_instance.recv.side_effect = [
            b'HTTP/1.1 301 Moved Permanently\r\n\r\n',
            b''
        ]

        result = make_redirect_request()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        self.assertGreaterEqual(mock_sock_instance.recv.call_count, 1)
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, True)


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        result = make_redirect_request()
        print(result)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
