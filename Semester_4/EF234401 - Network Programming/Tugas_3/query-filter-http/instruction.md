Query API and Filter Data (http.client)

Description: Write a Python program to fetch posts from https://
jsonplaceholder.typicode.com/posts and print the total number of
posts that contain the word "voluptate" in the body. Use the
http.client module to solve this problem.

Input: None.

Output (without unit test): Count of posts containing "voluptate".

Output (with unit test):

connection called with: call('jsonplaceholder.typicode.com')
request called with: call('GET', '/posts')
response read called with: b'[{"body": "voluptate"}, {"body": "nonvoluptate"}]'
connection closed: call()
test attribute passed: 2 is equal to 2
