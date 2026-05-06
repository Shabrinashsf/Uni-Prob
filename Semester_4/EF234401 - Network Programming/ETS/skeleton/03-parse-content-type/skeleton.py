import ?




def get_header_value(response: str, header_name: str) -> str:
    ?

def request_content_type() -> str:
    ?

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
        mock_socket.return_value.__enter__.return_value = mock_sock_instance
        mock_sock_instance.recv.return_value = b'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{"json": true}'

        result = request_content_type()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        mock_sock_instance.recv.assert_called_once()
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, 'application/json')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        ct = request_content_type()
        print(ct)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
