# coding: utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import statistics as stat
import seaborn as sns

prices = pd.read_csv('./computer_prices_all.csv')
# print(prices)

# prices_stats = prices.describe(include='all')
# print(prices_stats)
#
# prices.sort_values('Laptop')
#
# prices.sort_values('brand')

for column in prices.columns:
    print(f"\n{column}:")
    print(prices[column].value_counts())


# print(prices.iloc[:, 0].values)
