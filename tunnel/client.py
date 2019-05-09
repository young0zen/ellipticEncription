#! /usr/local/bin/python

import socket
import sys
import getopt
from thread import *

host = "localhost"
port = 23456
isServer = False

def serverThreadFunction(conn):
    while ((data = conn.recv(65536))):
        print(data)

    conn.close()

def setup_socket(family, type):
    try:
        sock = socket.socket(family, type)
    except socket.error, message:
        print (message)
        sys.exit(1)
    return sock

def launch_server(port):
    sock = setup_socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.bind(('', port))
    except socket.error, message:
        print "Bind failed. Error " + str(message[0]) + ": " + message[1]
        sock.close()
        sys.exit(1)

    sock.listen(10)

    while True:
        conn, addr = sock.accept()
        start_new_thread(serverThreadFunction, (conn,))

    sock.close()

def connect_to_server(host, port):
    sock = setup_socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        remote_addr = socket.gethostbyname(host)
    except socket.gaierror:
        print "Host name could not be resolved. Aborting..."
        sock.close()
        sys.exit(1)

    sock.connect((remote_addr, port))

    while (msg = input()):
        sock.send(msg.encode("utf-8"))
    sock.close()

# main
opts, args = getopt.getopt(sys.argv[1:], "h:p:s")
for op, value in opts:
    if op == "-h":
        host = value
    elif op == "-p":
        port = int(value)
    elif op == "-s":
        isServer = True

if (isServer):
    launch_server(port)
else:
    connect_to_server(host, port)
