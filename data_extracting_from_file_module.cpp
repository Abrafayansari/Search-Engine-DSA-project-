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
void extract_from_files(vector<string>& files,Avl* &avl,Node * &root,Trie &trie) {
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
                        if(rooted){
                        	root=avl->insert(root,cleaned,files[i],lineNumber);
							 cout << cleaned  << " (" << files[i] << ", line " << lineNumber << ")" << endl;
							trie->insert(cleaned);
						}else{
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
	Trie trie;          // initialize AVL
    vector<string> files = {"t1.txt", "t2.txt"};
Stack browsinghistory;
    Queue recentsearches;
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
  avl->search(root,"rafay",browsinghistory,recentsearches);
    
     
    
    int choice;
    string query;

    cout << "SEARCH ENGINE" << endl;

    do {
    	cout<<endl;
    	cout << "===========================\n";
        cout << "|1. Search Word           |" << endl;
        cout << "|2. View All Documents    |" << endl;
        cout << "|3. Show Browsing History |" << endl;
        cout << "|4. Show Recent Searches  |" << endl;
        cout << "|5. Go Back               |" << endl;
        cout << "|6. Clear Recent Searches |" << endl;
        cout << "|7. Exit                  |" << endl;
        cout << "===========================\n";
        cout << "Enter choice: ";
        cin >> choice;
        if(choice<1||choice >7){
        	cout<<"\n Invalid";
		}else{
			 switch (choice) {
            case 1:
                cout << "Enter search word: ";
                cin>>query;
                if (!query.empty()) {
                cout<<"Results .........\n";
                 cin.clear();
//            string dummy;
//			 getline(cin, dummy);
//            liveAutocompleteMode(trie);
  avl->search(root,remove_unwanted_characters(query),browsinghistory,recentsearches);
  
                }
                break;

            case 2:
//                engine.displayAllDocuments();
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
                cout << "Recent searches cleared" << endl;
                break;

            case 7:
                cout << "Exiting" << endl;
                break;

            default:
                cout << "Invalid choice" << endl;
                break;
        }
		}
		cout<<endl;
       

    } while (choice != 7);
delete avl;
    return 0;
}