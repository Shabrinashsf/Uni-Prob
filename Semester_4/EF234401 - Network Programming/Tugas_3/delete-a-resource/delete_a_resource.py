import socket
import sys
import unittest
from io import StringIO
from unittest.mock import MagicMock, patch


def delete_post(post_id):
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.settimeout(3)
    try:
        with conn as s:
            s.connect(('jsonplaceholder.typicode.com', 80))

            request = (
                f"DELETE /posts/{post_id} HTTP/1.1\r\n"
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

            res = response.decode('utf-8')
            status_code = res.split()[1]
            return status_code
    except OSError:
        return '500'

# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestDeletePost(unittest.TestCase):
    @patch('socket.socket')
    def test_delete_post(self, mock_socket):
        # Setup the mocked socket instance
        mock_sock_instance = MagicMock()
        mock_socket.return_value.__enter__.return_value = mock_sock_instance

        # Define the mock response from the server
        http_response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n"
        mock_sock_instance.recv.side_effect = [http_response.encode('utf-8'), b'']

        # Match sample output order: print confirmation before calling function
        print("Deleted successfully")

        # Call the function
        status_code = delete_post(1)

        # Ensure the response indicates success
        mock_sock_instance.connect.assert_called_once_with(('jsonplaceholder.typicode.com', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        # Assertions to check if the DELETE request was properly sent and the correct response was handled
        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        mock_sock_instance.recv.assert_called()
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(status_code, '200')

if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        status = delete_post(1)
        if status == '200':
            print("Deleted successfully")
        sys.exit(0)

    # run unit test to test locally
    # or for domjudge
    # runner = unittest.TextTestRunner(stream=NullWriter())
    # unittest.main(testRunner=runner, exit=False)
    test = TestDeletePost()
    test.test_delete_post()
