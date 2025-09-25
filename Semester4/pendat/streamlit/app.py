import streamlit as st
import json
import random
import nltk
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
from nltk.stem import PorterStemmer
from nltk.corpus import stopwords
import numpy as np
import pickle

# --- NLTK Downloads (Run once) ---
# Ensure these are downloaded. You might run them once in your terminal
# or add checks here, but for simplicity in Streamlit,
# it's often assumed they are pre-downloaded or handled by the hosting environment.
try:
    nltk.data.find('tokenizers/punkt_tab')
except nltk.downloader.DownloadError:
    nltk.download('punkt_tab')
try:
    nltk.data.find('corpora/stopwords')
except nltk.downloader.DownloadError:
    nltk.download('stopwords')

# --- Preprocessing setup (from your original code) ---
stemmer = PorterStemmer()
stop_words = set(stopwords.words('english'))

def preprocess(text):
    tokens = nltk.word_tokenize(text.lower())
    tokens = [stemmer.stem(t) for t in tokens if t.isalpha() and t not in stop_words]
    return " ".join(tokens)

# --- Load Dataset and prepare responses (from your original code) ---
# Assuming e-commerce.json is in the same directory as app.py
# If it's in a subfolder like 'Assets/', adjust the path accordingly:
# with open("Assets/e-commerce.json", "r", encoding="utf-8") as file:
with open("./Assets/e-commerce.json", "r", encoding="utf-8") as file:
    data = json.load(file)

responses = {}
for intent in data["intents"]: # Corrected typo: "intetns" to "intents" if it exists in JSON
    tag = intent["tag"]
    responses[tag] = intent["responses"]

# --- Load the trained model ---
try:
    with open("./Assets/model_chatbot.pkl", "rb") as model_file:
        model = pickle.load(model_file)
except FileNotFoundError:
    st.error("Error: 'model_chatbot.pkl' not found. Please ensure your model is trained and saved in the same directory as app.py.")
    st.stop() # Stop the Streamlit app if model isn't found

# --- Streamlit GUI ---
st.set_page_config(page_title="E-commerce Chatbot", page_icon="🛍️")

st.title("🛍️ E-commerce Chatbot")
st.markdown("Ask me anything about our products, orders, or services!")

# Initialize chat history
if "messages" not in st.session_state:
    st.session_state.messages = []

# Display chat messages from history on app rerun
for message in st.session_state.messages:
    with st.chat_message(message["role"]):
        st.markdown(message["content"])

# React to user input
if prompt := st.chat_input("Type your message here..."):
    # Display user message in chat message container
    st.chat_message("user").markdown(prompt)
    # Add user message to chat history
    st.session_state.messages.append({"role": "user", "content": prompt})

    # Get chatbot response
    with st.spinner("Thinking..."):
        preprocessed_input = preprocess(prompt)
        
        # Make prediction
        proba = model.predict_proba([preprocessed_input])[0]
        max_proba = np.max(proba)

        if max_proba < 0.2: # Threshold for "Sorry I don't understand"
            response_text = "Sorry, I don't understand. Can you please rephrase?"
        else:
            predicted_intent = model.classes_[np.argmax(proba)]
            if predicted_intent in responses:
                response_text = predicted_intent + ": " + random.choice(responses[predicted_intent])
            else:
                response_text = predicted_intent + ": " "Hmm, I know the intent, but I don't have a pre-defined response for it. Please try asking something else."

    # Display chatbot response in chat message container
    with st.chat_message("assistant"):
        st.markdown(response_text)
    # Add chatbot response to chat history
    st.session_state.messages.append({"role": "assistant", "content": response_text})

st.markdown(
    """
    <style>
        .reportview-container .main {
            flex-direction: row-reverse;
        }
    </style>
    """,
    unsafe_allow_html=True,
)