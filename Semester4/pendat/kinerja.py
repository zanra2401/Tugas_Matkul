import json
import random
import nltk
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
from nltk.stem import PorterStemmer
from nltk.corpus import stopwords
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_recall_fscore_support, confusion_matrix, classification_report # Tambah import confusion_matrix
import numpy as np
import pickle


# --- NLTK Downloads (pastikan ini sudah diunduh atau jalankan sekali) ---
try:
    nltk.data.find('tokenizers/punkt_tab')
except nltk.downloader.DownloadError:
    nltk.download('punkt_tab')
try:
    nltk.data.find('corpora/stopwords')
except nltk.downloader.DownloadError:
    nltk.download('stopwords')

# --- Preprocessing setup ---
stemmer = PorterStemmer()
stop_words = set(stopwords.words('english'))

def preprocess(text):
    tokens = nltk.word_tokenize(text.lower())
    tokens = [stemmer.stem(t) for t in tokens if t.isalpha() and t not in stop_words]
    return " ".join(tokens)

# --- Load Dataset ---
# Sesuaikan path jika e-commerce.json ada di subfolder 'Assets/'
with open("./streamlit/Assets/e-commerce.json", "r", encoding="utf-8") as file:
    data = json.load(file)

# Siapkan data training (dan akan dibagi untuk pengujian)
X_patterns = []
y_tags = []
for intent in data["intents"]: # Periksa lagi typo "intetns" vs "intents"
    tag = intent["tag"]
    for pattern in intent["patterns"]:
        X_patterns.append(preprocess(pattern))
        y_tags.append(tag)

# --- Membagi Data menjadi Training dan Testing ---
# Split 80% untuk training, 20% untuk testing
# random_state memastikan hasil pembagian konsisten setiap kali dijalankan
X_train, X_test, y_train, y_test = train_test_split(X_patterns, y_tags, test_size=0.2, random_state=42)

print(f"Jumlah data training: {len(X_train)}")
print(f"Jumlah data testing: {len(X_test)}")


# --- Buat dan Latih Model ---
model = Pipeline([
    ("vectorizer", CountVectorizer()),
    ("classifier", MultinomialNB())
])

model.fit(X_train, y_train)

# print(X_test)
# print()
# print(y_test)

# --- Evaluasi Kinerja Model ---
# Prediksi pada data uji
y_pred = model.predict(X_test)

# --- Tampilkan Confusion Matrix ---
cm = confusion_matrix(y_test, y_pred, labels=model.classes_) # labels=model.classes_ penting untuk urutan
# print("\n--- Confusion Matrix ---")
# print(cm)

# --- Menghitung TP, TN, FP, FN untuk Setiap Kelas ---
print("\n--- Metrik TP, TN, FP, FN per Kelas ---")
classes = model.classes_ # Dapatkan daftar semua kelas/tag

for i, class_label in enumerate(classes):
    # Untuk kelas 'i' (class_label)
    TP = cm[i, i] # True Positives: diagonal elemen di baris i, kolom i
    
    # False Positives: jumlah di kolom 'i' (prediksi sebagai class_label) dikurangi TP
    FP = cm[:, i].sum() - TP 
    
    # False Negatives: jumlah di baris 'i' (seharusnya class_label) dikurangi TP
    FN = cm[i, :].sum() - TP
    
    # True Negatives: total semua sampel dikurangi TP, FP, FN
    # Atau, total semua sampel yang bukan class_label (baik aktual maupun prediksi)
    TN = cm.sum() - (TP + FP + FN)

    print(f"\nUntuk Kelas: '{class_label}'")
    print(f"  True Positives (TP): {TP}")
    print(f"  False Positives (FP): {FP}")
    print(f"  False Negatives (FN): {FN}")
    print(f"  True Negatives (TN): {TN}")

# --- Tampilkan Laporan Klasifikasi Lengkap (termasuk Presisi, Recall, F1-Score per kelas) ---
print("\n--- Laporan Klasifikasi Detail ---")
print(classification_report(y_test, y_pred, zero_division=0))

# --- Metrik Global (Akurasi, Presisi Weighted, Recall Weighted, F1-Score Weighted) ---
accuracy = accuracy_score(y_test, y_pred)
precision_w, recall_w, f1_score_w, _ = precision_recall_fscore_support(y_test, y_pred, average='weighted', zero_division=0)

# Hitung Akurasi
# Accuracy=(TP+TN)/(TP+TN+FP+FN)
accuracy = accuracy_score(y_test, y_pred)
print(f"\nAkurasi: {(accuracy * 100):.4f}%")

# Hitung Presisi, Recall, F1-Score per kelas (average='weighted' untuk mempertimbangkan imbalance kelas)
precision, recall, f1_score, _ = precision_recall_fscore_support(y_test, y_pred, average='weighted', zero_division=0)

# Precision=TP/(TP+FP)
print(f"Presisi (weighted): {(precision * 100):.4f}%")
# Recall=TP/(TP+FN)
print(f"Recall (weighted): {(recall * 100):.4f}%")
#  F1−Score=2∗(Precision∗Recall)/(Precision+Recall)
print(f"F1-Score (weighted): {(f1_score * 100):.4f}%")

# Untuk melihat metrik per kelas (jika diperlukan)
# from sklearn.metrics import classification_report
# print("\nLaporan Klasifikasi per Kelas:")
# print(classification_report(y_test, y_pred, zero_division=0))

# --- Simpan Model (Opsional, jika Anda ingin menyimpannya setelah dievaluasi) ---
# import pickle
# with open("model_chatbot.pkl", "wb") as model_file:
#     pickle.dump(model, model_file)
# print("\nModel 'model_chatbot.pkl' berhasil dilatih dan disimpan ulang.")