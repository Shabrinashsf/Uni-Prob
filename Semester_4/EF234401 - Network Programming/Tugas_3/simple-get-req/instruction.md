Simple GET Request

Description: Write a Python program that performs a GET request to
jsonplaceholder.typicode.com/posts/1 and prints the title of the
post. Use socket modules to connect to the server.

Input: None.

Output (without unit test): The title of the post.

Output (with unit test):

connect called with: call(('jsonplaceholder.typicode.com', 80))
send called with: call(b'GET /posts/1 HTTP/1.1\r\nHost:
jsonplaceholder.typicode.com\r\nConnection: close\r\n\r\n')
recv called with: call(4096)
test attribute passed: sunt aut facere repellat provident occaecati
excepturi optio reprehenderit is equal to sunt aut facere repellat
provident occaecati excepturi optio reprehenderit
