#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// C++11 unordered_set for stopwords
unordered_set<string> stopwords = { "a","an","and","are","as","at","be","but","by",
                                    "for","if","in","into","is","it","no","not","of",
                                    "on","or","such","that","the","their","then","there",
                                    "these","they","this","to","was","will","with" };

// Remove punctuation and convert to lowercase
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
void extract_from_files(vector<string>& files) {
    for (int i = 0; i < files.size(); i++) {
        ifstream file(files[i].c_str());
        if (!file) {
            cout << "Error opening file: " << files[i] << endl;
            continue;
        }

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
                            cout << cleaned << " (" << files[i] << ", line " << lineNumber << ")" << endl;
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
    vector<string> files;
    files.push_back("t1.txt");
    files.push_back("t2.txt");

    extract_from_files(files);

    return 0;
}
