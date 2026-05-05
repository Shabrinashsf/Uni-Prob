Update Resource Partially (http.client)

Description: Create a Python script to send a PATCH request to
jsonplaceholder.typicode.com/posts/1 updating the title to "Updated
Title". Print the new title of the post after the update. Use the
http.client module to connect to the server.

Input: None.

Output (without unit test): The updated title of the post.

Output (with unit test):

connection called with: call('jsonplaceholder.typicode.com')
request called with: call('PATCH', '/posts/1', body='{"title":
"Updated Title"}', headers={'Content-type': 'application/json'})
response read: b'{"title": "Updated Title"}'
connection closed: call()
test attribute passed: Updated Title is equal to Updated Title
