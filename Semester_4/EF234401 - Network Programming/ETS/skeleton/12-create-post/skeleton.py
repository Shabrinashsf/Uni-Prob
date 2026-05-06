import ?




def create_post(title: str, body: str, user_id: int) -> dict:
    ?

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestCreatePost(unittest.TestCase):
    @mock.patch('http.client.HTTPConnection')
    def test_create_post(self, mock_http_connection):
        print('Testing create_post ...')
        mock_conn = mock_http_connection.return_value
        expected_data = json.dumps({'title': 'My Post', 'body': 'Post content', 'userId': 1})
        expected_headers = {
            'Content-Type': 'application/json',
            'Content-Length': str(len(expected_data))
        }
        mock_response = mock.Mock()
        mock_response.read.return_value.decode.return_value = '{"id": 101, "title": "My Post", "body": "Post content", "userId": 1}'
        mock_conn.getresponse.return_value = mock_response

        result = create_post('My Post', 'Post content', 1)

        mock_http_connection.assert_called_once_with('jsonplaceholder.typicode.com')
        print(f"connection called with: {mock_http_connection.call_args}")

        mock_conn.request.assert_called_once_with('POST', '/posts', body=expected_data, headers=expected_headers)
        print(f"request called with: {mock_conn.request.call_args}")

        mock_conn.close.assert_called_once()
        print(f"connection closed: {mock_conn.close.call_args}")

        assert_equal(result['id'], 101)
        assert_equal(result['title'], 'My Post')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        post = create_post('My Post', 'Post content', 1)
        print(post)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
