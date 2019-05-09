#! /usr/local/bin/python3

import socket
import sys
import getopt
from _thread import *
import selectors
import PseudoIPPacket

sel = selectors.DefaultSelector()

port = 23456
next_hop_port = 0
next_hop_host = "localhost"

# A map from connection id to two-tuple (client_socket, to_remote_socket)
connection_map_dic = {}

def convert_ip_family(bytes):
    if (len(bytes) < 16):
        print("Error: unrecognized header format.")
        return None

    bytes = bytes.decode("utf-8")
    header = bytes[:16]
    if (header == "I AM IPV4 HEADER"):
        bytes = "I AM IPV6 HEADER" + bytes
    elif (header == "I AM IPV6 HEADER"):
        bytes = bytes[16:]
    else:
        print("Error: unrecognized header format.")
        return None

    return bytes.encode("utf-8")

def setup_socket(family, type):
    try:
        sock = socket.socket(family, type)
    except socket.error as err:
        print ("Error while setting up socket.", err)
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
        data = convert_ip_family(data)
        if (data == None): # unrecognized protocol
            return

        socket_pair = connection_map_dic.get(id, None)
        if (socket_pair == None): # not in the dictionary

            host_port = [next_hop_host, next_hop_port]

            to_server_sock = connect_to_server(host_port[0], host_port[1])
            if (to_server_sock == -1):
                print ("Cannot connect to server.")
            else:
                connection_map_dic[id] = (conn, to_server_sock)
                sel.register(to_server_sock, selectors.EVENT_READ, (read, id))
                print ("Connected to " + host_port[0] + ", port " + str(host_port[1]))
                to_server_sock.send(data) # forward it to server

        # send it to the other side
        elif (conn == socket_pair[0]):
            # add packet header here and send it
            socket_pair[1].send(data)
        elif (conn == socket_pair[1]):
            socket_pair[0].send(data)


connection_id = 0
def get_available_connection_id():
    global connection_id
    connection_id = connection_id + 1
    return connection_id

# main
opts, args = getopt.getopt(sys.argv[1:], "h:p:n:")
for op, value in opts:
    if op == "-h":
        next_hop_host = value
    elif op == "-p":
        port = int(value)
    elif op == "-n":
        next_hop_port = int(value)

sock = setup_socket(socket.AF_INET, socket.SOCK_STREAM)

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
