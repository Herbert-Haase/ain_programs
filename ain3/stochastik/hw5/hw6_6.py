#!/home/herbert/htwg/ain3/sto/sto/bin/python

from scipy.stats import norm

alt = norm(300, 100)
print("a)")
print("M2~norm(300,100)")
print("b)")
print(alt.cdf(350))
print("c)")
print(1-alt.cdf(200))
print("d)")
print(0)
print("e)")
print(alt.ppf(0.95))


