import http.client
import json
import sys
import unittest
from io import StringIO
from unittest import mock


def get_user_by_city(city):
    conn = http.client.HTTPSConnection("jsonplaceholder.typicode.com")
    conn.request("GET", "/users")

    response = conn.getresponse()
    conn.close()
    
    body = response.read()
    json_data = json.loads(body)
    for user in json_data:
        if user['address']['city'] == city:
            return user['name']



# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestGetUserByCity(unittest.TestCase):
    @mock.patch('http.client.HTTPSConnection')
    def test_get_user_by_city(self, mock_connection):
        # Mock the HTTP response
        mock_response = mock.Mock()
        mock_response.read.return_value = json.dumps([
            {
                'name': 'John Doe',
                'address': {
                    'city': 'New York'
                }
            },
            {
                'name': 'Jane Smith',
                'address': {
                    'city': 'Los Angeles'
                }
            }
        ]).encode()
        mock_connection.return_value.getresponse.return_value = mock_response

        # Test case 1: City exists in the data
        result = get_user_by_city('New York')

        mock_connection.assert_called_once_with("jsonplaceholder.typicode.com")
        print(f"connection called with: {mock_connection.call_args}")

        mock_connection.return_value.request.assert_called_once_with("GET", "/users")
        print(f"request called with: {mock_connection.return_value.request.call_args}")

        mock_response.read.assert_called_once()
        print(f"read called: {mock_response.read.return_value}")

        mock_connection.return_value.close.assert_called_once()
        print(f"connection closed: {mock_connection.return_value.close.call_args}")

        assert_equal(result, 'John Doe')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        city = get_user_by_city('New York')
        print(city)

    # run unit test to test locally
    # or for domjudge
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)