---
jupytext:
  formats: md:myst
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

# Data Understanding

## 1. Sumber Data

Data yang digunakan dalam penelitian ini dapat diperoleh dari:
Harga Emas Harian **data historis dari yahoo finance**.

1. Faktor Eksternal yang memengaruhi harga emas, seperti:
    - Indeks Dolar AS (USD Index)
    - Harga Minyak Dunia
    - Inflasi (CPI)
    - Indeks Saham (misalnya S&P 500)

2. Deskripsi Data
    - Periode Data: (misalnya dari tahun 2015–2024)
    - Frekuensi: Harian atau bulanan
    - Atribut Utama:
    - date : Tanggal pencatatan
    - gold_price : Harga emas per troy ounce
    - Atribut Eksternal:
    - usd_index : Indeks nilai tukar dolar AS
    - oil_price : Harga minyak dunia (per barrel)
    - sp500_index : Indeks saham S&P 500

3. Karakteristik Data
    - Data time series → urutan waktu sangat penting.
    - Data numerik kontinyu → sebagian besar berupa nilai angka.
    - Data multivariat → harga emas dipengaruhi oleh lebih dari 1 variabel.

## 2. Code Untuk Mendapatkan Data

```{code-cell}
import yfinance as yf
import pandas as pd
import warnings
from forex_python.converter import CurrencyRates

warnings.simplefilter(action="ignore", category=FutureWarning)

# -----------------------
# 1. Ambil data dari Yahoo Finance
# -----------------------
start_date = "2015-01-01"
end_date = "2025-01-01"

# Fungsi bantu untuk ambil data dan rename kolom Close
def get_yf_data(ticker, col_name):
    data = yf.download(ticker, start=start_date, end=end_date, progress=False)[["Close"]]
    data.rename(columns={"Close": col_name}, inplace=True)
    return data

gold = get_yf_data("GC=F", "Gold_Close")
oil = get_yf_data("CL=F", "Oil_Close")
dxy = get_yf_data("DX-Y.NYB", "DXY_Close")
sp500 = get_yf_data("^GSPC", "SP500_Close")

# Gabungkan semua menjadi satu DataFrame
df = pd.concat([gold, oil, dxy, sp500], axis=1)

df.head()
```