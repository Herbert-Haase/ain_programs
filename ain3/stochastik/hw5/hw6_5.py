#!/home/herbert/htwg/ain3/sto/sto/bin/python

from scipy.stats import uniform, expon

coffee_amount = uniform(150, 750-150)

print("1.")
print("a)")
print(coffee_amount.cdf(500))
print("b)")
print(coffee_amount.cdf(350)-coffee_amount.cdf(250))
print("c)")
print(coffee_amount.mean())
print(coffee_amount.std())

coffee_time = expon(0, 1/4)
print("2.")
print("a)")
print(coffee_time.sf(0.5))
print("b)")
print(coffee_time.ppf(0.75))
print("c)")
print(coffee_time.mean())
print(coffee_time.std())
