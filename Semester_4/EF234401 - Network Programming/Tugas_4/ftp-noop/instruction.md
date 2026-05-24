FTP Keep Alive (NOOP)

Description
In this problem, you are asked to implement an FTP client that
connects to an FTP server and sends a NOOP (No Operation) command
to keep the connection alive. The NOOP command is commonly used
to check if the server is still responsive without performing
any actual operation.

Method
Your task is to implement the keep_alive function that:

- Connects to the FTP server at the given host
- Prints the welcome message from the server
- Logs in with the given username and password
- Sends the NOOP command using voidcmd('NOOP') and prints the response
- Quits the connection
- Returns "NOOP command sent successfully."

Input
There is no input for this problem.
Output
The FTP server responses (verified via unit test).
Sample Output
220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/
230 Login successful.
200 NOOP ok.
221 Goodbye.
login called with call('user', '123')
voidcmd called with call('NOOP')
test attribute passed: NOOP command sent successfully. is equal to NOOP command
sent successfully.
test attribute passed: 220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/ is equal to 220-FileZilla Server
1.7.0
220 Please visit https://filezilla-project.org/
test attribute passed: 230 Login successful. is equal to 230 Login successful.
test attribute passed: 200 NOOP ok. is equal to 200 NOOP ok.
test attribute passed: 221 Goodbye. is equal to 221 Goodbye.
