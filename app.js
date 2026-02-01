// ============================================================
// DSA SEARCH ENGINE - JavaScript Implementation
// Implements: Trie, Hash Table, KMP, Stack, Queue, Max Heap
// ============================================================

// ===== STOPWORDS =====
const STOPWORDS = new Set([
    "a", "an", "and", "are", "as", "at", "be", "but", "by",
    "for", "if", "in", "into", "is", "it", "no", "not", "of",
    "on", "or", "such", "that", "the", "their", "then", "there",
    "these", "they", "this", "to", "was", "will", "with"
]);

// ===== SAMPLE DOCUMENTS (from t1.txt and t2.txt) =====
const DOCUMENTS = {
    "t1.txt": `Data structures play a crucial role in computer science.
Efficient storage techniques help manage large volumes of information.
Arrays provide constant-time access but fixed-size limitations.
Linked lists offer dynamic memory usage with sequential traversal.
Stacks operate on a last-in first-out mechanism.
Queues follow the first-in first-out approach used in scheduling.
Trees enable hierarchical representation of complex data.
Binary search trees support efficient searching and insertion.
Balanced trees maintain height constraints for predictable performance.
Graphs model relationships between interconnected entities.
Weighted graphs allow cost-based routing and navigation.
Hash tables provide average constant-time lookups.
Collisions in hashing are handled using chaining or open addressing.
Sorting algorithms organize data in meaningful order.
Searching algorithms help retrieve information quickly.
Recursion simplifies complex logic through repeated function calls.
Iteration provides a controlled flow for repeated tasks.
File handling techniques manage data stored on disk.
Indexing improves the speed of data retrieval operations.
Data mining extracts useful patterns from large datasets.
Machine learning models train on structured and unstructured data.
Neural networks simulate human brain-like processing.
Optimization techniques enhance model performance and accuracy.
Distributed systems store data across multiple networked machines.
Cybersecurity ensures protection against unauthorized access.
Trees grow taller than other trees in dense forests.`,
    "t2.txt": `what is your name (Rafay)`
};

// ============================================================
// TRIE DATA STRUCTURE - For Autocomplete
// ============================================================
class TrieNode {
    constructor() {
        this.children = {};
        this.isEnd = false;
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
    }

    // Normalize word: lowercase and letters only
    normalize(word) {
        return word.toLowerCase().replace(/[^a-z]/g, '');
    }

    // Insert word into trie
    insert(rawWord) {
        const word = this.normalize(rawWord);
        if (!word) return;

        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.isEnd = true;
    }

    // Collect all words with given prefix
    collect(node, prefix, results, limit = 50) {
        if (!node || results.length >= limit) return;

        if (node.isEnd) {
            results.push(prefix);
        }

        for (let i = 0; i < 26 && results.length < limit; i++) {
            const char = String.fromCharCode(97 + i);
            if (node.children[char]) {
                this.collect(node.children[char], prefix + char, results, limit);
            }
        }
    }

    // Get suggestions for prefix
    suggestions(rawPrefix, limit = 10) {
        const prefix = this.normalize(rawPrefix);
        const results = [];

        let node = this.root;
        for (const char of prefix) {
            if (!node.children[char]) return results;
            node = node.children[char];
        }

        this.collect(node, prefix, results, limit);
        return results;
    }
}

// ============================================================
// STACK DATA STRUCTURE - For Browsing History (LIFO)
// ============================================================
class StackNode {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class Stack {
    constructor() {
        this.top = null;
        this.size = 0;
    }

    push(data) {
        const newNode = new StackNode(data);
        newNode.next = this.top;
        this.top = newNode;
        this.size++;
    }

    pop() {
        if (!this.top) return null;
        const data = this.top.data;
        this.top = this.top.next;
        this.size--;
        return data;
    }

    peek() {
        return this.top ? this.top.data : null;
    }

    isEmpty() {
        return this.top === null;
    }

    toArray() {
        const result = [];
        let current = this.top;
        while (current) {
            result.push(current.data);
            current = current.next;
        }
        return result;
    }

    clear() {
        this.top = null;
        this.size = 0;
    }
}

// ============================================================
// QUEUE DATA STRUCTURE - For Recent Searches (FIFO, Max 5)
// ============================================================
class Queue {
    constructor(maxSize = 5) {
        this.front = null;
        this.rear = null;
        this.count = 0;
        this.maxSize = maxSize;
    }

    enqueue(data) {
        // Remove oldest if at max size
        if (this.count >= this.maxSize) {
            this.dequeue();
        }

        const newNode = new StackNode(data);
        if (!this.rear) {
            this.front = this.rear = newNode;
        } else {
            this.rear.next = newNode;
            this.rear = newNode;
        }
        this.count++;
    }

    dequeue() {
        if (!this.front) return null;
        const data = this.front.data;
        this.front = this.front.next;
        if (!this.front) {
            this.rear = null;
        }
        this.count--;
        return data;
    }

    isEmpty() {
        return this.front === null;
    }

    toArray() {
        const result = [];
        let current = this.front;
        while (current) {
            result.push(current.data);
            current = current.next;
        }
        return result;
    }

    clear() {
        this.front = null;
        this.rear = null;
        this.count = 0;
    }
}

// ============================================================
// MAX HEAP - For Sorting Results by Frequency
// ============================================================
class MaxHeap {
    constructor() {
        this.heap = [null]; // 1-indexed
        this.size = 0;
    }

    insert(item) {
        this.size++;
        this.heap[this.size] = item;
        this.bubbleUp(this.size);
    }

    bubbleUp(index) {
        while (index > 1) {
            const parent = Math.floor(index / 2);
            if (this.heap[parent].frequency < this.heap[index].frequency) {
                [this.heap[parent], this.heap[index]] = [this.heap[index], this.heap[parent]];
                index = parent;
            } else {
                break;
            }
        }
    }

    extractMax() {
        if (this.size === 0) return null;
        const max = this.heap[1];
        this.heap[1] = this.heap[this.size];
        this.size--;
        this.heapify(1);
        return max;
    }

    heapify(index) {
        let largest = index;
        const left = 2 * index;
        const right = 2 * index + 1;

        if (left <= this.size && this.heap[left].frequency > this.heap[largest].frequency) {
            largest = left;
        }
        if (right <= this.size && this.heap[right].frequency > this.heap[largest].frequency) {
            largest = right;
        }

        if (largest !== index) {
            [this.heap[index], this.heap[largest]] = [this.heap[largest], this.heap[index]];
            this.heapify(largest);
        }
    }

    // Sort and return array (heap sort)
    getSorted() {
        const sorted = [];
        const originalSize = this.size;
        const originalHeap = [...this.heap];

        while (this.size > 0) {
            sorted.push(this.extractMax());
        }

        // Restore heap
        this.heap = originalHeap;
        this.size = originalSize;

        return sorted;
    }
}

// ============================================================
// KMP ALGORITHM - For Pattern Matching
// ============================================================
class KMP {
    // Build LPS (Longest Proper Prefix which is also Suffix) array
    static buildLPS(pattern) {
        const m = pattern.length;
        const lps = new Array(m).fill(0);
        let len = 0;
        let i = 1;

        while (i < m) {
            if (pattern[i] === pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len !== 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    // Search for pattern in text, return all positions
    static search(text, pattern) {
        const positions = [];
        if (!pattern || !text) return positions;

        const n = text.length;
        const m = pattern.length;
        const lps = this.buildLPS(pattern);

        let i = 0; // text index
        let j = 0; // pattern index

        while (i < n) {
            if (text[i].toLowerCase() === pattern[j].toLowerCase()) {
                i++;
                j++;
            }

            if (j === m) {
                positions.push(i - j);
                j = lps[j - 1];
            } else if (i < n && text[i].toLowerCase() !== pattern[j].toLowerCase()) {
                if (j !== 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return positions;
    }
}

// ============================================================
// HASH TABLE WITH SEPARATE CHAINING - For Word Indexing
// ============================================================
class HashNode {
    constructor(word) {
        this.word = word;
        this.files = {}; // { fileName: { frequency, positions: [], sentences: [] } }
        this.next = null;
    }

    addOccurrence(fileName, position, sentence) {
        if (!this.files[fileName]) {
            this.files[fileName] = {
                frequency: 0,
                positions: [],
                sentences: []
            };
        }
        this.files[fileName].frequency++;
        this.files[fileName].positions.push(position);
        if (sentence && !this.files[fileName].sentences.includes(sentence)) {
            this.files[fileName].sentences.push(sentence);
        }
    }
}

class HashTable {
    constructor(size = 1000) {
        this.size = size;
        this.buckets = new Array(size).fill(null);
        this.entries = 0;
    }

    // Polynomial rolling hash function
    hash(word) {
        let h = 0;
        let p = 31;
        let pow = 1;

        for (const char of word) {
            h = (h + (char.charCodeAt(0) - 'a'.charCodeAt(0) + 1) * pow) % this.size;
            pow = (pow * p) % this.size;
        }
        return Math.abs(h);
    }

    // Insert word with file info
    insert(word, fileName, position, sentence) {
        // Check load factor and rehash if needed
        const load = this.entries / this.size;
        if (load >= 0.7) {
            this.rehash();
        }

        const key = this.hash(word);
        let current = this.buckets[key];

        // Check if word exists
        while (current) {
            if (current.word === word) {
                current.addOccurrence(fileName, position, sentence);
                return;
            }
            current = current.next;
        }

        // New word - create node
        const newNode = new HashNode(word);
        newNode.addOccurrence(fileName, position, sentence);
        newNode.next = this.buckets[key];
        this.buckets[key] = newNode;
        this.entries++;
    }

    // Search for word
    search(word) {
        const key = this.hash(word);
        let current = this.buckets[key];

        while (current) {
            if (current.word === word) {
                return current;
            }
            current = current.next;
        }
        return null;
    }

    // Rehash when load factor exceeds threshold
    rehash() {
        const oldBuckets = this.buckets;
        const oldSize = this.size;

        this.size = this.size * 2;
        this.buckets = new Array(this.size).fill(null);
        this.entries = 0;

        for (let i = 0; i < oldSize; i++) {
            let current = oldBuckets[i];
            while (current) {
                for (const [fileName, data] of Object.entries(current.files)) {
                    for (let j = 0; j < data.positions.length; j++) {
                        this.insert(current.word, fileName, data.positions[j], data.sentences[j]);
                    }
                }
                current = current.next;
            }
        }
    }

    // Get all words
    getAllWords() {
        const words = [];
        for (let i = 0; i < this.size; i++) {
            let current = this.buckets[i];
            while (current) {
                words.push(current.word);
                current = current.next;
            }
        }
        return words;
    }
}

// ============================================================
// SEARCH ENGINE CLASS - Main Application
// ============================================================
class SearchEngine {
    constructor() {
        this.trie = new Trie();
        this.hashTable = new HashTable();
        this.browsingHistory = new Stack();
        this.recentSearches = new Queue(5);
        this.documents = DOCUMENTS;

        this.initializeIndex();
        this.setupEventListeners();
        this.renderDocuments();
    }

    // Remove unwanted characters and normalize
    normalize(str) {
        return str.toLowerCase().replace(/[^a-z0-9]/g, '');
    }

    // Extract sentence containing position
    extractSentence(text, position) {
        let start = position;
        let end = position;

        // Move left to find sentence start
        while (start > 0 && !['.', '?', '!', '\n'].includes(text[start - 1])) {
            start--;
        }

        // Move right to find sentence end
        while (end < text.length && !['.', '?', '!', '\n'].includes(text[end])) {
            end++;
        }

        return text.substring(start, end + 1).trim();
    }

    // Initialize index from documents
    initializeIndex() {
        for (const [fileName, content] of Object.entries(this.documents)) {
            const words = content.split(/\s+/);
            let position = 0;

            for (const rawWord of words) {
                const word = this.normalize(rawWord);
                
                if (word && !STOPWORDS.has(word)) {
                    const sentence = this.extractSentence(content, position);
                    this.hashTable.insert(word, fileName, position, sentence);
                    this.trie.insert(word);
                }
                
                position += rawWord.length + 1;
            }
        }

        console.log('Index initialized with', this.hashTable.entries, 'unique words');
    }

    // Search for a word
    searchWord(query) {
        const cleanQuery = this.normalize(query);
        if (!cleanQuery) return [];

        // Check if multi-word query
        const isMultiWord = query.includes(' ');

        if (isMultiWord) {
            return this.searchPhrase(query);
        }

        // Single word search using hash table
        const node = this.hashTable.search(cleanQuery);
        if (!node) return [];

        // Use max heap to sort by frequency
        const heap = new MaxHeap();
        for (const [fileName, data] of Object.entries(node.files)) {
            heap.insert({
                fileName,
                frequency: data.frequency,
                sentences: data.sentences
            });
        }

        // Add to history and recent
        this.browsingHistory.push(query);
        this.recentSearches.enqueue(query);

        return heap.getSorted();
    }

    // Search for phrase using KMP
    searchPhrase(phrase) {
        const results = [];
        const pattern = phrase.toLowerCase().replace(/[^a-z0-9 ]/g, '');

        for (const [fileName, content] of Object.entries(this.documents)) {
            const positions = KMP.search(content.toLowerCase(), pattern);
            
            if (positions.length > 0) {
                const sentences = positions.map(pos => this.extractSentence(content, pos));
                const uniqueSentences = [...new Set(sentences)];
                
                results.push({
                    fileName,
                    frequency: positions.length,
                    sentences: uniqueSentences
                });
            }
        }

        // Add to history and recent
        this.browsingHistory.push(phrase);
        this.recentSearches.enqueue(phrase);

        // Sort by frequency using heap
        const heap = new MaxHeap();
        results.forEach(r => heap.insert(r));

        return heap.getSorted();
    }

    // Get autocomplete suggestions
    getSuggestions(prefix) {
        return this.trie.suggestions(prefix, 8);
    }

    // Go back (pop from history)
    goBack() {
        return this.browsingHistory.pop();
    }

    // Clear recent searches
    clearRecent() {
        this.recentSearches.clear();
    }

    // ==================== UI METHODS ====================

    setupEventListeners() {
        const searchInput = document.getElementById('searchInput');
        const searchBtn = document.getElementById('searchBtn');
        const goBackBtn = document.getElementById('goBackBtn');
        const clearRecentBtn = document.getElementById('clearRecentBtn');
        const toggleDocsBtn = document.getElementById('toggleDocsBtn');
        const suggestionsBox = document.getElementById('suggestions');

        // Search input events
        searchInput.addEventListener('input', (e) => this.handleInput(e));
        searchInput.addEventListener('keydown', (e) => this.handleKeydown(e));
        searchInput.addEventListener('focus', () => this.showSuggestions());
        
        // Click outside to hide suggestions
        document.addEventListener('click', (e) => {
            if (!e.target.closest('.search-section')) {
                suggestionsBox.classList.remove('active');
            }
        });

        // Button events
        searchBtn.addEventListener('click', () => this.performSearch());
        goBackBtn.addEventListener('click', () => this.handleGoBack());
        clearRecentBtn.addEventListener('click', () => this.handleClearRecent());
        toggleDocsBtn.addEventListener('click', () => this.toggleDocuments());
    }

    handleInput(e) {
        const query = e.target.value;
        this.updateSuggestions(query);
        this.updateGhostText(query);
    }

    handleKeydown(e) {
        const suggestionsBox = document.getElementById('suggestions');
        const items = suggestionsBox.querySelectorAll('.suggestion-item');
        const highlighted = suggestionsBox.querySelector('.highlighted');

        if (e.key === 'Enter') {
            e.preventDefault();
            if (highlighted) {
                document.getElementById('searchInput').value = highlighted.dataset.word;
            }
            this.performSearch();
            suggestionsBox.classList.remove('active');
        } else if (e.key === 'Tab') {
            e.preventDefault();
            if (items.length > 0) {
                const firstWord = items[0].dataset.word;
                document.getElementById('searchInput').value = firstWord;
                this.updateSuggestions(firstWord);
            }
        } else if (e.key === 'ArrowDown') {
            e.preventDefault();
            this.navigateSuggestions(1);
        } else if (e.key === 'ArrowUp') {
            e.preventDefault();
            this.navigateSuggestions(-1);
        } else if (e.key === 'Escape') {
            suggestionsBox.classList.remove('active');
        }
    }

    navigateSuggestions(direction) {
        const suggestionsBox = document.getElementById('suggestions');
        const items = [...suggestionsBox.querySelectorAll('.suggestion-item')];
        if (items.length === 0) return;

        const currentIndex = items.findIndex(item => item.classList.contains('highlighted'));
        items.forEach(item => item.classList.remove('highlighted'));

        let newIndex;
        if (currentIndex === -1) {
            newIndex = direction === 1 ? 0 : items.length - 1;
        } else {
            newIndex = (currentIndex + direction + items.length) % items.length;
        }

        items[newIndex].classList.add('highlighted');
        document.getElementById('searchInput').value = items[newIndex].dataset.word;
    }

    showSuggestions() {
        const query = document.getElementById('searchInput').value;
        if (query) {
            this.updateSuggestions(query);
        }
    }

    updateSuggestions(query) {
        const suggestionsBox = document.getElementById('suggestions');
        
        if (!query) {
            suggestionsBox.classList.remove('active');
            return;
        }

        // Get last word for multi-word queries
        const words = query.split(' ');
        const lastWord = words[words.length - 1];
        
        const suggestions = this.getSuggestions(lastWord);

        if (suggestions.length === 0) {
            suggestionsBox.classList.remove('active');
            return;
        }

        suggestionsBox.innerHTML = suggestions.map((word, index) => {
            // For multi-word, replace last word with suggestion
            const fullQuery = words.length > 1 
                ? [...words.slice(0, -1), word].join(' ')
                : word;
            
            const matchLen = lastWord.length;
            const highlighted = word.substring(0, matchLen);
            const rest = word.substring(matchLen);
            
            return `
                <div class="suggestion-item ${index === 0 ? 'highlighted' : ''}" 
                     data-word="${fullQuery}"
                     onclick="searchEngine.selectSuggestion('${fullQuery}')">
                    <span class="icon">🔍</span>
                    <span class="text">
                        <span class="match">${highlighted}</span>${rest}
                    </span>
                    ${index === 0 ? '<span class="dsa-tag">Top</span>' : ''}
                </div>
            `;
        }).join('');

        suggestionsBox.classList.add('active');
    }

    selectSuggestion(word) {
        document.getElementById('searchInput').value = word;
        document.getElementById('suggestions').classList.remove('active');
        this.performSearch();
    }

    updateGhostText(query) {
        const ghostText = document.getElementById('ghostText');
        
        if (!query) {
            ghostText.classList.remove('active');
            return;
        }

        const suggestions = this.getSuggestions(query);
        if (suggestions.length > 0) {
            ghostText.textContent = `Press TAB to complete: ${suggestions[0]}`;
            ghostText.classList.add('active');
        } else {
            ghostText.classList.remove('active');
        }
    }

    performSearch() {
        const query = document.getElementById('searchInput').value.trim();
        if (!query) return;

        const results = this.searchWord(query);
        this.renderResults(results, query);
        this.renderHistory();
        this.renderRecent();
        
        document.getElementById('suggestions').classList.remove('active');
        document.getElementById('ghostText').classList.remove('active');
    }

    renderResults(results, query) {
        const container = document.getElementById('searchResults');
        const countBadge = document.getElementById('resultCount');

        if (results.length === 0) {
            container.innerHTML = '<p class="placeholder">No results found for "' + query + '"</p>';
            countBadge.textContent = '0 results';
            return;
        }

        const totalFreq = results.reduce((sum, r) => sum + r.frequency, 0);
        countBadge.textContent = `${results.length} file(s), ${totalFreq} occurrence(s)`;

        container.innerHTML = results.map((result, index) => {
            const highlightedSentences = result.sentences.map(sentence => {
                // Highlight the search term in sentences
                const regex = new RegExp(`(${query.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')})`, 'gi');
                const highlighted = sentence.replace(regex, '<span class="highlight">$1</span>');
                return `<div class="result-sentence">${highlighted}</div>`;
            }).join('');

            return `
                <div class="result-item">
                    <div class="result-header">
                        <span class="result-file">
                            <span>📄</span>
                            ${result.fileName}
                        </span>
                        <span class="result-freq">Freq: ${result.frequency}</span>
                    </div>
                    <div class="result-sentences">
                        ${highlightedSentences || '<em>No sentence context available</em>'}
                    </div>
                </div>
            `;
        }).join('');
    }

    renderHistory() {
        const container = document.getElementById('browsingHistory');
        const items = this.browsingHistory.toArray();

        if (items.length === 0) {
            container.innerHTML = '<p class="placeholder">No history yet</p>';
            return;
        }

        container.innerHTML = items.map((item, index) => `
            <div class="history-item" onclick="searchEngine.searchFromHistory('${item}')">
                <span class="number">${index + 1}</span>
                <span>${item}</span>
            </div>
        `).join('');
    }

    renderRecent() {
        const container = document.getElementById('recentSearches');
        const items = this.recentSearches.toArray();

        if (items.length === 0) {
            container.innerHTML = '<p class="placeholder">No recent searches</p>';
            return;
        }

        container.innerHTML = items.map((item, index) => `
            <div class="recent-item" onclick="searchEngine.searchFromHistory('${item}')">
                <span class="number">${index + 1}</span>
                <span>${item}</span>
            </div>
        `).join('');
    }

    searchFromHistory(query) {
        document.getElementById('searchInput').value = query;
        this.performSearch();
    }

    handleGoBack() {
        const lastSearch = this.goBack();
        if (lastSearch) {
            document.getElementById('searchInput').value = '';
            this.renderHistory();
            this.renderResults([], '');
            document.getElementById('resultCount').textContent = '0 results';
        }
    }

    handleClearRecent() {
        this.clearRecent();
        this.renderRecent();
    }

    renderDocuments() {
        const container = document.getElementById('documentsContent');
        
        container.innerHTML = Object.entries(this.documents).map(([fileName, content]) => `
            <div class="document-item">
                <div class="document-header">
                    <span>📄</span>
                    ${fileName}
                </div>
                <div class="document-content">
                    ${content.split('\n').map(line => `<p>${line}</p>`).join('')}
                </div>
            </div>
        `).join('');
    }

    toggleDocuments() {
        const content = document.getElementById('documentsContent');
        const btn = document.getElementById('toggleDocsBtn');
        
        content.classList.toggle('hidden');
        btn.textContent = content.classList.contains('hidden') ? 'Show Documents' : 'Hide Documents';
    }
}

// ============================================================
// INITIALIZE APPLICATION
// ============================================================
let searchEngine;

document.addEventListener('DOMContentLoaded', () => {
    searchEngine = new SearchEngine();
    console.log('DSA Search Engine initialized!');
});
