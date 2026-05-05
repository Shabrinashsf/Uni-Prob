import socket
import unittest
from unittest.mock import MagicMock, patch
from io import StringIO
import sys
import json


def post_comment():
    request_body = {
        "postId": 1,
        "name": "Test Name",
        "email": "test@example.com",
        "body": "This is a test comment."
    }

    json_data = json.dumps(request_body)

    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.settimeout(3)
    try:
        with conn as s:
            s.connect(('jsonplaceholder.typicode.com', 80))

            request = (
                "POST /comments HTTP/1.1\r\n"
                "Host: jsonplaceholder.typicode.com\r\n"
                "Content-Type: application/json\r\n"
                f"Content-Length: {len(json_data)}\r\n"
                "Connection: close\r\n\r\n"
                f"{json_data}"
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
            if status_code == '201':
                # Extract the comment ID from the response body
                response_body = res.split('\r\n\r\n')[1]
                comment_id = json.loads(response_body)['id']
                return comment_id
            return None
    except OSError:
        return None


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestCommentPoster(unittest.TestCase):
    @patch('socket.socket')
    def test_post_comment(self, mock_socket):
        # Setup the mock socket
        mock_socket_instance = MagicMock()
        mock_socket.return_value.__enter__.return_value = mock_socket_instance
        
        # Define a fake response to be returned by socket.recv
        fake_response = "HTTP/1.1 201 Created\r\nContent-Type: application/json\r\n\r\n{\"id\": 101, \"name\": \"Test Name\"}"
        mock_socket_instance.recv.side_effect = [fake_response.encode(), b'']

        # Call the function
        comment_id = post_comment()

        # Verify that the socket methods were called correctly
        mock_socket_instance.connect.assert_called_with(('jsonplaceholder.typicode.com', 80))
        print(f"connect called with: {mock_socket_instance.connect.call_args}")

        mock_socket_instance.send.assert_called_once()
        print(f"send called with: {mock_socket_instance.send.call_args}")

        mock_socket_instance.recv.assert_called()
        print(f"recv called with: {mock_socket_instance.recv.call_args}")

        assert_equal(comment_id, 101)


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        comment_id = post_comment()
        print(comment_id)
        sys.exit(0)

    # run unit test to test locally or for domjudge
    test = TestCommentPoster()
    test.test_post_comment()
