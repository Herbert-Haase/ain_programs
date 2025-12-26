#!/usr/bin/python3

# from urllib.request import urlopen
import hashlib
import itertools
import string

target = "dbc3337f151da4276572aaaa424cddb0d89a5422862"


def compare2hash(combi):
    pw = ''.join(combi)
    pw_hash = hashlib.sha1(pw.encode("utf-8")).hexdigest()
    if (target == pw_hash):
        return True
    else:
        return False


characters = string.ascii_letters + string.digits
combination_len = 6
combinations = itertools.product(characters, repeat=combination_len)

result = next((''.join(i) for i in combinations if compare2hash(i)), None)
print(result)

# └── ❯ /bin/time ./pw_cracker.py
# None
# 41861.81user 0.79system 11:38:46elapsed 99%CPU (0avgtext+0avgdata 16152maxresident)
# 0inputs+0outputs (0major+1420minor)pagefaults 0swaps
