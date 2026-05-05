import ? 


def get_new_post_id():
    ?


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestGetNewPostId(unittest.TestCase):
    @mock.patch('http.client.HTTPSConnection')
    def test_get_new_post_id(self, mock_connection):
        mock_response = mock.Mock()
        mock_response.read.return_value = b'{"id": 123}'
        mock_connection.return_value.getresponse.return_value = mock_response

        # Assume json_data and headers are defined
        headers = {'Content-type': 'application/json'}
        post_data = json.dumps({
            'title': 'New Entry',
            'body': 'This is a new post.',
            'userId': 1
        })
        
        post_id = get_new_post_id()
        
        mock_connection.assert_called_once_with("jsonplaceholder.typicode.com")
        print(f"connection called with: {mock_connection.call_args}")

        mock_connection.return_value.request.assert_called_once_with('POST', '/posts', body=post_data, headers=headers)
        print(f"request called with: {mock_connection.return_value.request.call_args}")

        mock_response.read.assert_called_once()
        print(f"read called: {mock_response.read.return_value}")

        mock_connection.return_value.close.assert_called_once()
        print(f"connection closed: {mock_connection.return_value.close.call_args}")

        assert_equal(post_id, 123)

if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        post_id = get_new_post_id()
        print(post_id)

    # run unit test to test locally
    # or for domjudge
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)