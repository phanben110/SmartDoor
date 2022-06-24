import socket
from time import sleep

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while 1:
    sock.sendto('0'.encode(), ( "192.168.130.28", 5007 ))
    print("sent message")
    sleep(4)
