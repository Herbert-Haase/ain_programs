import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

# --- 1. Data Setup ---
# Correlation coefficients (like Pearson's) are for NUMERICAL data.
# We use your provided lists to define which columns are relevant.

# Your provided lists
stetig_liste = ["cpu_base_ghz", "cpu_boost_ghz", "display_size_in", "bluetooth", "weight_kg", "price"]
diskret_liste = ["release_year", "cpu_tier", "cpu_cores", "cpu_threads", "gpu_tier", "vram_gb", "ram_gb", "storage_gb", "storage_drive_count", "refresh_hz", "battery_wh", "charger_watts", "psu_watts", "warranty_months"]

# Combine all numerical columns we might want to analyze
numerical_cols = [
    # From stetig_liste
    "price", "cpu_base_ghz", "display_size_in", "weight_kg", "bluetooth",
    # From diskret_liste
    "ram_gb", "storage_gb", "cpu_cores", "cpu_threads", "battery_wh"
]

# Load your actual data from the CSV file
# Ensure this file exists in your execution environment!
computers_pd = pd.read_csv('./computer_prices_all.csv')


# --- 2. Method 1: Seaborn pairplot (Visual Analysis) ---
# It creates a grid of scatterplots for every variable pair.
# NOTE: sns.pairplot requires a DataFrame as input, which is why we pass computers_pd[plot_cols].
print("\n--- Displaying Seaborn pairplot ---")
print("Look for scatterplots (off-diagonal) that show a clear line with 'price'.")

# We only plot a few key variables to keep the plot readable
plot_cols = ["price", "ram_gb", "cpu_cores", "weight_kg", "battery_wh"]

# This line passes a subset DataFrame and is the correct usage:
sns.pairplot(computers_pd[plot_cols])
plt.suptitle("Pairplot of Key Computer Features", y=1.02) # Title above the plot
plt.show()


# --- 3. Method 2: NumPy corrcoef (Numerical Matrix) ---
# Calculates the Pearson correlation coefficient matrix using NumPy.

# First, create the 'computers' numpy array from the numerical columns
computers_numerical_pd = computers_pd[numerical_cols]
computers = computers_numerical_pd.values # .values extracts the NumPy array

# Calculate the correlation matrix
corrcoef_computers = np.corrcoef(computers, rowvar=False)

# Convert the NumPy array result back to a pandas DataFrame with labels for readability
corr_matrix_np = pd.DataFrame(corrcoef_computers,
                                columns=computers_numerical_pd.columns,
                                index=computers_numerical_pd.columns)

print("\n\n--- Correlation Matrix from np.corrcoef ---")
print(corr_matrix_np)


# --- 4. Method 3: The Easy Way (Pandas .corr()) ---
# Calculate correlation matrix using the built-in pandas method.
print("\n\n--- Correlation Matrix from pandas .corr() (Easier Method) ---")
corr_matrix_pd = computers_numerical_pd.corr()
print(corr_matrix_pd)


# --- 5. Answering Your Question: "Which attributes correlate with 'price'?" ---
# Extract the correlation values with 'price' and sort them.
# A value near 1.0 means strong positive correlation, near -1.0 means strong negative correlation.

print("\n\n--- Correlation with 'price' (Sorted) ---")
price_correlation = corr_matrix_pd['price'].sort_values(ascending=False)
print(price_correlation)


# --- 6. Bonus: The Best Visualization (Heatmap) ---
# A heatmap is the standard way to visualize a correlation matrix.
print("\n--- Displaying Correlation Heatmap ---")

plt.figure(figsize=(12, 10))
sns.heatmap(
    corr_matrix_pd,
    annot=True,     # Show the numbers in each cell
    cmap='coolwarm',  # Use a diverging colormap
    fmt=".2f"       # Format numbers to 2 decimal places
)
plt.title("Correlation Heatmap of Computer Features")
plt.show()
