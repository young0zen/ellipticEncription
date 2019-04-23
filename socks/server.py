#! /usr/local/bin/python3

import socket
import sys
import getopt
from _thread import *
import selectors
import time

sel = selectors.DefaultSelector()

host = "localhost"
port = 23456
isServer = False

connection_map_dic = {}

def setup_socket(family, type):
    try:
        sock = socket.socket(family, type)
    except (socket.error, message):
        print (message)
        sys.exit(1)
    return sock


def connect_to_server(host, port):
    sock = setup_socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        remote_addr = socket.gethostbyname(host)
    except socket.gaierror:
        print ("Host name could not be resolved. Aborting...")
        sock.close()
        sys.exit(1)

    sock.connect((remote_addr, port))
    sel.register(sock, selectors.EVENT_READ, read)

def accept(sock, mask):
    conn, addr = sock.accept()  # Should be ready
    print('accepted', conn, 'from', addr)
    conn.setblocking(False)
    sel.register(conn, selectors.EVENT_READ, read)

def read(conn, mask):
    data = conn.recv(65536)  # Should be ready
    print (type(data))
    if data:
        conn.send(data)  # Hope it won't block
    else:
        # print('closing', conn)
        sel.unregister(conn)
        conn.close()

# main
opts, args = getopt.getopt(sys.argv[1:], "h:p:s")
for op, value in opts:
    if op == "-h":
        host = value
    elif op == "-p":
        port = int(value)
    elif op == "-s":
        isServer = True

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except (socket.error, message):
    print (message)
    sys.exit(1)

try:
    sock.bind(('', port))
except (socket.error, message):
    print ("Bind failed. Error " + str(message[0]) + ": " + message[1])
    sock.close()
    sys.exit(1)

sock.listen(100)
sock.setblocking(False)
sel.register(sock, selectors.EVENT_READ, accept)

while True:
    events = sel.select()
    for key, mask in events:
        callback = key.data
        callback(key.fileobj, mask)
