#include <iostream>
#include <string>
using namespace std;

class S_Node {
public:
    string data;
    S_Node* next;
    S_Node(string val) {
        data = val;
        next = nullptr;
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
        
        S_Node* newNode = new Node(url);
        
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

class SearchEngine {
private:
    string documents[15] = {
        "search engine google web browsing internet",
        "code repository github programming developers",
        "programming help stackoverflow questions answers",
        "encyclopedia wikipedia knowledge information",
        "video platform youtube entertainment movies",
        "ecommerce amazon shopping products online",
        "social media facebook friends network",
        "microblogging twitter tweets news",
        "professional network linkedin jobs career",
        "photo sharing instagram pictures social",
        "discussion forum reddit communities posts",
        "software company microsoft windows office",
        "technology company apple iphone macbook",
        "streaming service netflix movies entertainment",
        "music streaming spotify songs playlist"
    };

    string toLower(string str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str[i] = str[i] + 32;
            }
        }
        return str;
    }

    int countFrequency(string text, string word) {
        string textLower = toLower(text);
        string wordLower = toLower(word);
        int frequency = 0;
        
        for (int i = 0; i <= textLower.length() - wordLower.length(); i++) {
            bool match = true;
            for (int j = 0; j < wordLower.length(); j++) {
                if (textLower[i + j] != wordLower[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                if ((i == 0 || textLower[i-1] == ' ') && 
                    (i + wordLower.length() == textLower.length() || 
                     textLower[i + wordLower.length()] == ' ')) {
                    frequency++;
                }
            }
        }
        return frequency;
    }

public:
    void searchWord(string query, Stack& history, Queue& recent) {
        cout << "Searching for: " << query << endl;
        
        bool found = false;
        int totalFrequency = 0;
        
        for (int i = 0; i < 15; i++) {
            int freq = countFrequency(documents[i], query);
            if (freq > 0) {
                cout << "Document " << i+1 << ": " << documents[i] << endl;
                cout << "Frequency: " << freq << " times" << endl;
                found = true;
                totalFrequency += freq;
            }
        }
        
        if (!found) {
            cout << "No documents found for " << query << endl;
        } else {
            cout << "Total frequency: " << totalFrequency << " times" << endl;
        }
        
        history.push(query);
        recent.enqueue(query);
    }

    void displayAllDocuments() {
        cout << "All 15 Documents:" << endl;
        for (int i = 0; i < 15; i++) {
            cout << i+1 << ". " << documents[i] << endl;
        }
    }
};

int main() {
    Stack browsingHistory;
    Queue recentSearches;
    SearchEngine engine;
    
    int choice;
    string query;

    cout << "SEARCH ENGINE" << endl;

    do {
        cout << "1. Search Word" << endl;
        cout << "2. View All Documents" << endl;
        cout << "3. Show Browsing History" << endl;
        cout << "4. Show Recent Searches" << endl;
        cout << "5. Go Back" << endl;
        cout << "6. Clear Recent Searches" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter search word: ";
                cin.ignore();
                getline(cin, query);
                if (!query.empty()) {
                    engine.searchWord(query, browsingHistory, recentSearches);
                }
                break;

            case 2:
                engine.displayAllDocuments();
                break;

            case 3:
                browsingHistory.display();
                break;

            case 4:
                recentSearches.display();
                break;

            case 5:
                browsingHistory.pop();
                break;

            case 6:
                while (!recentSearches.isEmpty()) {
                    recentSearches.dequeue();
                }
                cout << "Recent searches cleared" << endl;
                break;

            case 7:
                cout << "Exiting" << endl;
                break;

            default:
                cout << "Invalid choice" << endl;
        }

    } while (choice != 7);

    return 0;
}