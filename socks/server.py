#! /usr/local/bin/python3

import socket
import sys
import getopt
from _thread import *
import selectors

sel = selectors.DefaultSelector()

#host = "localhost"
port = 23456

# A map from connection id to two-tuple (client_socket, to_remote_socket)
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
        return -1

    try:
        sock.connect((remote_addr, port))
    except socket.error:
        print ("Connection failed.")
        sock.close()
        return -1;

    return sock

def accept(sock, mask):
    conn, addr = sock.accept()  # Should be ready
    print('accepted', conn, 'from', addr)
    conn.setblocking(False)
    sel.register(conn, selectors.EVENT_READ, (read, get_available_connection_id()))

def read(conn, id):
    # print (conn, "id:", id)

    data = conn.recv(65536)  # Should be ready
    if not data: # eof or error
        socket_pair = connection_map_dic.get(id, None)
        if (socket_pair == None): # not in the dictionary
            print ("Unregistering one")
            sel.unregister(conn)
            conn.close()
        else:
            print ("Unregistering both")
            sel.unregister(socket_pair[0])
            sel.unregister(socket_pair[1])
            socket_pair[0].close()
            socket_pair[1].close()
            del connection_map_dic[id]
    else:
        socket_pair = connection_map_dic.get(id, None)
        if (socket_pair == None): # not in the dictionary
            msg = data.decode("utf-8")
            msg = msg.strip()
            host_port = msg.split(':')
            print ("Connecting to " + host_port[0] + ", port " + host_port[1])
            to_server_sock = connect_to_server(host_port[0], int(host_port[1]))
            if (to_server_sock == -1):
                print ("Cannot connect to server.")
            else:
                connection_map_dic[id] = (conn, to_server_sock)
                sel.register(to_server_sock, selectors.EVENT_READ, (read, id))
        # send it to the other side
        elif (conn == socket_pair[0]):
            socket_pair[1].send(data)
        elif (conn == socket_pair[1]):
            socket_pair[0].send(data)


connection_id = 0
def get_available_connection_id():
    global connection_id
    connection_id = connection_id + 1
    return connection_id

# main
opts, args = getopt.getopt(sys.argv[1:], "h:p:")
for op, value in opts:
    if op == "-h":
        pass
        #host = value
    elif op == "-p":
        port = int(value)

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except (socket.error, message): #TODO: check python3 grammer
    print (message)
    sys.exit(1)

try:
    sock.bind(('', port))
except (socket.error):
    print ("Bind failed.")
    sock.close()
    sys.exit(1)

sock.listen(100)
sock.setblocking(False)
sel.register(sock, selectors.EVENT_READ, (accept, 0))

while True:
    events = sel.select()
    for key, mask in events:
        callback = key.data[0]
        callback(key.fileobj, key.data[1])
