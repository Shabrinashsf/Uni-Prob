Fetch and Filter JSON Data (http.client)

Description: Write a Python program that fetches data from https://
jsonplaceholder.typicode.com/users and prints the name of the user
who lives in the city "Gwenborough". Use http.client module to
connect to the server.

Input: None.

Output (without unit test): The name of the user.

Output (with unit test):

connection called with: call('jsonplaceholder.typicode.com')
request called with: call('GET', '/users')
read called: b'[{"name": "John Doe", "address": {"city": "New
York"}}, {"name": "Jane Smith", "address": {"city": "Los
Angeles"}}]'
connection closed: call()
test attribute passed: John Doe is equal to John Doe
