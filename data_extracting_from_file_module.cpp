#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <cctype>
#include "utils.cpp"

using namespace std;
unordered_set<string> stopwords = { "a","an","and","are","as","at","be","but","by",
                                    "for","if","in","into","is","it","no","not","of",
                                    "on","or","such","that","the","their","then","there",
                                    "these","they","this","to","was","will","with" };

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

// Extract words from files and print non-stopwords with line numbers
void extract_from_files(vector<string>& files,Avl* &avl,Node * &root) {
    for (int i = 0; i < files.size(); i++) {
        ifstream file(files[i].c_str());
        if (!file) {
            cout << "Error opening file: " << files[i] << endl;
            continue;
        }
		bool rooted=false;
        string line;
        int lineNumber = 0;
        while (getline(file, line)) {
            lineNumber++;
            string word = "";
            for (int j = 0; j <= line.length(); j++) {
                if (j == line.length() || !isalnum(line[j])) {
                    if (!word.empty()) {
                        string cleaned = remove_unwanted_characters(word);
                        if (!cleaned.empty() && stopwords.find(cleaned) == stopwords.end()) {
                        
							root=avl->insert(root,cleaned,files[i],lineNumber);
							 cout << cleaned  << " (" << files[i] << ", line " << lineNumber << ")" << endl;

							
                        }
                        word = "";
                    }
                } else {
                    word += line[j];
                }
            }
        }
    }
}

int main() {
    Avl *avl = new Avl();          // initialize AVL
    vector<string> files = {"t1.txt", "t2.txt"};

    // Read first word of first file to create root
    string firstWord;
    ifstream firstFile(files[0]);
    if (firstFile >> firstWord) {
        firstWord = remove_unwanted_characters(firstWord);
    } else {
        cout << "First file is empty!" << endl;
        return 1;
    }
    Node* root = new Node(firstWord);
    root->add_FNF(files[0], 1,1); 

    
    extract_from_files(files, avl, root);

    cout << "\n\nInorder traversal of AVL (unique words):\n";
    avl->inorder(root);
    cout << endl;
avl->search(root,"ahmad");
    delete avl;  
    return 0;
}
