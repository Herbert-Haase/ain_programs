#!/home/herbert/htwg/ain3/sto/sto/bin/python

from scipy.stats import uniform, binom

# Gegebene Parameter
N = 1000
p1 = 0.007
sensitivitaet = 0.85
spezifitaet = 0.99

p_test_neg_given_inf = 1 - sensitivitaet

p_nicht_inf = 1 - p1

p_test_neg_given_nicht_inf = spezifitaet

p_test_neg = (p_test_neg_given_inf * p1) + \
    (p_test_neg_given_nicht_inf * p_nicht_inf)

p2 = (p_test_neg_given_inf * p1) / p_test_neg
print("--- Aufgabe a) ---")
print(f"Wahrscheinlichkeit p2 (Infiziert trotz neg. Test): {p2:.6f} (ca. {p2*100:.3f}%)")

X1 = binom(n=N, p=p1)
X2 = binom(n=N, p=p2)
print("--- Aufgabe b) ---")
print(f"X1 ~ B({N},{p1})")
print(f"X2 ~ B({N},{p2})")

print("--- Aufgabe c) ---")
print(f"X1.mean(): {X1.mean()}")
print(f"X2.mean(): {X2.mean()}")

print("--- Aufgabe d) ---")
print(f"X1.pmf(0): {X1.pmf(0)}")
print(f"X2.pmf(0): {X2.pmf(0)}")

print("--- Aufgabe e) ---")
print(f"X1.ppf: {X1.ppf(0.99)}")
print(f"X2.ppf: {X2.ppf(0.99)}")
