Delete a Resource

Description: Write a Python program that sends a DELETE request to
delete the post with id=1 at https://jsonplaceholder.typicode.com/
posts/1. Print "Deleted successfully" if the operation is
acknowledged by the server. Use the socket module to solve this
problem.

Input: None.

Output (without unit test): Deletion confirmation.

Output (with unit test):

Deleted successfully
connect called with: call(('jsonplaceholder.typicode.com', 80))
send called with: call(b'DELETE /posts/1 HTTP/1.1\r\nHost:
jsonplaceholder.typicode.com\r\nConnection: close\r\n\r\n')
recv called with: call(4096)
test attribute passed: 200 is equal to 200
