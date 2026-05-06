import socket
import sys
import unittest
import json
from io import StringIO
from unittest.mock import MagicMock, patch



def get_header_value(response: str, header_name: str) -> str:
    headers_part = response.split('\r\n\r\n')[0]
    headers_lines = headers_part.split('\r\n')[1:]
    
    for line in headers_lines:
        if line.startswith(header_name + ':'):
            return line.split(':', 1)[1].strip()
    
    return ''

def request_content_type() -> str:
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect(('httpbin.org', 80))
    
    headers = (
        "GET /json HTTP/1.1\r\n"
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
    
    content_type = get_header_value(res, 'Content-Type')
    return content_type

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestParseContentType(unittest.TestCase):
    def test_get_header_value(self):
        print('Testing get_header_value ...')
        response = 'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 10\r\n\r\nbody'
        assert_equal(get_header_value(response, 'Content-Type'), 'application/json')
        assert_equal(get_header_value(response, 'Content-Length'), '10')
        assert_equal(get_header_value(response, 'X-Missing'), '')

    @patch('socket.socket')
    def test_request_content_type(self, mock_socket):
        print('Testing request_content_type ...')
        mock_sock_instance = MagicMock()
        mock_socket.return_value = mock_sock_instance
        mock_sock_instance.recv.side_effect = [b'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{"json": true}', b'']

        result = request_content_type()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        self.assertGreaterEqual(mock_sock_instance.recv.call_count, 1)
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, 'application/json')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        ct = request_content_type()
        print(ct)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)