import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt


numerical_cols = [
    "price", "cpu_base_ghz", "cpu_boost_ghz", "cpu_tier", "gpu_tier",
    "ram_gb", "vram_gb", "cpu_cores", "cpu_threads"
]

computers_pd = pd.read_csv('./computer_prices_all.csv')


sns.pairplot(computers_pd[numerical_cols[0:5]])
plt.suptitle("Pairplot of Key Computer Features", y=1.02) # Title above the plot
plt.show()

computers_numerical_pd = computers_pd[numerical_cols]
computers = computers_numerical_pd.values

corr_matrix_pd = computers_numerical_pd.corr()
print(corr_matrix_pd)


plt.figure(figsize=(12, 10))
sns.heatmap(
    corr_matrix_pd,
    annot=True,     # Show the numbers in each cell
    cmap='coolwarm',  # Use a diverging colormap
    fmt=".2f"       # Format numbers to 2 decimal places
)
plt.title("Correlation Heatmap of Computer Features")
plt.show()
