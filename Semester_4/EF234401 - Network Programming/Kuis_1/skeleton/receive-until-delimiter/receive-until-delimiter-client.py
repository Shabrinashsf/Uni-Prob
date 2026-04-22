import socket
import unittest
from io import StringIO
from unittest.mock import patch, MagicMock

# Client functionality
def client_program():
    host = ?
    port = ?
    message = "Hello Server!\nThis is a message from one of your Client.\nIf you are reading this please call me back.\r\n"

    # Connect to server
    client_socket = ?
    
    # Send the message to the server
    ? 
    
    # Receive 1024 bytes response from the server
    ?
    
    # Print the original message and the received response
    print(f"Original message: {message}")
    print(f"Received response: {response}")

    # Close socket
    ?

# Unit test for the client code
class TestClient(unittest.TestCase):
    @patch('socket.socket')  # Mock the socket object
    def test_client_program(self, mock_socket):
        mock_socket_instance = MagicMock()
        mock_socket.return_value = mock_socket_instance

        # Test message
        test_message = "Hello Server!\nThis is a message from one of your Client.\nIf you are reading this please call me back.\r\n"
        
        mock_socket_instance.recv.return_value = test_message.encode()

        # Run the client program without capturing stdout
        client_program()

        # Verify connection to the correct server and port
        mock_socket_instance.connect.assert_called_with(('127.0.0.1', 12345))
        print(f"connect called with: {mock_socket_instance.connect.call_args}")

        # Verify the client sends the correct message
        mock_socket_instance.send.assert_called_with(test_message.encode())
        print(f"send called with: {mock_socket_instance.send.call_args}")

        # Verify the client receives a response
        mock_socket_instance.recv.assert_called_with(1024)
        print(f"recv called with: {mock_socket_instance.recv.call_args}")

        # Verify the client closes the socket
        mock_socket_instance.close.assert_called_once()
        print(f"close called with: {mock_socket_instance.close.call_args}")

# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass

if __name__ == '__main__':
    # Run unittest with a custom runner that suppresses output
    # Make sure to uncomment this before uploading the code to domjudge
    # runner = unittest.TextTestRunner(stream=NullWriter())
    # unittest.main(testRunner=runner, exit=False)

    # Uncomment this if you want to run the client program, not running the unit test
    client_program()