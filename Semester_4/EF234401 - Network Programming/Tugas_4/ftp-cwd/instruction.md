FTP Change Working Directory Client

Background
File Transfer Protocol (FTP) allows clients to navigate the server directory tre
e. You must implement an FTP client that changes the current working directory u
sing the ftplib library.
Task
Implement change_directory(host, username, password, path) which logs in and cha
nges the working directory to the given path.
Requirements

- Establish connection and print welcome message.
- Login and print response.
- Change directory and print response.
- Quit and print response.
- Return a confirmation message.

Constraints

- Assume server is reachable and credentials are correct.
  Output (without unit test)
  220-FileZilla Server 1.7.0
  220 Please visit https://filezilla-project.org/
  230 Login successful.
  250 CWD command successful.
  221 Goodbye.
  Changed directory to /uploads successfully.

Output (with unit test)
220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/
230 Login successful.
250 CWD command successful.
221 Goodbye.
login called with call('user', '123')
cwd called with call('/uploads')
test attribute passed: Changed directory to /uploads successfully. is equal to C
hanged directory to /uploads successfully.
test attribute passed: 220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/ is equal to 220-FileZilla Server
1.7.0
220 Please visit https://filezilla-project.org/
test attribute passed: 230 Login successful. is equal to 230 Login successful.
test attribute passed: 250 CWD command successful. is equal to 250 CWD command s
uccessful.
test attribute passed: 221 Goodbye. is equal to 221 Goodbye.
...
