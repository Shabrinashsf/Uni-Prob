Post Data (http.client)

Description: Create a Python script that posts a new blog entry to
jsonplaceholder.typicode.com/posts. The entry should have title='New
Entry', body='This is a new post.', and userId=1. Print the id of
the created post. Use http.client to connect to the server.

Input: None.

Output (without unit test): The id of the newly created post.

Output (with unit test):

connection called with: call('jsonplaceholder.typicode.com')
request called with: call('POST', '/posts', body='{"title": "New
Entry", "body": "This is a new post.", "userId": 1}',
headers={'Content-type': 'application/json'})
read called: b'{"id": 123}'
connection closed: call()
test attribute passed: 123 is equal to 123
