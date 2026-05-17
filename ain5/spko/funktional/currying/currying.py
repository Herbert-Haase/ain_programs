#!/usr/bin/python3
# Beispiel aus de.wikipedia.org/wiki/Currying

# Definition und Aufruf einer Funktion mit zwei Parametern:
def uncurried_add(x, y):
    return x + y

n = uncurried_add(3, 5)
print(n)

# das gleiche mit einer Funktion und einem Lambda mit je einem Parameter:
def curried_add(x):
    return lambda y: x + y

n = curried_add(3)(5)
print(n)

add_three = curried_add(3)
n = add_three(5)
print(n)

