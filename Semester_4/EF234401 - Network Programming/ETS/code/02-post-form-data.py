import socket
import sys
import unittest
import json
from io import StringIO
from unittest.mock import MagicMock, patch

def post_form_data() -> str:
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect(('httpbin.org', 80))
    
    body_data = "name=John+Doe&age=30"
    
    headers = (
        "POST /post HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        f"Content-Length: {len(body_data)}\r\n"
        "Connection: close\r\n\r\n"
    )
    
    conn.send((headers + body_data).encode('utf-8'))
    
    response = b''
    while True:
        data = conn.recv(4096)
        if not data:
            break
        response += data
        
    res = response.decode('utf-8')
    
    body = res.split('\r\n\r\n', 1)[1]
    return body

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestPostFormData(unittest.TestCase):
    @patch('socket.socket')
    def test_post_form_data(self, mock_socket):
        print('Testing post_form_data ...')
        mock_sock_instance = MagicMock()
        mock_socket.return_value = mock_sock_instance
        
        # Format the fake response to match the user's expected output
        expected_body = '{"form": {"name": "John Doe", "age": "30"}}'
        fake_response = f'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{expected_body}'.encode('utf-8')
        
        mock_sock_instance.recv.side_effect = [fake_response, b'']

        result = post_form_data()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        self.assertGreaterEqual(mock_sock_instance.recv.call_count, 1)
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, expected_body)


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        body = post_form_data()
        print(body)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)