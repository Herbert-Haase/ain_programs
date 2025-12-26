# coding: utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

prices = pd.read_csv('./computer_prices_all.csv')
stetig_liste = ["cpu_base_ghz","cpu_boost_ghz","display_size_in","bluetooth","weight_kg","price"]
nominal_liste = ["device_type","brand","model","os","form_factor","cpu_brand","cpu_model","gpu_brand","gpu_model","storage_type","display_type","resolution","wifi"]
diskret_liste = ["release_year","cpu_tier","cpu_cores","cpu_threads","gpu_tier","vram_gb","ram_gb","storage_gb","storage_drive_count","refresh_hz","battery_wh","charger_watts","psu_watts","warranty_months"]

prices_nom = prices.copy(deep=True)
for stetig in stetig_liste:
    prices_nom = prices.drop(stetig)


prices_stet = prices.copy(deep=True)
for nominal in nominal_liste:
    prices_stet = prices.drop(nominal)


sns.pairplot(prices_nom)
np.corrcoef(prices_nom.values, rowvar=False)

