import socket
import unittest
from io import StringIO
from unittest.mock import patch, MagicMock

# Server function
def handle_client_connection(client_socket, addr):
    print(f"Got a connection from {addr}")

    # Receive message
    data = client_socket.recv(1024).decode()

    # Reverse the message
    reversed_data = data[::-1]

    # Send back the reversed string
    client_socket.send(reversed_data.encode())

    # Close socket
    client_socket.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = '127.0.0.1'
    port = 12345

    server_socket.bind((host, port))
    server_socket.listen(1)

    print(f"Listening on {host}:{port} ...")
    try:
        while True:
            client_socket, addr = server_socket.accept()
            handle_client_connection(client_socket, addr)
    except KeyboardInterrupt:
        print("Server shutting down.")
    finally:
        server_socket.close()

# Unit test for the server
class TestServer(unittest.TestCase):
    @patch('socket.socket')
    def test_handle_client_connection(self, mock_socket):
        print("Test handle_client_connection ...")
        mock_client_socket = MagicMock()
        mock_addr = ('127.0.0.1', 12345)

        test_message = "Hello, Server! Please reverse this message."
        reversed_message = test_message[::-1]
        mock_client_socket.recv.return_value = test_message.encode()

        handle_client_connection(mock_client_socket, mock_addr)

        mock_client_socket.recv.assert_called_with(1024)
        print(f"recv called with: {mock_client_socket.recv.call_args}")

        mock_client_socket.send.assert_called_with(reversed_message.encode())
        print(f"send called with: {mock_client_socket.send.call_args}")

        mock_client_socket.close.assert_called_once()
        print(f"close called with: {mock_client_socket.close.call_args}")

    @patch('socket.socket')
    def test_start_server(self, mock_socket):
        print("Test start_server ...")
        mock_server_socket = MagicMock()
        mock_client_socket = MagicMock()
        mock_addr = ('127.0.0.1', 12345)
        test_message = "Trigger"
        mock_client_socket.recv.return_value = test_message.encode()

        mock_socket.return_value = mock_server_socket
        mock_server_socket.accept.side_effect = [(mock_client_socket, mock_addr), Exception("Done")]

        try:
            start_server()
        except Exception as e:
            if str(e) != "Done":
                raise

        print(f"accept called with: {mock_server_socket.accept.call_args}")
        mock_server_socket.bind.assert_called_once_with(('127.0.0.1', 12345))
        print(f"bind called with: {mock_server_socket.bind.call_args}")
        mock_server_socket.listen.assert_called_once_with(1)
        print(f"listen called with: {mock_server_socket.listen.call_args}")

if __name__ == '__main__':
    runner = unittest.TextTestRunner(stream=StringIO())
    unittest.main(testRunner=runner, exit=False)

    # Uncomment below to run server manually
    # start_server()
