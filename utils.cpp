#include <iostream>
#include <fstream>   // for ifstream
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cctype>
using namespace std;
using namespace std;

#define FILE_COUNT 2
#define LINE_COUNT 100

class trie_node {
public:
    TrieNode* children[26];
    bool isEnd;
    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; ++i) children[i] = nullptr;
    }
};
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


void liveAutocompleteMode(Trie &trie) {
    string typed = "";
    string ghost = "";

    cout << "Live inline autocomplete mode.\n";
    cout << "TAB to accept suggestion, ENTER to submit, ESC to return\n\n";

    fflush(stdin);

    while (true) {
        vector<string> sug = trie.suggestions(typed, 20);
        ghost = (!sug.empty() ? "Search !!!!" : typed);

        system("cls");
        renderInputWithGhost(typed, ghost);

        cout << "Suggestions:\n";
        vector<string> show = trie.suggestions(typed, 8);
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

        int ch = _getch();

        if (ch == 27) return;
        if (ch == 13) {
            system("cls");
            cout << "Search submitted: " << typed << "\n";
            vector<string> results = trie.suggestions(typed, 20);

            if (results.empty()) cout << "No results.\n";
            else {
                for (size_t i = 0; i < results.size(); i++)
                    cout << i + 1 << ". " << results[i] << "\n";
            }
            cout << "\nPress any key...";
            _getch();
            return;
        }
        if (ch == 9) { // TAB
            if (!ghost.empty()) typed = ghost;
            continue;
        }
        if (ch == 8) { // BACKSPACE
            if (!typed.empty()) typed.pop_back();
            continue;
        }
        if (isalpha(ch)) typed.push_back((char)tolower(ch));
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

    int linenumbers[LINE_COUNT]; // fixed size array to store line numbers
    int lineindex;               // line index to record the total number of lines in the line numbers array

    FNF() {
        file_Name = "";
        frequency = 0;
        lineindex = 0;
        for(int i=0;i<LINE_COUNT;i++) linenumbers[i]=0;
    }

    FNF(string v, int f){
        file_Name = v;
        frequency = f;
        lineindex = 0;
        for(int i=0;i<LINE_COUNT;i++) linenumbers[i]=0;
    }

    void addlinenumbers(int line) {
        if(lineindex < LINE_COUNT){
            linenumbers[lineindex++] = line;
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



class Node {
public:
    string word;
    FNF *fnf_arr;
     int index=0;
     
    Node *left;
    Node *right;
    int height;

    Node(string d){
        word = d;
        height = 0;
        fnf_arr = new FNF[FILE_COUNT]; 
        left = right = NULL;
    }   
    
    ~Node() { 
	delete[] fnf_arr;
	 }

    
   void add_FNF(string f, int fr, int line) {
    // Check if the file already exists in fnf_arr
    for(int i = 0; i < index; i++) {
        if(fnf_arr[i].file_Name == f) {
            fnf_arr[i].frequency += fr;           // increment frequency
            fnf_arr[i].addlinenumbers(line);       // add line number
            return;
        }
    }

    // if File not found then add new FNF
    if(index < FILE_COUNT) {
        fnf_arr[index] =FNF(f, fr);
        fnf_arr[index].addlinenumbers(line);       // store first line number
        index++;
    } else {
        cout << "FNF fnf_array full for word: " << word << std::endl;
    }
}


};


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
	
//	void delete_from_heap(){
//		if(size==0)return;
//		fnf_arr[1]=fnf_arr[size];
//		size--;
//		heapify(fnf_arr,size,1);
//	}
	
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


class Avl{
public:
int maxi(int d1,int d2){
    return d1>d2?d1:d2;
}

int calculate_Height(Node *root){
    if(root==NULL) return -1;
    return 1 + maxi(calculate_Height(root->left), calculate_Height(root->right));
}

int bf(Node *root){
    if(root==NULL) return 0;
    int lh = root->left ? root->left->height : -1;
    int rh = root->right ? root->right->height : -1;
    return lh - rh;
}

Node* rotate_right(Node *root){
    Node *x = root->left;
    Node *temp = x->right;
    x->right = root;
    root->left = temp;
    root->height = calculate_Height(root);
    x->height = calculate_Height(x);
    return x;
}

Node* rotate_left(Node *root){
    Node *x = root->right;
    Node *temp = x->left;
    x->left = root;
    root->right = temp;
    root->height = calculate_Height(root);
    x->height = calculate_Height(x);
    return x;
}

Node* minValueNode(Node* root){
    Node* current = root;
    while(current && current->left != NULL)
        current = current->left;
    return current;
}

Node* insert(Node* &root, string d, string file_name, int lineNumber) {
    if(root == NULL) {
        Node* n = new Node(d);
        n->add_FNF(file_name, 1, lineNumber);  //  pass line number
        return n;
    }

    if(d == root->word) {
        root->add_FNF(file_name, 1, lineNumber);  //  increment frequency + add line number
        return root;
    }

    if(d < root->word)
        root->left = insert(root->left, d, file_name, lineNumber);
    else if(d > root->word)
        root->right = insert(root->right, d, file_name, lineNumber);

    // Update height and balance
    root->height = calculate_Height(root);
    int b = bf(root);

    // Left heavy
    if(b > 1) {
        if(d < root->left->word)
            return rotate_right(root);
        else {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }
    }

    // Right heavy
    if(b < -1) {
        if(d > root->right->word)
            return rotate_left(root);
        else {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
    }

    return root;
}

Node* deleteNode(Node* root, string d){
    if(root == NULL) return root;

    if(d < root->word)
        root->left = deleteNode(root->left, d);
    else if(d > root->word)
        root->right = deleteNode(root->right, d);
    else {
        if(root->left == NULL || root->right == NULL){
            Node* temp = root->left ? root->left : root->right;
            if(temp == NULL){
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->word = temp->word;
            root->right = deleteNode(root->right, temp->word);
        }
    }

    if(root == NULL) return root;

    root->height = calculate_Height(root);
    int b = bf(root);

    if(b > 1){
        if(bf(root->left) >= 0)
            return rotate_right(root);
        else{
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }
    }

    if(b < -1){
        if(bf(root->right) <= 0)
            return rotate_left(root);
        else{
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
    }

    return root;
}

void printfnf_arr(int j,Node *root){
	for(int i=0;i<j;i++){
		cout<< " "<<root->fnf_arr[i].file_Name<< " "<<root->fnf_arr[i].frequency<<" " ;
	}
	cout<<endl;
}

void inorder(Node* root){
    if(root == NULL) return;
    inorder(root->left);
    cout << root->word << " ";
    printfnf_arr(root->index,root);
    inorder(root->right);
}
// make search if found or not 
int compareresult(ResultEntry a, ResultEntry b){
    if(a.frequency != b.frequency)
        return b.frequency - a.frequency;  // descending frequency
    return a.fileName < b.fileName ? -1 : 1;  // filename ascending
}

Node* search_Node(Node* root, string word) {
    if(root == NULL) return NULL;

    if(word == root->word)
        return root;
    else if(word < root->word)
        return search_Node(root->left, word);
    else
        return search_Node(root->right, word);
}


void search(Node* root, string word,Stack &s,Queue &q) {
    Node* node = search_Node(root, word);
    if(node == NULL||word==""){
        cout << "No results found for word: " << word << endl;
        return;
    }

    // Convert FNF fnf_array to resultentry fnf_array
    ResultEntry results[FILE_COUNT];
    int resCount = 0;
    int totalHits = 0;
s.push(word);
q.enqueue(word);
    for(int i=0; i<node->index; i++){
        results[resCount].fileName = node->fnf_arr[i].file_Name;
        results[resCount].frequency = node->fnf_arr[i].frequency;
        results[resCount].linecount = node->fnf_arr[i].lineindex;
        for(int j=0;j<node->fnf_arr[i].lineindex;j++)
            results[resCount].linenumbers[j] = node->fnf_arr[i].linenumbers[j];
        totalHits += results[resCount].frequency;
        resCount++;
    }
    
    heap h;
    for(int i=0;i<FILE_COUNT;i++){
    	h.insert(node->fnf_arr[i]);
	}
	
	h.heap_sort();
	
	
	
	
    
    
    

    // Sort results
//    for(int i=0;i<resCount-1;i++){
//        for(int j=0;j<resCount-i-1;j++){
//            if(compareresult(results[j], results[j+1]) > 0){
//                ResultEntry temp = results[j];
//                results[j] = results[j+1];
//                results[j+1] = temp;
//            }
//        }
//    }

    // Display results 
    cout << "Search results for word: " << word << endl;
    int j=0;
    for(int i=h.size;i>h.size-3;i--){
    	
        cout << j+1 << ". " << h.fnf_arr[i].file_Name
             << " (Frequency: " <<h.fnf_arr[i].frequency << ")" << endl;

        ifstream file(h.fnf_arr[i].file_Name);
        if(!file.is_open()){
            cout << "  Cannot open file to show snippet." << endl;
            continue;
        }

        string lineText;
        int lineNum = 1;
        while(getline(file, lineText)) {
            for(int j=0;j<h.fnf_arr[i].lineindex;j++){
                if(h.fnf_arr[i].linenumbers[j] == lineNum){
                    int start = max(0, (int)lineText.find(word)-30);
                    int end = min((int)lineText.length(), start+60);
                    cout << "  Line " << lineNum << ": " << lineText.substr(start, end-start) << endl;
                }
            }
            lineNum++;
        }
        file.close();
    }

    cout << "Total hits: " << totalHits << endl;
    cout << "Files matched: " << resCount << endl;
}
//Deleting AVL class prevent from memory leak
void deleteAVL(Node* root) {
    if(root == NULL) return;

    deleteAVL(root->left);
    deleteAVL(root->right);

    delete root; 
}


};