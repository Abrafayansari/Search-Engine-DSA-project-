#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <cctype>
#include "utils.cpp"
#include <windows.h>

using namespace std;






int main() {
separate_chaining hashtable;   
 Trie trie;          
    vector<string> files = {"t1.txt", "t2.txt"};
    Stack browsinghistory;
    Queue recentsearches;

    
    extract_from_files(files, hashtable,trie);

    setColor(11);
    cout << "\n\nInorder traversal of AVL (unique words):\n";
    setColor(7);
    cout << endl;


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
                    trie.liveAutocompleteMode(trie,hashtable , browsinghistory, recentsearches);
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

    return 0;
}