import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats

# aufgabe 100.1
zimmeranz = np.array([3, 4, 5, 1, 5, 2, 1, 3, 1, 3, 3, 3, 2, 1, 5])

# aufgabe 100.1.2
value, count = np.unique(zimmeranz,return_counts=True);
print(value, count)
print(count / count.sum())

# aufgabe 100.1.3
plt.figure()
plt.bar(value,count)
plt.xlabel('Zimmer')
plt.ylabel('Absolute Häufigkeit')
plt.title('Histogramm des Zimmeranzahl')
plt.show()

# aufgabe 100.1.4
def compute_ecdf(data):
    """Berechnet die ECDF für gegebene Daten"""
    x = np.sort(data)
    y = np.arange(1, len(data) + 1) / len(data)
    return x, y

x_ecdf, y_ecdf = compute_ecdf(zimmeranz);

plt.step(x_ecdf, y_ecdf, 'bo-', linewidth=2, markersize=8, label='Empirische ECDF', alpha=0.7)
plt.xlabel('Zimmeranzahl')
plt.ylabel('Kumulative Wahrscheinlichkeit')
plt.title('Empirische ECDF der Zimmeranzahl')
plt.grid(True, alpha=0.3)
plt.legend()
plt.xlim(0.5, 6.5)
plt.ylim(0, 1)
plt.show()
# aufgabe 100.1.5
print(np.mean(zimmeranz))
print(np.median(zimmeranz))
mode_result = stats.mode(zimmeranz, keepdims=True)
print(f"value: {mode_result.mode[0]} count: {mode_result.count[0]}")

