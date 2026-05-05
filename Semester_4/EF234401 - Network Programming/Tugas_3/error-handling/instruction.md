Error Handling

Description: Write a Python script to request
jsonplaceholder.typicode.com/invalidurl. If the request fails (HTTP
status code 404), print "Request Failed". Use the socket module to
solve this problem.

Input: None.

Output (without unit test): A message indicating whether the request
failed.

Output (with unit test):

connect called with: call(('jsonplaceholder.typicode.com', 80))
send called with: call(b'GET /invalidurl HTTP/1.1\r\nHost:
jsonplaceholder.typicode.com\r\nConnection: close\r\n\r\n')
recv called with: call(4096)
test attribute passed: Request Failed is equal to Request Failed
