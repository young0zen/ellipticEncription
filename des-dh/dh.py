#! /usr/local/bin/python

import random
import math

def isPrime(number):
    if number <= 0:
        return False
    if number == 1:
        return True

    for i in range(2, number):
        if number % i == 0:
            return False

    return True


# this function must be supplied with a prime number, it will return -1
# otherwise
def get_generator_of(p):
    if (not isPrime(p)):
        return -1

    tmp = 2
    while True:

        if (tmp ** (p - 1) % p == 1):
            num = 2
            flag = True
            for i in range(2, p - 1):
                if tmp ** i % p == 1:
                    flag = False
                    break

            if flag == True:
                return tmp

        tmp += 1

def compute_public_val(generator, num, p):
    return (generator ** num) % p

def compute_key(peer, own, p):
    return (peer ** own) % p
