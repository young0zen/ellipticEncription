#! /usr/local/bin/python

import dh

p = int(input())
gen = dh.get_generator_of(p)
if (gen == -1):
    print ("Invalid Input. Aborting...")
    quit()

priA = 10
pubA = dh.compute_public_val(gen, priA, p)

priB = 11
pubB = dh.compute_public_val(gen, priB, p)

ackA = dh.compute_key(pubB, priA, p)
ackB = dh.compute_key(pubA, priB, p)

if ackA == ackB:
    print ("Success!")
else:
    print ("Fail")
# print ("ackA: %r" %ackA)