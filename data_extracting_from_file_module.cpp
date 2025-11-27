#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <cctype>
#include "utils.cpp"
#include <windows.h>

using namespace std;

unordered_set<string> stopwords = { "a","an","and","are","as","at","be","but","by",
                                    "for","if","in","into","is","it","no","not","of",
                                    "on","or","such","that","the","their","then","there",
                                    "these","they","this","to","was","will","with" };

void setColor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
}

// Extract words from files and print non-stopwords with line numbers
void extract_from_files(vector<string>& files,Avl* &avl,Node * &root,Trie &trie) {
    for (int i = 0; i < files.size(); i++) {
        ifstream file(files[i].c_str());
        if (!file) {
            setColor(12); // Red
            cout << "Error opening file: " << files[i] << endl;
            setColor(7);
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
                            if(rooted){
                                root=avl->insert(root,cleaned,files[i],lineNumber);
                                setColor(10); // Light Green
                                cout << cleaned  << " (" << files[i] << ", line " << lineNumber << ")" << endl;
                                setColor(7);
                                trie.insert(cleaned);
                            } else {
                                rooted=true;
                            }
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
    Avl *avl = new Avl();
    Trie trie;          
    vector<string> files = {"t1.txt", "t2.txt"};
    Stack browsinghistory;
    Queue recentsearches;

    string firstWord;
    ifstream firstFile(files[0]);
    if (firstFile >> firstWord) {
        firstWord = remove_unwanted_characters(firstWord);
    } else {
        setColor(12);
        cout << "First file is empty!" << endl;
        setColor(7);
        return 1;
    }
    Node* root = new Node(firstWord);
    root->add_FNF(files[0], 1,1); 

    extract_from_files(files, avl, root,trie);

    setColor(11);
    cout << "\n\nInorder traversal of AVL (unique words):\n";
    setColor(7);
    avl->inorder(root);
    cout << endl;

    avl->search(root,"rafay",browsinghistory,recentsearches);

    int choice;
    string query;

    setColor(13); // Light Magenta
    cout << "\nSEARCH ENGINE" << endl;
    setColor(7);

    do {
        cout<<endl;
        setColor(9); // Light Blue
        cout << "===========================\n";
        setColor(14); // Yellow
        cout << "|1. Search Word           |\n";
        cout << "|2. View All Documents    |\n";
        cout << "|3. Show Browsing History |\n";
        cout << "|4. Show Recent Searches  |\n";
        cout << "|5. Go Back               |\n";
        cout << "|6. Clear Recent Searches |\n";
        setColor(12); // Light Red
        cout << "|7. Exit                  |\n";
        setColor(9);
        cout << "===========================\n";
        setColor(7);
        cout << "Enter choice: ";
        cin >> choice;

        if(choice<1||choice >7){
            setColor(12); 
            cout<<"\n Invalid choice";
            setColor(7);
        } else {
            switch (choice) {
                case 1:
                {
                    cin.clear();
                    string dummy;
                    getline(cin, dummy);
                    trie.liveAutocompleteMode(trie, avl, root, browsinghistory, recentsearches);
                    break;
                }
                case 2:
                    break;
                case 3:
                    browsinghistory.display();
                    break;
                case 4:
                    recentsearches.display();
                    break;
                case 5:
                    browsinghistory.pop();
                    break;
                case 6:
                    while (!recentsearches.isEmpty()) {
                        recentsearches.dequeue();
                    }
                    setColor(14);
                    cout << "Recent searches cleared" << endl;
                    setColor(7);
                    break;
                case 7:
                    setColor(12);
                    cout << "Exiting" << endl;
                    setColor(7);
                    break;
                default:
                    setColor(12);
                    cout << "Invalid choice" << endl;
                    setColor(7);
                    break;
            }
        }
        cout<<endl;
    } while (choice != 7);

    delete avl;
    return 0;
}
