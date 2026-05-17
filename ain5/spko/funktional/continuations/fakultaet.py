#!/usr/bin/python3
import sys

def fakultaet(n) :
    if (n == 0) :
        return 1
    return n * fakultaet(n - 1)

n = int(sys.argv[1])
print(fakultaet(n))
