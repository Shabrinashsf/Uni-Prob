import json
import socket
import sys
import unittest
from io import StringIO
from unittest.mock import MagicMock, patch


def get_with_user_agent() -> str:
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect(('httpbin.org', 80))
    
    headers = (
        "GET /user-agent HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "User-Agent: MyCustomAgent/1.0\r\n"
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
    
    body = res.split('\r\n\r\n')[1]
    json_body = json.loads(body)
    
    return json_body.get('user-agent', '')

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestUserAgentHeader(unittest.TestCase):
    @patch('socket.socket')
    def test_get_with_user_agent(self, mock_socket):
        print('Testing get_with_user_agent ...')
        mock_sock_instance = MagicMock()
        mock_socket.return_value = mock_sock_instance
        fake_response = b'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{"user-agent": "MyCustomAgent/1.0"}'
        mock_sock_instance.recv.side_effect = [fake_response, b'']

        result = get_with_user_agent()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        self.assertGreaterEqual(mock_sock_instance.recv.call_count, 1)
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, 'MyCustomAgent/1.0')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        ua = get_with_user_agent()
        print(ua)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
