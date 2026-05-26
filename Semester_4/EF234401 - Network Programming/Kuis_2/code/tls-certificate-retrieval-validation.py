import ssl
import socket
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO
from datetime import datetime

# Target server to test SSL connection
test_hostname = 'www.python.org'
test_port = 443

# Establish an SSL connection and retrieve peer certificate
def get_ssl_certificate(host, port):
    context = ssl.create_default_context()
    with socket.create_connection((host, port)) as sock:
        with context.wrap_socket(sock, server_hostname=host) as ssock:
            cert = ssock.getpeercert()
            return cert

# Check if certificate is still valid based on 'notAfter' field
def is_cert_valid(cert):
    notAfter = cert.get('notAfter')
    if notAfter is None:
        return False
    formatDate = '%b %d %H:%M:%S %Y %Z'
    expire_date = datetime.strptime(notAfter, formatDate)
    return datetime.utcnow() < expire_date

# Extract commonName (CN) from certificate subject
def get_common_name(cert):
    subject = cert.get('subject', [])
    for item in subject:
        for key, value in item:
            if key == 'commonName':
                return value
    return None

# NullWriter that discards output (for unittest runner)
class NullWriter(StringIO):
    def write(self, txt):
        pass

# Unit test for SSL certificate retrieval and validation
class TestTLSCertificate(unittest.TestCase):

    @patch('ssl.create_default_context')
    @patch('socket.create_connection')
    def test_get_ssl_certificate_and_validation(self, mock_create_conn, mock_create_ctx):
        mock_sock = MagicMock()
        mock_create_conn.return_value.__enter__.return_value = mock_sock

        mock_ssl_sock = MagicMock()
        mock_ssl_sock.getpeercert.return_value = {
            'subject': ((('commonName', 'www.python.org'),),),
            'notAfter': 'Dec 31 23:59:59 2099 GMT'
        }

        mock_context = MagicMock()
        mock_context.wrap_socket.return_value.__enter__.return_value = mock_ssl_sock
        mock_create_ctx.return_value = mock_context

        cert = get_ssl_certificate(test_hostname, test_port)

        self.assertIn('subject', cert)
        self.assertIn('notAfter', cert)
        cn = get_common_name(cert)
        self.assertEqual(cn, 'www.python.org')
        self.assertTrue(is_cert_valid(cert))

        print(f"Common Name (CN): {cn}")
        print(f"Certificate valid: {'YES' if is_cert_valid(cert) else 'NO (expired)'}")

if __name__ == '__main__':
    import sys
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        cert = get_ssl_certificate(test_hostname, test_port)
        cn = get_common_name(cert)
        valid = is_cert_valid(cert)
        print(f"Common Name (CN): {cn}")
        print(f"Certificate valid: {'YES' if valid else 'NO (expired)'}")
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)