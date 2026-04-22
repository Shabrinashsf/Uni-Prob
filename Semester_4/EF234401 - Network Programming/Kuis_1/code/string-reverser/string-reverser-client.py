import socket
import unittest
from io import StringIO
from unittest.mock import patch, MagicMock

# Client functionality
def client_program():
    host = '127.0.0.1'  # localhost
    port = 12345  # 12345
    message = "Hello, Server! Please reverse this message."

    # create socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect to server
    client_socket.connect((host, port))

    # Send the message to the server
    client_socket.send(message.encode())

    # Receive the reversed message from the server
    reversed_message = client_socket.recv(1024).decode()

    # Print the original message and the received reversed string
    print(f"Original message: {message}")
    print(f"Received reversed: {reversed_message}")

    # close socket
    client_socket.close()

# Unit test for the client code
class TestClient(unittest.TestCase):
    @patch('socket.socket')  # Mock the socket object
    def test_client_program(self, mock_socket):
        mock_socket_instance = MagicMock()
        mock_socket.return_value = mock_socket_instance

        # Test message
        test_message = "Hello, Server! Please reverse this message."
        expected_reversed = ".egassem siht esrever esaelP !revreS ,olleH"
        mock_socket_instance.recv.return_value = expected_reversed.encode()

        # Run the client program
        client_program()

        # Output expected interaction
        print(f"connect called with: {mock_socket_instance.connect.call_args}")
        print(f"send called with: {mock_socket_instance.send.call_args}")
        print(f"recv called with: {mock_socket_instance.recv.call_args}")
        print(f"close called with: {mock_socket_instance.close.call_args}")

        # Verify the connection, send, receive, and close methods
        mock_socket_instance.connect.assert_called_with(('127.0.0.1', 12345))
        mock_socket_instance.send.assert_called_with(test_message.encode())
        mock_socket_instance.recv.assert_called_with(1024)
        mock_socket_instance.close.assert_called_once()

# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass

if __name__ == '__main__':
    # Run unit test using null output stream
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)

    # Uncomment this to run the client manually
    # client_program()
