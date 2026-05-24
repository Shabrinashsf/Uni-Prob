Hello over UDP (Client)

## Problem description

A client wants to send a greeting to a UDP server and receive a reply. Your task
is to implement the UDP client so that:

- It sends the message "Hello, Server!" to the server at IP 127.0.0.1 and port 1

2345.

- It waits for a reply from the server and prints the message received.

The expected reply from the server is: "Hello, Client!".
Input

---

There is no input to this program from stdin.
Output

---

Your program must output (without unit test) exactly one line to stdout as follo
ws:
Received from server: Hello, Client!
Output with unit test is shown below:
Received from server: Hello, Client!
sendto called with: call(b'Hello, Server!', ('127.0.0.1', 12345))
recvfrom called with: call(1024)
close called with: call()
Implementation constraints

---

- You must use the socket module and the UDP protocol (SOCK_DGRAM).
- The server is assumed to be running at 127.0.0.1 on UDP port 12345.
- Your implementation must not use any external libraries except standard Python
  modules.
- Ensure the socket is properly closed after communication.
