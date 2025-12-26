import numpy as np
import pandas as pd
from scipy import stats

print("=" * 70)
print("PYTHON-FUNKTIONEN FÜR KOVARIANZ UND KORRELATION")
print("=" * 70)

# Beispieldaten: Eisverkauf
# Gemeinsame Wahrscheinlichkeitsverteilung
prob_table = {
    (1, 0): 0.1, (1, 1): 0.2, (1, 2): 0.1,
    (2, 0): 0.1, (2, 1): 0.3, (2, 2): 0.2
}

# Für diskrete Verteilungen: Stichprobe generieren
np.random.seed(42)
n_samples = 10000

# Stichprobe basierend auf Wahrscheinlichkeiten generieren
X_samples = []
Y_samples = []

for (x, y), prob in prob_table.items():
    n = int(prob * n_samples)
    X_samples.extend([x] * n)
    Y_samples.extend([y] * n)

X = np.array(X_samples)
Y = np.array(Y_samples)

print("\n" + "=" * 70)
print("METHODE 1: NumPy-Funktionen (für Stichproben)")
print("=" * 70)

# a) Kovarianz mit np.cov()
print("\na) KOVARIANZ mit np.cov()")
print("-" * 40)
cov_matrix = np.cov(X, Y)
print("Kovarianzmatrix:")
print(cov_matrix)
print(f"\nCov(X,Y) = {cov_matrix[0, 1]:.6f}")

# b) Korrelationskoeffizient mit np.corrcoef()
print("\n\nb) KORRELATION mit np.corrcoef()")
print("-" * 40)
corr_matrix = np.corrcoef(X, Y)
print("Korrelationsmatrix:")
print(corr_matrix)
print(f"\nρ(X,Y) = {corr_matrix[0, 1]:.6f}")

# Alternative: stats.pearsonr()
print("\n\nAlternative: stats.pearsonr()")
print("-" * 40)
correlation, p_value = stats.pearsonr(X, Y)
print(f"ρ(X,Y) = {correlation:.6f}")
print(f"p-value = {p_value:.6e}")

# d) Varianz der Summe
print("\n\nd) VARIANZ DER SUMME")
print("-" * 40)
X_plus_Y = X + Y
var_sum = np.var(X_plus_Y, ddof=1)  # ddof=1 für Stichprobenvarianz
print(f"Var(X+Y) = {var_sum:.6f}")

# Vergleich mit Formel
var_X = np.var(X, ddof=1)
var_Y = np.var(Y, ddof=1)
var_sum_formula = var_X + var_Y + 2 * cov_matrix[0, 1]
print(f"\nVergleich mit Formel:")
print(f"Var(X) + Var(Y) + 2·Cov(X,Y) = {var_sum_formula:.6f}")


print("\n\n" + "=" * 70)
print("METHODE 2: Pandas-Funktionen (besonders praktisch)")
print("=" * 70)

df = pd.DataFrame({'X': X, 'Y': Y})

# a) Kovarianz mit DataFrame.cov()
print("\na) KOVARIANZ mit df.cov()")
print("-" * 40)
cov_df = df.cov()
print(cov_df)
print(f"\nCov(X,Y) = {df['X'].cov(df['Y']):.6f}")

# b) Korrelation mit DataFrame.corr()
print("\n\nb) KORRELATION mit df.corr()")
print("-" * 40)
corr_df = df.corr()
print(corr_df)
print(f"\nρ(X,Y) = {df['X'].corr(df['Y']):.6f}")

# Verschiedene Korrelationsmethoden
print("\n\nVerschiedene Korrelationskoeffizienten:")
print("-" * 40)
print(f"Pearson:  {df['X'].corr(df['Y'], method='pearson'):.6f}")
print(f"Spearman: {df['X'].corr(df['Y'], method='spearman'):.6f}")
print(f"Kendall:  {df['X'].corr(df['Y'], method='kendall'):.6f}")


print("\n\n" + "=" * 70)
print("METHODE 3: Für diskrete Verteilungen (exakte Berechnung)")
print("=" * 70)

# Exakte Berechnung aus Wahrscheinlichkeitstabelle
X_vals = [1, 2]
Y_vals = [0, 1, 2]

# Randverteilungen
P_X = {1: 0.4, 2: 0.6}
P_Y = {0: 0.2, 1: 0.5, 2: 0.3}

# Erwartungswerte
E_X = sum(x * P_X[x] for x in X_vals)
E_Y = sum(y * P_Y[y] for y in Y_vals)

# Varianzen
E_X2 = sum(x**2 * P_X[x] for x in X_vals)
E_Y2 = sum(y**2 * P_Y[y] for y in Y_vals)
Var_X = E_X2 - E_X**2
Var_Y = E_Y2 - E_Y**2

# Kovarianz
E_XY = sum(x * y * prob_table[(x, y)] for x in X_vals for y in Y_vals)
Cov_XY = E_XY - E_X * E_Y

# Korrelation
rho_XY = Cov_XY / (np.sqrt(Var_X) * np.sqrt(Var_Y))

print("\na) KOVARIANZ (exakt)")
print("-" * 40)
print(f"Cov(X,Y) = {Cov_XY}")

print("\n\nb) KORRELATION (exakt)")
print("-" * 40)
print(f"ρ(X,Y) = {rho_XY:.6f}")

print("\n\nd) VARIANZ DER SUMME (exakt)")
print("-" * 40)
Var_sum_exact = Var_X + Var_Y + 2 * Cov_XY
print(f"Var(X+Y) = {Var_sum_exact}")


print("\n\n" + "=" * 70)
print("ZUSAMMENFASSUNG DER FUNKTIONEN")
print("=" * 70)
print("""
FÜR STICHPROBEN/DATEN:
─────────────────────────────────────────────────────────────
NumPy:
  • np.cov(X, Y)           → Kovarianzmatrix
  • np.corrcoef(X, Y)      → Korrelationsmatrix
  • np.var(X)              → Varianz

Pandas:
  • df.cov()               → Kovarianzmatrix
  • df['X'].cov(df['Y'])   → Kovarianz zwischen X und Y
  • df.corr()              → Korrelationsmatrix
  • df['X'].corr(df['Y'])  → Korrelation zwischen X und Y

SciPy:
  • stats.pearsonr(X, Y)   → Pearson-Korrelation + p-Wert
  • stats.spearmanr(X, Y)  → Spearman-Korrelation (Rangkorr.)
  • stats.kendalltau(X, Y) → Kendall-Tau-Korrelation


FÜR DISKRETE VERTEILUNGEN (Wahrscheinlichkeitstabelle):
─────────────────────────────────────────────────────────────
  • Manuelle Berechnung mit Formeln (siehe Methode 3)
  • Oder: Stichprobe generieren und obige Funktionen nutzen


WICHTIGE PARAMETER:
─────────────────────────────────────────────────────────────
  • ddof=1   bei np.var(), np.cov()   → Stichprobenvarianz
  • ddof=0   (default)                → Populationsvarianz
""")

print("=" * 70)
