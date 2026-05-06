import ?




def get_status_code(response: str) -> int:
    ?

def make_request() -> int:
    ?

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
        mock_socket.return_value.__enter__.return_value = mock_sock_instance
        mock_sock_instance.recv.return_value = b'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'

        result = make_request()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        mock_sock_instance.recv.assert_called_once()
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, 200)


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        status = make_request()
        print(status)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
