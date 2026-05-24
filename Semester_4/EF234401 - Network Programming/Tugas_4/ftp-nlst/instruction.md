FTP List Files (NLST)

Description
In this problem, you are asked to implement an FTP client that
connects to an FTP server, retrieves a list of files in the current
directory using the NLST command, and returns the list.
Method
Your task is to implement the list_files function that:

- Connects to the FTP server at the given host
- Prints the welcome message from the server
- Logs in with the given username and password
- Retrieves and prints the list of files using nlst()
- Quits the connection
- Returns the list of files

Input
There is no input for this problem.
Output
The FTP server responses and list of files (verified via unit test).
Sample Output
220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/
230 Login successful.
Files: ['file1.txt', 'file2.pdf', 'file3.png']
221 Goodbye.
login called with call('user', '123')
nlst called with call()
test attribute passed: ['file1.txt', 'file2.pdf', 'file3.png'] is equal to ['fil
e1.txt', 'file2.pdf', 'file3.png']
test attribute passed: 220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/ is equal to 220-FileZilla Server
1.7.0
220 Please visit https://filezilla-project.org/
test attribute passed: 230 Login successful. is equal to 230 Login successful.
test attribute passed: ['file1.txt', 'file2.pdf', 'file3.png'] is equal to ['fil
e1.txt', 'file2.pdf', 'file3.png']
test attribute passed: 221 Goodbye. is equal to 221 Goodbye.
