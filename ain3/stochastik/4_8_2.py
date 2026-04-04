import numpy as np

# Gemeinsame Wahrscheinlichkeitsverteilung P(X,Y)
# X = 1: wenig Sonne, X = 2: viel Sonne
# Y = 0,1,2: Anzahl verkaufter Eiskugeln pro Stunde

# Wahrscheinlichkeitstabelle
prob_table = {
    (1, 0): 0.1,
    (1, 1): 0.2,
    (1, 2): 0.1,
    (2, 0): 0.1,
    (2, 1): 0.3,
    (2, 2): 0.2
}

# Werte von X und Y
X_vals = [1, 2]
Y_vals = [0, 1, 2]

# Randverteilungen aus Aufgabe 4.8.1 (bereits bekannt)
P_X = {1: 0.4, 2: 0.6}
P_Y = {0: 0.2, 1: 0.5, 2: 0.3}

# Erwartungswerte aus Aufgabe 4.8.1 (bereits bekannt)
E_X = sum(x * P_X[x] for x in X_vals)
E_Y = sum(y * P_Y[y] for y in Y_vals)

print("=" * 60)
print("TEILAUFGABE 4.8.2")
print("=" * 60)

# a) Kovarianz Cov(X,Y)
print("\na) Kovarianz Cov(X,Y):")
print("-" * 40)

# Cov(X,Y) = E[XY] - E[X]·E[Y]
E_XY = sum(x * y * prob_table[(x, y)] for x in X_vals for y in Y_vals)

Cov_XY = E_XY - E_X * E_Y

print(f"E[X] = {E_X}")
print(f"E[Y] = {E_Y}")
print(f"E[XY] = {E_XY}")
print(f"Cov(X,Y) = E[XY] - E[X]·E[Y] = {E_XY} - {E_X}·{E_Y}")
print(f"Cov(X,Y) = {Cov_XY}")

# b) Korrelationskoeffizient ρ(X,Y)
print("\n\nb) Korrelationskoeffizient ρ(X,Y):")
print("-" * 40)

# Varianzen berechnen (aus 4.8.1)
Var_X = sum(x**2 * P_X[x] for x in X_vals) - E_X**2
Var_Y = sum(y**2 * P_Y[y] for y in Y_vals) - E_Y**2

# Standardabweichungen
sigma_X = np.sqrt(Var_X)
sigma_Y = np.sqrt(Var_Y)

# Korrelationskoeffizient
rho_XY = Cov_XY / (sigma_X * sigma_Y)

print(f"Var(X) = {Var_X}")
print(f"Var(Y) = {Var_Y}")
print(f"σ(X) = {sigma_X:.6f}")
print(f"σ(Y) = {sigma_Y:.6f}")
print(f"ρ(X,Y) = Cov(X,Y) / (σ(X)·σ(Y))")
print(f"ρ(X,Y) = {Cov_XY} / ({sigma_X:.6f}·{sigma_Y:.6f})")
print(f"ρ(X,Y) = {rho_XY:.6f}")

# c) Unabhängigkeit prüfen
print("\n\nc) Sind X und Y unabhängig?")
print("-" * 40)

independent = True
for x in X_vals:
    for y in Y_vals:
        p_xy = prob_table[(x, y)]
        p_x_times_p_y = P_X[x] * P_Y[y]
        if not np.isclose(p_xy, p_x_times_p_y):
            independent = False
            print(f"P(X={x}, Y={y}) = {p_xy} ≠ P(X={x})·P(Y={y}) = {p_x_times_p_y}")
            break
    if not independent:
        break

if independent:
    print("Ja, X und Y sind unabhängig.")
    print("(Es gilt P(X=x, Y=y) = P(X=x)·P(Y=y) für alle x,y)")
else:
    print("\nNein, X und Y sind NICHT unabhängig.")
    print("Begründung: Es existiert mindestens ein Paar (x,y), für das")
    print("P(X=x, Y=y) ≠ P(X=x)·P(Y=y) gilt.")

# d) Varianz der Summe Var(X+Y)
print("\n\nd) Varianz der Summe Var(X+Y):")
print("-" * 40)

# Var(X+Y) = Var(X) + Var(Y) + 2·Cov(X,Y)
Var_X_plus_Y = Var_X + Var_Y + 2 * Cov_XY

print(f"Var(X+Y) = Var(X) + Var(Y) + 2·Cov(X,Y)")
print(f"Var(X+Y) = {Var_X} + {Var_Y} + 2·{Cov_XY}")
print(f"Var(X+Y) = {Var_X_plus_Y}")

# e) Interpretation
print("\n\ne) Interpretation des Zusammenhangs:")
print("-" * 40)
print(f"Kovarianz: Cov(X,Y) = {Cov_XY}")
print(f"Korrelationskoeffizient: ρ(X,Y) = {rho_XY:.6f}")
print()
if Cov_XY > 0:
    print("➤ Positive Kovarianz und Korrelation bedeuten:")
    print("  Je mehr Sonnenschein (höherer X-Wert), desto mehr")
    print("  Eiskugeln werden im Durchschnitt verkauft (höherer Y-Wert).")
    print()
    print(f"  Die Korrelation von {rho_XY:.6f} zeigt einen")
    if rho_XY > 0.5:
        print("  deutlichen positiven Zusammenhang zwischen")
    else:
        print("  positiven Zusammenhang zwischen")
    print("  Sonnenintensität und Eisverkauf.")
else:
    print("➤ Negative Kovarianz würde bedeuten, dass mehr Sonne")
    print("  mit weniger Eisverkauf einhergeht (hier nicht der Fall).")

print("\n" + "=" * 60)
