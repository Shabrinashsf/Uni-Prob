Check Server Status
Description: Write a Python program that checks the status of
jsonplaceholder.typicode.com/posts and prints "Server is up!" if the
status is 200, otherwise print "Server is down!". Use the socket
module to connect to the server.

Input: None.

Output (without unit test): Server status message.

Output (with unit test):

Server is down!
connect called with: call(('jsonplaceholder.typicode.com', 80))
send called with: call(b'GET /posts HTTP/1.1\r\nHost:
jsonplaceholder.typicode.com\r\nConnection: close\r\n\r\n')
recv called with: call(4096)
test attribute passed: 500 is equal to 500
Server is up!
connect called with: call(('jsonplaceholder.typicode.com', 80))
send called with: call(b'GET /posts HTTP/1.1\r\nHost:
jsonplaceholder.typicode.com\r\nConnection: close\r\n\r\n')
recv called with: call(4096)
test attribute passed: 200 is equal to 200
