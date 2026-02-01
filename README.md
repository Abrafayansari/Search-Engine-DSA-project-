# 🔍 DSA Search Engine

A **Data Structures & Algorithms (DSA)** based search engine built as an academic project. This project demonstrates practical implementations of core DSA concepts, including **Trie, Hashing, KMP Algorithm, Stack, Queue, and Heap**, to efficiently search words and phrases in text documents.

---

## 📌 Project Overview

The DSA Search Engine enables users to:

* Search **single words** and **multi-word phrases**
* Get **fast autocomplete suggestions**
* View **search history** and **recent searches**
* Perform **case-insensitive** and **cleaned searches**
* Search efficiently across **multiple text files**

This project emphasizes **performance, correctness, and the real-world application of data structures** rather than relying on built-in libraries.

---

## 🧠 Data Structures & Algorithms Used

| Component                      | Purpose                               |
| ------------------------------ | ------------------------------------- |
| Trie                           | Autocomplete & prefix searching       |
| Hash Table (Separate Chaining) | Fast word indexing and lookup         |
| KMP Algorithm                  | Efficient full-string / phrase search |
| Stack                          | Browsing history (Back navigation)    |
| Queue                          | Recent searches tracking              |
| Heap                           | Sorting results by frequency          |
| Linear Probing Hashing         | Stop-word filtering                   |

---

## ✨ Key Features

* **Single Word Search**
* **Full Phrase Search** (e.g., “computer science”)
* **Live Autocomplete Suggestions**
* **Browsing History** (Stack)
* **Recent Searches** (Queue)
* **Stop-Word Removal**
* **Input Cleaning** (special characters handled)
* **Multi-File Search Support**
* **Crash-Safe Input Handling**

---

## 🖥️ User Interface

* Clean, minimal UI
* Search bar with **autocomplete**
* Results panel
* Browsing history & recent searches panel
* **UI implemented using console + structured layout**

---

## 📂 Project Structure

```
DSA-Search-Engine/
│
├── backend/
│   ├── utils.cpp      # Core logic & data structures (Trie, Hash, KMP, etc.)
│   ├── main.cpp       # Program entry point
│   ├── t1.txt         # Sample document
│   └── t2.txt         # Sample document
│
├── frontend/
│   ├── index.html     # UI layout (search bar, results, panels)
│   ├── styles.css     # UI styling (dark theme, layout)
│   └── app.js         # UI logic (search request handling)
│
└── README.md          # Project documentation
```

---

## 🚀 How It Works (Methodology)

1. **Document Parsing**: Extract words from input files
2. **Stop Words Removal**: Remove common irrelevant words
3. **Word Indexing**: Use Hash Tables for fast lookup
4. **Trie Construction**: Store valid words for **autocomplete**
5. **Search Execution**:

   * Single word → Hash Table lookup
   * Phrase search → KMP algorithm
6. **Results Handling**:

   * Sort by frequency using Heap
   * Store history with Stack & Queue

---

## 🧪 Test Cases Covered

* Empty input handling
* Special character removal
* Case-insensitive searches
* No-match queries
* Large dataset performance
* Numeric & alphanumeric inputs

---

## ⚠️ Challenges Faced

* Handling duplicate sentence outputs
* Preventing crashes on **TAB + ENTER**
* Replacing STL vectors with arrays
* Implementing stop words using hashing
* Managing multi-word autocomplete

---

## 🔮 Future Enhancements

* GUI using **Web / Qt**
* File upload support
* Ranking using **TF-IDF**
* Advanced spell correction
* Persistent storage (database)
* Parallel searching for large datasets

---

## 👨‍💻 Team Members

* Abdul Rafay Ansari
* Hamza
* Shahzan Khan

---

## 📚 Academic Note

This project was developed strictly for **educational purposes** to demonstrate real-world applications of **Data Structures & Algorithms** without relying on STL shortcuts.

---


