# Step 1: Import library
import pandas as pd
from sklearn.model_selection import LeaveOneOut
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
from sklearn.preprocessing import LabelEncoder

# Step 2: Baca dataset
file_path = 'data_cleaned_no_outliers.xlsx'
df = pd.read_excel(file_path)

# Step 3: Buang baris dengan Status 'CL' (transplantasi)
df = df[df['Status'].isin(['C', 'D'])]

# Step 4: Ubah Status: 'D' → 0 (meninggal), 'C' → 1 (hidup)
df['Status'] = df['Status'].map({'D': 0, 'C': 1})

# Step 5: Hapus kolom ID & baris kosong
df = df.drop(columns=[col for col in ['ID'] if col in df.columns])
df = df.dropna()

# Step 6: Encode kolom kategorikal
cat_cols = df.select_dtypes(include=['object']).columns
for col in cat_cols:
    df[col] = LabelEncoder().fit_transform(df[col].astype(str))

# Step 7: Pisahkan fitur dan label
X = df.drop(columns=['Status'])
y = df['Status']

# Step 8: Inisialisasi Leave-One-Out dan model
loo = LeaveOneOut()
model = GaussianNB()

# Step 9: Simpan hasil evaluasi
y_true = []
y_pred = []

# Step 10: Lakukan LOO-CV
for train_index, test_index in loo.split(X):
    X_train, X_test = X.iloc[train_index], X.iloc[test_index]
    y_train, y_test = y.iloc[train_index], y.iloc[test_index]

    model.fit(X_train, y_train)
    y_pred_single = model.predict(X_test)

    y_pred.append(y_pred_single[0])
    y_true.append(y_test)

# Step 11: Evaluasi hasil
print("Confusion Matrix:\n", confusion_matrix(y_true, y_pred))
print("\nClassification Report:\n", classification_report(y_true, y_pred, target_names=["Meninggal", "Hidup"]))
print("\nAkurasi: ", accuracy_score(y_true, y_pred))
