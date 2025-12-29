# Source - https://stackoverflow.com/a
# Posted by AbdulMueed, modified by community. See post 'Timeline' for change history
# Retrieved 2025-12-30, License - CC BY-SA 3.0

import socket

host = socket.gethostname()
port = 8080                  # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
s.sendall(b'Hello, world')
data = s.recv(1024)
s.close()
print('Received', repr(data))
