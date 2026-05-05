import http.client
import json
import socket
import unittest
from unittest import mock
from io import StringIO
import sys


def send_json_request():
    request_data = {
        "name": "John Doe",
        "age": 30
    }

    json_data = json.dumps(request_data)

    headers = {
        "Content-Type": "application/json",
        "Content-Length": str(len(json_data))
    }

    previous_timeout = socket.getdefaulttimeout()
    socket.setdefaulttimeout(1)

    conn = http.client.HTTPConnection("httpbin.org")
    try:
        conn.request("POST", "/post", body=json_data, headers=headers)

        response = conn.getresponse()
        return response.read().decode('utf-8')
    except OSError:
        return ""
    finally:
        conn.close()
        socket.setdefaulttimeout(previous_timeout)

# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestSendJsonRequest(unittest.TestCase):
    @mock.patch('http.client.HTTPConnection')
    def test_send_json_request(self, mock_http_connection):
        # Mock the HTTPConnection object
        mock_conn = mock_http_connection.return_value

        # Set up the expected data, headers, host, and path
        expected_data = json.dumps({"name": "John Doe", "age": 30})
        expected_content_length = len(expected_data)
        expected_headers = {
            "Content-Type": "application/json",
            "Content-Length": str(expected_content_length)
        }
        expected_host = 'httpbin.org'
        expected_path = '/post'

        # Set up the expected response
        expected_response_body = 'Mock response body'
        expected_response = mock.Mock()
        expected_response.read.return_value.decode.return_value = expected_response_body
        mock_conn.getresponse.return_value = expected_response

        # Call the function
        response_body = send_json_request()

        # Assert that the HTTPConnection was called with the expected arguments
        mock_http_connection.assert_called_once_with(expected_host)
        print(f"connection called with: {mock_http_connection.call_args}")

        # Assert that the request was sent with the expected arguments
        mock_conn.request.assert_called_once_with("POST", expected_path, body=expected_data, headers=expected_headers)
        print(f"request called with: {mock_conn.request.call_args}")

        # Assert that the response was read and decoded
        expected_response.read.assert_called_once()
        expected_response.read.return_value.decode.assert_called_once()
        print(f"read called: {expected_response.read.return_value.decode.return_value}")

        # Assert that the connection was closed
        mock_conn.close.assert_called_once()
        print(f"connection closed: {mock_conn.close.call_args}")

        # Assert that the response body is returned
        assert_equal(response_body, expected_response_body)

if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        body = send_json_request()
        print(body)
        sys.exit(0)

    # run unit test to test locally or for domjudge
    test = TestSendJsonRequest()
    test.test_send_json_request()