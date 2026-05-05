Send JSON Data in POST Request (http.client)

Description: Write a Python script to send a POST request with JSON
data to https://httpbin.org/post. Include the following data in the
request: { "name": "John Doe", "age": 30 }. Print the JSON response
from the server. Use the http.client module to solve this problem.

Input: None.

Output (without unit test): The JSON response containing the data
sent.

Output (with unit test):

connection called with: call('httpbin.org')
request called with: call('POST', '/post', body='{"name": "John
Doe", "age": 30}', headers={'Content-Type': 'application/json',
'Content-Length': '31'})
read called: Mock response body
connection closed: call()
test attribute passed: Mock response body is equal to Mock response
body
