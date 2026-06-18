import sys
import socket, smtplib, ssl, unittest
from io import StringIO
from unittest.mock import patch, MagicMock

message_template = """To: {}
From: {}
Subject: Test Message from simple.py

Hello,

This is a test message sent to you.
"""


def main():
    if len(sys.argv) < 4:
        # print usage information and exit
        name = sys.argv[0]
        print("Syntax: {} server fromaddr toaddr [toaddr...]".format(name))
        sys.exit(2)

    server, fromaddr, toaddrs = sys.argv[1], sys.argv[2], sys.argv[3:]
    message = message_template.format(', '.join(toaddrs), fromaddr)

    try:
        # create the SMTP connection
        connectsmtp = smtplib.SMTP(server)

        # send the message securely
        send_message_securely(connectsmtp, fromaddr, toaddrs, message)
        
    except (socket.gaierror, socket.error, socket.herror,
            smtplib.SMTPException) as e:
        print("Your message may not have been sent!")
        print(e)
        sys.exit(1)
    else:
        s = '' if len(toaddrs) == 1 else 's'
        print("Message sent to {} recipient{}".format(len(toaddrs), s))
        connectsmtp.quit()


def send_message_securely(connection, fromaddr, toaddrs, message):
    code = connection.ehlo()[0]
    uses_esmtp = (200 <= code <= 299)
    if not uses_esmtp:
        code = connection.helo()[0]
        if isinstance(code, int) and not (200 <= code <= 299):
            print("Remote server refused HELO")
            sys.exit(2)

    if uses_esmtp and connection.has_extn('starttls'):
        print("Negotiating TLS....")
        # create a secure SSL context
        contextssl = ssl.SSLContext()

        # wrap the existing socket with the SSL context
        code = connection.starttls(context=contextssl)[0]
        connection.ehlo()
        if isinstance(code, int) and not (200 <= code <= 299):
            print("Couldn't EHLO after STARTTLS")
            sys.exit(5)
        print("Using TLS connection.")
    else:
        print("Server does not support TLS; using normal connection.")

    # send the email message
    connection.sendmail(fromaddr, toaddrs, message)


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestSmtpTls(unittest.TestCase):

    @patch('__main__.send_message_securely')
    @patch('smtplib.SMTP')
    def test_main(self, mock_smtp_cls, mock_send_securely):
        mock_connection = MagicMock()
        mock_smtp_cls.return_value = mock_connection

        with patch('sys.argv', ['smtp-tls.py', 'smtp.example.com',
                                'sender@example.com', 'recipient@example.com']):
            main()

        print(f"mock_smtp_cls.call_args: {mock_smtp_cls.call_args}")
        assert_equal(mock_send_securely.called, True)
        assert_equal(mock_connection.quit.called, True)

    @patch('ssl.SSLContext')
    def test_send_message_securely(self, mock_ssl_context):
        mock_connection = MagicMock()
        mock_connection.ehlo.return_value = (250, b'OK')
        mock_connection.has_extn.return_value = True

        fromaddr = 'sender@example.com'
        toaddrs = ['recipient@example.com']
        message = "Test message"

        send_message_securely(mock_connection, fromaddr, toaddrs, message)

        assert_equal(mock_connection.starttls.called, True)
        assert_equal(mock_connection.sendmail.called, True)
        assert_equal(mock_connection.sendmail.call_args[0][0], fromaddr)
        assert_equal(mock_connection.sendmail.call_args[0][1], toaddrs)


if __name__ == '__main__':
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
