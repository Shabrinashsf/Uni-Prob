import ?




def post_form_data() -> str:
    ?

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
        mock_socket.return_value.__enter__.return_value = mock_sock_instance
        fake_response = b'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{"form": {"name": "John Doe", "age": "30"}}'
        mock_sock_instance.recv.return_value = fake_response

        result = post_form_data()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        mock_sock_instance.recv.assert_called_once()
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, '{"form": {"name": "John Doe", "age": "30"}}')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        body = post_form_data()
        print(body)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
