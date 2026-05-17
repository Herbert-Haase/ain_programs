#!/usr/bin/python3
import sys

def fakultaet(c, n) :
    while True :
        if (n == 0) :
            return c(1)
        c = lambda f, c = c, n = n : c(n * f)
        n = n - 1

n = int(sys.argv[1])
fakultaet(lambda f: print(f), n)
