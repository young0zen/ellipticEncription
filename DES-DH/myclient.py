import socket
from dh import *
from tryDes import *


if __name__ == '__main__':
    client = socket.socket()
    client.connect(("127.0.0.1", 12345))
    p = 11
    genP = get_generator_of(p)
    if genP == -1:
        print("Invalid P......")
    print("Please input an exponential:")
    exp = int(input())
    clientPublicKey = compute_public_val(genP, exp, p)
    print("clientPublicKey:",clientPublicKey)
    client.send(b"ready")
    msg = client.recv(1024)
    if msg.decode() == "ok":
        serverPublicKey = client.recv(1024)
        transferData = str(clientPublicKey)
        transferData = transferData.encode()
        client.send(transferData)
        if serverPublicKey.decode() == '':
            print("Invalid serverPublikKey")
        serverPublicKey = int(serverPublicKey.decode())
        print("recv serverPublicKey:",serverPublicKey)
        commonKey = compute_key(serverPublicKey, exp, p)
        print("CommonKey:",commonKey)

        commonKey = str(commonKey)
        if len(commonKey) != 8:
            length = len(commonKey) % 8
            for i in range(8-length):
                commonKey += '0'
        print("8 bit commonKey:", commonKey)


        iv = "23456789"
        data = 'Please encrypt my data!'
        des = DES(commonKey, iv)
        code = des.encrypt(data)
        print("client code:",code)
        client.send(code)

    client.close()




