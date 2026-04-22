import socket
import unittest
from io import StringIO
from unittest.mock import patch, MagicMock

# recv_until function
def recv_until(?, ?):
    # Receive 16 bytes message from client
    message = ?
    
    # Use while loop to check for delimiter in message
    while ?:
        # If delimiter not found yet, receive 16 more bytes from client
        more = ? 
        if not more:
            raise IOError('received {!r} then socket closed'.format(message))
        # Append more to original message
        ?
    return message

# Server function
def handle_client_connection(client_socket, addr):
    """Handle a single client connection."""
    print(f"Got a connection from {addr}")
    
    # Receive message from client
    data = recv_until(?, '?')
    
    # Send message back to client
    ?
    
    # Close the connection
    ?

def start_server():
    """Start the server and listen for incoming connections."""
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = '?'  # Localhost
    port = ?        # Port to listen on
    # binding to address
    ?
    # listen to a single connection
    ?
    print(f"Listening on {host}:{port} ...")
    try:
        while True:
            client_socket, addr = server_socket.accept()
            handle_client_connection(client_socket, addr)
    except KeyboardInterrupt:
        print("Server shutting down.")
    finally:
        server_socket.close()

class ExitLoopException(Exception):
    pass

# 'Null' stream to discard output (not used here)
class NullWriter(StringIO):
    def write(self, txt):
        pass

class TestServer(unittest.TestCase):
    @patch('socket.socket')
    def test_handle_client_connection(self, mock_socket):
        """Test handling of a client connection."""
        print('Test handle_client_connection ...')
        mock_client_socket = MagicMock()
        mock_addr = ('127.0.0.1', 12345)

        # Simulate recv returning 16-byte chunks ending with \r\n
        full_message = (
            "Hello Server!\nThis is a message from one of your Client.\n"
            "If you are reading this please call me back.\r\n"
        )
        chunks = [full_message[i:i+16].encode() for i in range(0, len(full_message), 16)]

        # Return each chunk on successive calls to recv
        mock_client_socket.recv.side_effect = chunks

        handle_client_connection(mock_client_socket, mock_addr)

        # Check that send was called with the full message
        mock_client_socket.send.assert_called_once_with(full_message.encode())
        print(f"send called with: {mock_client_socket.send.call_args}")

        # Verify that the connection was closed
        mock_client_socket.close.assert_called_once()
        print(f"close called with: {mock_client_socket.close.call_args}")

    @patch('socket.socket')
    def test_start_server(self, mock_socket):
        """Test starting of the server and listening for connections."""
        print('Test start_server ...')
        mock_server_socket = MagicMock()
        mock_client_socket = MagicMock()
        mock_addr = ('127.0.0.1', 12345)

        # Simulate recv for one full message
        test_message = "Test message for start_server\r\n"
        mock_client_socket.recv.side_effect = [
            test_message[:16].encode(), test_message[16:].encode()
        ]

        mock_socket.return_value = mock_server_socket
        mock_server_socket.accept.side_effect = [(mock_client_socket, mock_addr), ExitLoopException]

        try:
            start_server()
        except ExitLoopException:
            pass  # Expected to break the loop for test

        # Check bind and listen
        mock_server_socket.bind.assert_called_once_with(('127.0.0.1', 12345))
        mock_server_socket.listen.assert_called_once_with(1)
        
        print(f"bind called with: {mock_server_socket.bind.call_args}")
        print(f"listen called with: {mock_server_socket.listen.call_args}")


if __name__ == '__main__':
    # Use sys.stdout to make print output visible in console
    # runner = unittest.TextTestRunner(stream=NullWriter())
    # unittest.main(testRunner=runner, exit=False)

    # Uncomment the following line if you want to run the server directly, not the unit test
    start_server()