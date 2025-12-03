
#include <iostream>
#include <fstream>   // for ifstream
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <unordered_set>
#include <windows.h>
#include <cctype>
using namespace std;

#define FILE_COUNT 20
#define LINE_COUNT 100


 
    bool readFileIntoCharArray(const string &filename, char *buffer, int &len) {
    ifstream file(filename.c_str());
    if(!file.is_open()) return false;

    len = 0;
    char ch;

    while(file.get(ch)) {
        buffer[len] = ch;
        len++;
        if(len >= 90000) break; // Safe limit
    }

    buffer[len] = '\0';
    file.close();
    return true;
}

void buildLPS(const string &pat, int lps[]) {
    int m = pat.length();
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}


int KMP(const char *text, int n, const string &pat) {
    int m = pat.length();
    if (m == 0) return -1;

    int *lps = new int[m];
    buildLPS(pat, lps);

    int i = 0; // text index
    int j = 0; // pattern index

    while (i < n) {
        if (text[i] == pat[j]) {
            i++; j++;
        }

        if (j == m) {
            delete[] lps;
            return i - j;   // match starting index
        }

        else if (i < n && text[i] != pat[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }

    delete[] lps;
    return -1;
}


unordered_set<string> stopwords = { "a","an","and","are","as","at","be","but","by",
                                    "for","if","in","into","is","it","no","not","of",
                                    "on","or","such","that","the","their","then","there",
                                    "these","they","this","to","was","will","with" };

void setColor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
}



void extractSentence(const char *buffer, int len, int pos, char *result) {
    int start = pos;
    int end = pos;
    // Move left until full stop or file start
    while(start > 0 && buffer[start] != '.' && buffer[start] != '?' && buffer[start] != '!') {
        start--;
    }
    // now if buffer[start] is punctuation we want the next character
    if (start < pos && (buffer[start] == '.' || buffer[start] == '?' || buffer[start] == '!')) start++;
    if (start < 0) start = 0;
    // Move right until full stop or file end
    while(end < len && buffer[end] != '.' && buffer[end] != '?' && buffer[end] != '!') {
        end++;
    }
    if (end >= len) end = len - 1;
    // copy
    int idx = 0;
    for (int i = start; i <= end && i < len; ++i) result[idx++] = buffer[i];
    result[idx] = '\0';
}



string remove_unwanted_characters(const string& s) {
    string s1 = "";
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] >= 'A' && s[i] <= 'Z') ||
            (s[i] >= 'a' && s[i] <= 'z') ||
            (s[i] >= '0' && s[i] <= '9')) {
            s1 += tolower(s[i]);
        }
    }
    return s1;
}
class S_Node {
public:
    string data;
    S_Node* next;
    S_Node(string val) {
        data = val;
        next = nullptr;
    }
};

class FNF{
public:
    string file_Name;
    int frequency;
  int positions[LINE_COUNT]; 
    int linenumbers[LINE_COUNT]; // fixed size array to store line numbers
    int lineindex;               // line index to record the total number of lines in the line numbers array

    FNF() {
        file_Name = "";
        frequency = 0;
        lineindex = 0;
        for(int i=0;i<LINE_COUNT;i++){
        	 linenumbers[i]=0;
        	 positions[i]=-1;
		}
    }

    FNF(string v, int f){
        file_Name = v;
        frequency = f;
        lineindex = 0;
for(int i=0;i<LINE_COUNT;i++){
        	 linenumbers[i]=0;
        	 positions[i]=-1;
		}    }

 void addOccurrence(int line, int pos) {
        if(lineindex < LINE_COUNT){
            linenumbers[lineindex] = line;
            positions[lineindex] = pos;
            lineindex++;
        } else {
            cout << "LineNumbers array full for file: " << file_Name << endl;
        }
    }

    
};
class ResultEntry {
public:
    string fileName;
    int frequency;
    int linenumbers[LINE_COUNT];
    int linecount;

    ResultEntry() { frequency = 0;
linecount = 0; }
};




class Node{
public:
string word;
    FNF *fnf_arr;
     int index=0;
Node *next;

Node(string d){
        word = d;
        fnf_arr = new FNF[FILE_COUNT];
        next=NULL;
    }

~Node() {
delete[] fnf_arr;
}

void add_FNF(string f, int fr, int line, int pos) {
    // Check if file entry exists
    for(int i = 0; i < index; i++) {
        if(fnf_arr[i].file_Name == f) {
            fnf_arr[i].frequency += fr;
            fnf_arr[i].addOccurrence(line, pos);
            return;
        }
    }
    // new file entry
    if(index < FILE_COUNT) {
        fnf_arr[index] = FNF(f, fr);
        fnf_arr[index].addOccurrence(line, pos);
        index++;
    } else {
        cout << "FNF fnf_array full for word: " << word << std::endl;
    }
}

 
};


class trie_node {
public:
    trie_node* children[26];
    bool isend;
    trie_node() {
        isend = false;
        for (int i = 0; i < 26; ++i) children[i] = nullptr;
    }
};



class Stack {
private:
    S_Node* top;
public:
    Stack() {
        top = nullptr;
    }

    void push(string url) {
        S_Node* newNode = new S_Node(url);
        newNode->next = top;
        top = newNode;
    }



/////////////////////
string toString() {
    if (!top) return "(empty)\n";

    string result;
    S_Node* temp = top;
    while (temp) {
        result += temp->data + "\n";
        temp = temp->next;
    }
    return result;
}


    void pop() {
        if (top == nullptr) {
            cout << "History is empty" << endl;
            return;
        }
        S_Node* temp = top;
        top = top->next;
        delete temp;
    }

    string peek() {
        if (top == nullptr) {
            return "";
        }
        return top->data;
    }

    void display() {
        if (top == nullptr) {
            cout << "History is empty" << endl;
            return;
        }
        cout << "Browsing History:" << endl;
        S_Node* temp = top;
        int count = 1;
        while (temp != nullptr) {
            cout << count << ". " << temp->data << endl;
            temp = temp->next;
            count++;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};
//deleting the Stack to prevent from memory leak
void clearStack(Stack &s){
    while(!s.isEmpty()) s.pop();
}



class Queue {
private:
    S_Node* front;
    S_Node* rear;
    int count;
    const int MAX_SIZE = 5;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void enqueue(string url) {
        if (count >= MAX_SIZE) {
            dequeue();
        }
       
        S_Node* newNode = new S_Node(url);
       
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    void dequeue() {
        if (front == nullptr) {
            return;
        }
        S_Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        count--;
    }
   
    ///////////////////////////////
    string toString() {
    if (!front) return "(empty)\n";

    string result;
    S_Node* temp = front;
    while (temp) {
        result += temp->data + "\n";
        temp = temp->next;
    }
    return result;
}


    void display() {
        if (front == nullptr) {
            cout << "No recent searches" << endl;
            return;
        }
        cout << "Recent 5 Searches:" << endl;
        S_Node* temp = front;
        int position = 1;
        while (temp != nullptr) {
            cout << position << ". " << temp->data << endl;
            temp = temp->next;
            position++;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }
};
//deleting QUEUE prevent from memory leak
void clearQueue(Queue &q){
    while(!q.isEmpty()) q.dequeue();
}


class heap{
public:
FNF fnf_arr[1000];
int size;

heap(){
size=0;
}

void insert(FNF d){
if(size==1000)return;
size++;
fnf_arr[size]=d;
int i=size;
while(i>1){
int parent=i/2;

if(fnf_arr[parent].frequency<fnf_arr[i].frequency){
  swap(fnf_arr[parent],fnf_arr[i]);
  i=parent;
}else{
return;
}

}
}

// void delete_from_heap(){
// if(size==0)return;
// fnf_arr[1]=fnf_arr[size];
// size--;
// heapify(fnf_arr,size,1);
// }

void heapify(FNF fnf_arr1[],int size1,int i){
int tobesort=i;
int left=2*i;
int right=2*i+1;

if(left<=size1&&fnf_arr1[left].frequency>fnf_arr1[tobesort].frequency){
tobesort=left;
}

if(right<=size1&&fnf_arr1[right].frequency>fnf_arr1[tobesort].frequency){
tobesort=right;
}

if(i!=tobesort){
swap(fnf_arr1[tobesort],fnf_arr1[i]);
heapify(fnf_arr1,size1,tobesort);
}


}

void heap_sort(){
for(int i=size;i>1;i--){
swap(fnf_arr[i],fnf_arr[1]);
heapify(fnf_arr,i-1,1);
}
}
};







class separate_chaining{
public:
Node **arr;
int size;
int entries;


separate_chaining(){
size=10000;
arr=new Node* [size];
for(int i=0;i<size;i++){
arr[i]=NULL;
}
entries=0;
}

int hash(string s) {
        long long h= 0;
        long long p= 31;
        long long pow= 1;

        for (char c : s) {
            h =(h+(c-'a' + 1)*pow)%size;
            pow =(pow*p)%size;
        }
        return (int)h;
    }
   
   
   

void insert(string word,string filename,int line,int pos) {
        float load=(float)entries/(float)size;

        if (load>=0.7) {
            rehash();
        }

        int key=hash(word);

        Node *temp=arr[key];

        // If already exists  update FNF
        while (temp != NULL) {
            if (temp->word == word) {
                temp->add_FNF(filename, 1, line,pos);
                return;
            }
            temp = temp->next;
        }

        // New word  create node
        Node *newnode = new Node(word);
        newnode->add_FNF(filename,1,line,pos);
        newnode->next=arr[key];
        arr[key]=newnode;
        entries++;
    }

 void rehash() {
        Node **old=arr;
        int oldSize=size;
         size =size*2;
        entries = 0;
        arr=new Node*[size];
        for (int i=0;i<size;i++)
            arr[i]=NULL;

        for (int i = 0; i < oldSize; i++) {
            Node *temp=old[i];
            while(temp!=NULL) {
                for(int j =  0;j< temp->index;j++) {
                    // reinsert each file occurrence
                    for (int k = 0; k < temp->fnf_arr[j].lineindex; k++) {
                        insert(temp->word,temp->fnf_arr[j].file_Name,temp->fnf_arr[j].linenumbers[k],temp->fnf_arr[j].positions[k]);
                    }
                }
                temp=temp->next;
            }
        }

        delete [] old;
    }

Node* search(string word) {
        int key=hash(word);
        Node *temp=arr[key];

        while (temp!=NULL) {
            if (temp->word==word)
                return temp;
            temp=temp->next;
        }
        return NULL;
    }


void delete_node(string d){
int key=hash(d);
Node *curr=arr[key];
Node *prev=NULL;
if(curr==NULL){
cout<<"empty";
return;
}

while(curr!=NULL){

if(curr->word==d){
if(prev!=NULL)
prev->next=curr->next;
else arr[key]=curr->next;
delete curr;
return;
}
prev=curr;
curr=curr->next;
}
}

void display(){
for(int i=0;i<size;i++){
Node *temp=arr[i];
cout<< i<<" ";
while(temp!=NULL){
cout<<temp->word<<"->";
temp=temp->next;

}

cout<<"NULL\n";

}
}

void searchword(const string &wordRaw, Stack &s, Queue &q) {
    string word = remove_unwanted_characters(wordRaw);

    if (word.empty()) {
        cout << "No results found.\n";
        return;
    }

    Node *node = search(word);
    if (!node) {
        cout << "No results found.\n";
        return;
    }

    // History
    s.push(word);
    q.enqueue(word);

    // Build heap (sorted by frequency)
    heap h;
    for (int i = 0; i < node->index; i++)
        h.insert(node->fnf_arr[i]);
    h.heap_sort();

    cout << "Search results for: " << word << endl;

    // For each file that contains the word
    for (int k = 0; k < node->index; k++) {

        cout << k + 1 << ". " << node->fnf_arr[k].file_Name
             << " (Freq: " << node->fnf_arr[k].frequency << ")\n";

        char buffer[100000];
        int len = 0;

        if (!readFileIntoCharArray(node->fnf_arr[k].file_Name, buffer, len)) {
            cout << "  Cannot open file.\n";
            continue;
        }

        // ---- Make lowercase copy of buffer (for case-insensitive searching) ----
        static char lowerBuf[100000];
        for (int i = 0; i < len; ++i)
            lowerBuf[i] = tolower(buffer[i]);
        lowerBuf[len] = '\0';

        // ---- ALSO lowercase the search word ----
        string lowWord = word;
        for (char &c : lowWord) c = tolower(c);

        int start = 0;
        while (start < len) {

            int pos = KMP(lowerBuf + start, len - start, lowWord);
            if (pos == -1) break;      // no more matches
            pos += start;               // convert local index → global

            // ----- Extract sentence -----
            char sentence[2000];
            extractSentence(buffer, len, pos, sentence);
            cout << "  Sentence: " << sentence << endl;

            // ----- Skip ahead to next punctuation instead of skipping word length -----
            while (pos < len && buffer[pos] != '.' && buffer[pos] != '?' && buffer[pos] != '!')
                pos++;

            start = pos + 1;            // move to next sentence
        }
    }
}



//void searchword(const string &wordRaw, Stack &s, Queue &q) {
//    string word = wordRaw;
//    if (word.empty()) {
//        cout << "No results found.\n";
//        return;
//    }
//
//    Node *node = search(word);
//    if (!node) {
//        cout << "No results found.\n";
//        return;
//    }
//
//    // History
//    s.push(word);
//    q.enqueue(word);
//
//    // Build heap with FNF entries
//    heap h;
//    for (int i = 0; i < node->index; i++)
//        h.insert(node->fnf_arr[i]);
//
//    h.heap_sort(); // highest freq at end
//
//    cout << "Search results for: " << word << endl;
//
//    // Show all files
//    for (int k = 0; k < node->index; k++) {
//
//        cout << k + 1 << ". " << node->fnf_arr[k].file_Name
//             << " (Freq: " << node->fnf_arr[k].frequency << ")\n";
//
//        // Read file into char buffer
//        char buffer[100000];
//        int len = 0;
//        if (!readFileIntoCharArray(node->fnf_arr[k].file_Name, buffer, len)) {
//            cout << "  Cannot open file.\n";
//            continue;
//        }
//
//        // ⭐ NEW LOOP: iterate through every occurrence by positions[]
////        for (int occ = 0; occ < node->fnf_arr[k].lineindex; occ++) {
////
////            int position = node->fnf_arr[k].positions[occ];  // exact char position
////
////            // Extract full sentence
////            char sentence[2000];
////            extractSentence(buffer, len, position, sentence);
////
////            cout << "  Sentence: " << sentence << endl;
////        }
//
//static char lowerBuf[100000];
//for (int i = 0; i < len; ++i)
//    lowerBuf[i] = tolower(buffer[i]);
//lowerBuf[len] = '\0';
//
//int start = 0;
//while (start < len) {
//    int position = KMP(lowerBuf + start, len - start, word);
//    if (position == -1) break;
//
//    position += start; // adjust
//
//    char sentence[2000];
//    extractSentence(buffer, len, position, sentence);
//    cout << "  Sentence: " << sentence << endl;
//
//    // Move past the entire matched word to avoid duplicate matches
//    start = position + word.length();
//}



    //}//
//}


};



// Extract words from files and print non-stopwords with line numbers

class Trie {
public:
    trie_node* root;
    Trie() { root = new trie_node(); }

    static string normalize(const string &s) {
        string out;
        for (char c : s)
            if (isalpha((unsigned char)c))
                out.push_back((char)tolower((unsigned char)c));
           
        return out;
       
    }

    void insert(const string &rawWord) {
        string word = normalize(rawWord);
        if (word.empty()) return;

        trie_node* cur = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) cur->children[idx] = new trie_node();
            cur = cur->children[idx];
        }
        cur->isend = true;
    }

    void collect(trie_node* node, const string &prefix, vector<string> &out, int limit = 50) {
        if (!node) return;
        if (node->isend) {
            out.push_back(prefix);
            if ((int)out.size() >= limit) return;
        }
        for (int i = 0; i < 26 && (int)out.size() < limit; ++i) {
            if (node->children[i]) {
                collect(node->children[i], prefix + char('a' + i), out, limit);
            }
        }
    }

    vector<string> suggestions(const string &rawPrefix, int limit = 50) {
        string prefix = normalize(rawPrefix);
        vector<string> out;

        trie_node* cur = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!cur->children[idx]) return out;
            cur = cur->children[idx];
        }

        collect(cur, prefix, out, limit);
        return out;
    }


void setColor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
}

void renderInputWithGhost(const string &typed, const string &ghost) {
    setColor(7);
    cout << "Search: " << typed;

    if (!ghost.empty()) {
        if (ghost.size() >= typed.size() && ghost.substr(0, typed.size()) == typed) {
            string rem = ghost.substr(typed.size());
            setColor(8);
            cout << rem;
            setColor(7);
        }
    }
    cout << "\n\n";
}


void liveAutocompleteMode(Trie &trie, separate_chaining &table, Stack &s, Queue &q) {

    string typed = "";
    string ghost = "";

    cout << "Live inline autocomplete mode.\n";
    cout << "TAB to accept suggestion, ENTER to submit, ESC to return\n\n";
    fflush(stdin);

    while (true) {

        vector<string> sug = trie.suggestions(typed, 20);
        ghost = (!sug.empty() ? sug[0] : "");

        system("cls");
        renderInputWithGhost(typed, ghost);

        // show suggestions
        cout << "Suggestions:\n";
        vector<string> show;
        for (size_t i = 0; i < sug.size() && i < 8; i++)
            show.push_back(sug[i]);

        if (show.empty()) cout << "  (none)\n";
        else {
            for (size_t i = 0; i < show.size(); i++) {
                if (i == 0) {
                    setColor(144);
                    cout << "  " << show[i] << "  <- top\n";
                    setColor(7);
                } else {
                    cout << "  " << show[i] << "\n";
                }
            }
        }

        cout << "\n(ESC to return)\n";

        // Read key
        int ch = _getch();

        // ---------------------------
        // ESC
        // ---------------------------
        if (ch == 27) return;

        // ---------------------------
        // ENTER
        // ---------------------------
        if (ch == 13) {
            system("cls");
            cout << "Search submitted: " << typed << "\n";
            table.searchword( remove_unwanted_characters(typed), s, q);
            cout << "\nPress any key...";
            _getch();
            return;
        }

        // ---------------------------
        // TAB
        // ---------------------------
        if (ch == 9) {
            if (!ghost.empty()) typed = ghost;
            continue;
        }

        // ---------------------------
        // BACKSPACE
        // ---------------------------
        if (ch == 8) {
            if (!typed.empty()) typed.pop_back();
            continue;
        }

        // ---------------------------
        // SPECIAL KEYS (arrow keys, F1-F12)
        // They come in pairs: first 224 or 0
        // Ignore them completely
        // ---------------------------
        if (ch == 224 || ch == 0) {
            _getch(); // swallow second byte
            continue;
        }

        // ---------------------------
        // Accept alphabets only
        // ---------------------------
        if (isalpha(ch)) {
            typed.push_back((char)tolower(ch));
            continue;
        }

        // ---------------------------
        // Ignore all other keys
        // ---------------------------
        continue;
    }
}


//    void preloadSamples() {
//        vector<string> sample = {
//            "cat","cap","car","care","carbon","cart","cartoon","cater",
//            "dog","door","dot","dove","data","date",
//            "apple","apply","application","apt","aptitude",
//            "search","sea","season","second","secure"
//        };
//        for (auto &w : sample) insert(w);
//    }
};

void extract_from_files(vector<string>& files, separate_chaining &hashtable, Trie &trie) {
    for (int i = 0; i < files.size(); i++) {

        ifstream file(files[i].c_str());
        if (!file) {
            setColor(12);
            cout << "Error opening file: " << files[i] << endl;
            setColor(7);
            continue;
        }

        string line;
        int lineNumber = 0;

        int file_offset = 0;   // <----- IMPORTANT NEW VARIABLE

        while (getline(file, line)) {

            lineNumber++;
            int lineLen = (int)line.size();
            string word = "";

            for (int j = 0; j <= line.length(); j++) {

                if (j == line.length() || !isalnum(line[j])) {
                    if (!word.empty()) {

                        string cleaned = remove_unwanted_characters(word);

                        if (!cleaned.empty() && stopwords.find(cleaned) == stopwords.end()) {

                            // ---------------------------------------
                            // NEW LOGIC FOR REAL OCCURRENCE OFFSET
                            // ---------------------------------------
                            int start_in_line = j - (int)word.length();
                            int global_pos = file_offset + start_in_line;

                            // Call your updated insert()
                            hashtable.insert(cleaned, files[i], lineNumber, global_pos);
                            // ---------------------------------------

                            setColor(10);
                            cout << cleaned << " (" << files[i]
                                 << ", line " << lineNumber << ")" << endl;
                            setColor(7);

                            trie.insert(cleaned);
                        }

                        word = "";
                    }
                }
                else {
                    word += line[j];
                }
            }

            // -------------------------------------
            // UPDATE OFFSET FOR NEXT LINE
            // +1 for '\n' that getline removes
            // -------------------------------------
            file_offset += lineLen + 1;
        }
    }
}






