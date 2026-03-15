import socket
import unittest
import sys
from io import StringIO
from unittest.mock import patch, MagicMock


files = {
    "example.txt": "Hello, this is the content of example.txt",
}

def handle_connection(conn, addr):
    print(f"Connected by {?}")
    try:
        # receive message and decode bytes
        filename = ?

        # get file content from files variable in line 9
        file_content = ?

        # send file content
        conn?
    finally:
        # close socket
        ?

def start_server():
    # create socket
    server_socket = ?

    # define address
    host = ?
    port = ?

    # bind address to socket
    ?

    # listen
    ?
    print(f"Server listening on port {?}...")

    try:
        while True:
            # accept connection
            conn, addr = ?
            handle_connection(?, ?)
    except KeyboardInterrupt:
        print("Server shutting down.")
    finally:
        # close server socket
        ?

class ExitLoopException(Exception):
    pass

# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass

class TestFileServer(unittest.TestCase):
    @patch('socket.socket')
    def test_file_download_existing(self, mock_print):
        print('Testing file download existing ...')
        # Setup
        mock_conn = MagicMock()
        mock_conn.recv.return_value = b"example.txt"
        addr = ('127.0.0.1', 12345)
        
        # Test
        handle_connection(mock_conn, addr)

        mock_conn.recv.assert_called_with(1024)
        print(f"recv called with: {mock_conn.recv.call_args}")
        
        # Assertions
        mock_conn.sendall.assert_called_with(b"Hello, this is the content of example.txt")
        print(f"sendall called with: {mock_conn.sendall.call_args}")

        mock_conn.close.assert_called_once()
        print(f"close called with: {mock_conn.close.call_args}")

    @patch('socket.socket')
    def test_file_download_non_existing(self, mock_print):
        print('Testing file download not exist ...')
        # Setup
        mock_conn = MagicMock()
        mock_conn.recv.return_value = b"non_existing_file.txt"
        addr = ('127.0.0.1', 12345)
        
        # Test
        handle_connection(mock_conn, addr)

        mock_conn.recv.assert_called_with(1024)
        print(f"recv called with: {mock_conn.recv.call_args}")
        
        # Assertions
        mock_conn.sendall.assert_called_with(b"File not found.")
        print(f"sendall called with: {mock_conn.sendall.call_args}")

        mock_conn.close.assert_called_once()
        print(f"close called with: {mock_conn.close.call_args}")

if __name__ == '__main__':
    # uncomment this to test the server on localhost
    # start_server()

    # run unit test
    # make sure to uncomment this before submitting to domjudge
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
