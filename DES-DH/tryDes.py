from pyDes import *
from binascii import b2a_hex,a2b_hex
import base64
# data = "http://www.google.com"

class DES(object):
    def __init__(self,key,iv):
        self.key = key
        self.iv = iv

    def encrypt(self,data):
        k = des(self.key,CBC,self.iv,pad=None,padmode=PAD_PKCS5)
        code = k.encrypt(data)
        return code

    def decrypt(self,code):
        k = des(self.key,CBC,self.iv,pad=None,padmode=PAD_PKCS5)
        words = k.decrypt(code)
        return words


if __name__ == '__main__':
    key = '12345678'
    iv = '23456789'
    data = 'Please encrypt my data!'
    des_test = DES(key, iv)
    code = des_test.encrypt(data)
    print(code)
    words = des_test.decrypt(code)
    print(words)
