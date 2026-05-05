Handling POST Requests

Description: Create a Python script to post a new comment to
jsonplaceholder.typicode.com/comments. The comment should include
postId=1, name='Test Name', email='test@example.com', and body='This
is a test comment.'. Print the id of the new comment. Use the socket
module to solve this problem.

Input: None.

Output (without unit test): The id of the newly created comment.

Output (with unit test):

connect called with: call(('jsonplaceholder.typicode.com', 80))
send called with: call(b'POST /comments HTTP/1.1\r\nHost:
jsonplaceholder.typicode.com\r\nContent-Type: application/
json\r\nContent-Length: 98\r\nConnection: close\r\n\r\n{"postId": 1,
"name": "Test Name", "email": "test@example.com", "body": "This is a
test comment."}')
recv called with: call(4096)
test attribute passed: 101 is equal to 101
