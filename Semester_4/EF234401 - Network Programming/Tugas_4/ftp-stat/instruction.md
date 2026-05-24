FTP Server Status (STAT)

Description
In this problem, you are asked to implement an FTP client that
connects to an FTP server and sends a STAT command to retrieve
the current status of the FTP server. The STAT command returns
information about the server's current state and configuration.

Method
Your task is to implement the get_status function that:

- Connects to the FTP server at the given host
- Prints the welcome message from the server
- Logs in with the given username and password
- Sends the STAT command using voidcmd('STAT') and prints the response
- Quits the connection
- Returns the STAT response message

Input
There is no input for this problem.
Output
The FTP server responses (verified via unit test).
Sample Output
220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/
230 Login successful.
211-FTP server status
211 End of status.
221 Goodbye.
login called with call('user', '123')
voidcmd called with call('STAT')
test attribute passed: 211-FTP server status
211 End of status. is equal to 211-FTP server status
211 End of status.
test attribute passed: 220-FileZilla Server 1.7.0
220 Please visit https://filezilla-project.org/ is equal to 220-FileZilla Server
1.7.0
220 Please visit https://filezilla-project.org/
test attribute passed: 230 Login successful. is equal to 230 Login successful.
test attribute passed: 211-FTP server status
211 End of status. is equal to 211-FTP server status
211 End of status.
test attribute passed: 221 Goodbye. is equal to 221 Goodbye.
