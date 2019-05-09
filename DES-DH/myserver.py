import socket
from dh import *
from tryDes import *



server = socket.socket()
server.bind(("127.0.0.1",12345))
server.listen(1)
conn, addr = server.accept()
print("new conn:",addr)

p = 11
genP = get_generator_of(p)
if genP == -1:
    print("Invalid P......")
print("Please input an exponential:")
exp = int(input())
serverPublicKey = compute_public_val(genP, exp, p)
print("serverPublicKey:",serverPublicKey)
status = conn.recv(1024)
if status.decode() == "ready":
    conn.send(b"ok")
    transferData = str(serverPublicKey).encode()
    conn.send(transferData)
    clientPublicKey = conn.recv(1024)
    clientPublicKey = int(clientPublicKey.decode())
    print("recv clientPublicKey:",clientPublicKey)
    commonKey = compute_key(clientPublicKey, exp, p)
    print("CommonKey:",commonKey)

    commonKey = str(commonKey)
    if len(commonKey) != 8:
        length = len(commonKey) % 8
        for i in range(8 - length):
            commonKey += '0'
    print("8 bit commonKey:", commonKey)

    iv = "23456789"
    des = DES(commonKey,iv)
    code = conn.recv(1024)
    data = des.decrypt(code)
    print("client data:",data)
server.close()

