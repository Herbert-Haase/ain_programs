#!/usr/bin/python3
import sys

def fakultaet(c, n) :
    if (n == 0) :
        return c(1)
    fakultaet(lambda f : c(n * f), n - 1)

n = int(sys.argv[1])
fakultaet(lambda f: print(f), n)
