🔍 DSA Search Engine
A Data Structures & Algorithms based Search Engine built as an academic project.
This project demonstrates the practical implementation of core DSA concepts such as Trie, Hashing, KMP Algorithm, Stack, Queue, and Heap to efficiently search words and phrases from text documents.

📌 Project Overview
The DSA Search Engine allows users to:

Search single words and multi‑word phrases

Get fast autocomplete suggestions

View search history and recent searches

Perform case‑insensitive and cleaned searches

Efficiently search within multiple text files

The project focuses on performance, correctness, and real‑world use of data structures rather than relying on built‑in libraries.

🧠 Data Structures & Algorithms Used
Component	Purpose
Trie	Autocomplete suggestions & prefix searching
Hash Table (Separate Chaining)	Fast word indexing and lookup
KMP Algorithm	Efficient full‑string / phrase searching
Stack	Browsing history (Back navigation)
Queue	Recent searches tracking
Heap	Sorting results based on frequency
Linear Probing Hashing	Stop‑word filtering
✨ Key Features
🔎 Single Word Search

🧾 Full Phrase Search (e.g., “computer science”)

⚡ Live Autocomplete Suggestions

🕒 Browsing History (Stack)

🧠 Recent Searches (Queue)

🚫 Stop‑Word Removal

🧹 Input Cleaning (special characters handled)

📂 Multi‑File Search Support

🛡️ Crash‑safe Input Handling

🖥️ User Interface
Clean and minimal UI

Search bar with autocomplete

Results panel

Browsing history and recent searches panel

(UI implemented using console + structured layout as shown in the project screenshot)

📂 Project Structure
DSA-Search-Engine/
│
├── backend/
│   ├── utils.cpp              # Core logic & data structures (Trie, Hash, KMP, etc.)
│   ├── main.cpp               # Program entry point
│   ├── t1.txt                 # Sample document
│   └── t2.txt                 # Sample document
│
├── frontend/
│   ├── index.html             # UI layout (search bar, results, panels)
│   ├── styles.css             # UI styling (dark theme, layout)
│   └── app.js                 # UI logic (search request handling)
│
├── README.md                  # Project documentation

🚀 How It Works (Methodology)
Documents are parsed

Words are extracted

Stop words are removed

Words are indexed using Hash Tables

Trie is built

Stores all valid words for fast autocomplete

Search Execution

Single word → Hash Table lookup

Phrase search → KMP string matching

Results Handling

Frequencies ranked using Heap

History stored using Stack & Queue

🧪 Test Cases Covered
Empty input handling

Special character removal

Case‑insensitive searches

No‑match queries

Large dataset performance

Numeric & alphanumeric inputs

⚠️ Challenges Faced
Handling duplicate sentence outputs

Preventing crashes on TAB + ENTER

Removing STL vectors and replacing with arrays

Implementing stop words using hashing

Managing multi‑word autocomplete

🔮 Future Enhancements
GUI using Web / Qt

File upload support

Ranking using TF‑IDF

Advanced spell correction

Persistent storage (database)

Parallel searching for large datasets

👨‍💻 Team Members
Abdul Rafay Ansari

Hamza

Shahzan Khan

📚 Academic Note
This project was developed strictly for educational purposes to demonstrate the real‑world application of Data Structures & Algorithms without relying on STL shortcuts.
