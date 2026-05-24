FTP Get File Size Client

Background
FTP supports retrieving the size of files on the server. You must implement an F
TP client that retrieves a file's size using ftplib.
Task
Implement get_file_size(host, username, password, filename) which logs in and re
turns the size of the specified file.
Requirements

- Establish connection and print welcome message.
- Login and print response.
- Retrieve file size (integer, not printed).
- Quit and print response.
- Return a message containing the filename and size.

Output (without unit test)
220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/
230 Login successful.
221 Goodbye.
File report.txt has size 1024 bytes.

Output (with unit test)
220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/
230 Login successful.
221 Goodbye.
login called with call('user', '123')
size called with call('report.txt')
test attribute passed: File report.txt has size 1024 bytes. is equal to File rep
ort.txt has size 1024 bytes.
test attribute passed: 220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/ is equal to 220-FileZilla Server
1.7.0
220 Please visit https://filezilla-project.org/
test attribute passed: 230 Login successful. is equal to 230 Login successful.
test attribute passed: 1024 is equal to 1024
test attribute passed: 221 Goodbye. is equal to 221 Goodbye.
...
