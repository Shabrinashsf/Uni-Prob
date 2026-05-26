import ? 


# Set up logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class Message:
    def __init__(self, ?, ?, ?):
        self.username = ?
        self.text = ?
        self.timestamp = ?

    @staticmethod
    def deserialize(?):
        message_dict = ?
        timestamp = ?
        return ?

    def serialize(self):
        return ?

def main():
    # create socket, bind, and listen
    server_socket = ?
    ?
    ?
    server_socket.setblocking(False)

    sockets_list = ?

    logger.info(?)

    while True:
        read_sockets, _, exception_sockets = ?

        for notified_socket in read_sockets:
            if notified_socket == ?:
                # accept client
                client_socket, client_address = ?
                client_socket.setblocking(False)

                # append to sockets_list
                ?
                logger.info(?)
            else:
                try:
                    # receive data
                    data = ?
                    if data:
                        message = ?
                        logger.info(?)
                        logger.info(f"Username: {?}")
                        logger.info(f"Text: {?}")
                        logger.info(f"Timestamp: {?}")
                except Exception as e:
                    logger.info(f"Exception: {e}")
                    # remove socket from sockets_list
                    ?
                    # close socket
                    ?

        for notified_socket in exception_sockets:
            # remove socket from sockets_list
            ?
            # close socket
            ?


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass

def assert_true_any(parameter1, parameter2):
    found = False
    for message in parameter2:
        if parameter1 in message:
            found = True
            break
    
    print(f'test attribute passed: {parameter1} found in log messages' if found else f'test attribute failed: {parameter1} not found in log messages')
    # return found

class TestChatServer(unittest.TestCase):
    
    @patch('select.select')
    @patch('socket.socket')
    def test_server_main(self, mock_socket_class, mock_select):
        mock_server_socket = MagicMock()
        mock_client_socket = MagicMock()
        
        mock_socket_class.return_value = mock_server_socket
        mock_server_socket.accept.return_value = (mock_client_socket, ('127.0.0.1', 54321))
        
        # Initial call to select() returns the server socket as ready to accept
        mock_select.side_effect = [
            ([mock_server_socket], [], []),
            ([mock_client_socket], [], []),
            KeyboardInterrupt()  # To break out of the infinite loop
        ]
        
        # Mock data received from the client
        test_message = Message("Alice", "Hello, World!", datetime.now())
        serialized_message = test_message.serialize()
        mock_client_socket.recv.return_value = serialized_message
        
        with self.assertLogs(logger, level='INFO') as log:
            with self.assertRaises(KeyboardInterrupt):
                main()
            
            # Check if the server accepted a new connection
            mock_server_socket.accept.assert_called_once()
            mock_client_socket.setblocking.assert_called_once_with(False)
            
            # Check if the server received and deserialized the message correctly
            mock_client_socket.recv.assert_called_once_with(1024)
            
            # Verify log messages
            log_output = log.output
            
            assert_true_any("Received message:", log_output)
            assert_true_any("Username: Alice", log_output)
            assert_true_any("Text: Hello, World!", log_output) 

if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        main()
    
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
