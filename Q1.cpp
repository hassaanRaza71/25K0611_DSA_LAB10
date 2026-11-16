#include <iostream>
#include <string>

using namespace std;

struct Node {
    string hashtag;
    int count;
    Node* next;
    Node(string tag) : hashtag(tag), count(1), next(nullptr) {}
};

class HotTopicTracker {
private:
    int table_size;
    Node** table;

    int hashFunction(const string& tag) {
        unsigned long hash = 0;
        for (char c : tag) {
            hash = (hash * 31 + c) % table_size;
        }
        return hash % table_size;
    }

public:
    HotTopicTracker(int size) : table_size(size) {
        table = new Node*[table_size];
        for (int i = 0; i < table_size; i++) {
            table[i] = nullptr;
        }
    }

    ~HotTopicTracker() {
        for (int i = 0; i < table_size; i++) {
            Node* curr = table[i];
            while (curr != nullptr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insertTag(const string& tag) {
        int index = hashFunction(tag);
        Node* curr = table[index];

        while (curr != nullptr) {
            if (curr->hashtag == tag) {
                curr->count++;
                return;
            }
            curr = curr->next;
        }

        Node* newNode = new Node(tag);
        newNode->next = table[index];
        table[index] = newNode;

        checkLongestChain();
    }

    int searchTag(const string& tag) {
        int index = hashFunction(tag);
        Node* curr = table[index];

        while (curr != nullptr) {
            if (curr->hashtag == tag) {
                return curr->count;
            }
            curr = curr->next;
        }
        return 0;
    }

    void removeTag(const string& tag) {
        int index = hashFunction(tag);
        Node* curr = table[index];
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->hashtag == tag) {
                if (prev == nullptr) {
                    table[index] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                cout << "Removed banned tag: " << tag << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Tag not found: " << tag << endl;
    }

    int checkLongestChain() {
        int maxLen = 0;
        for (int i = 0; i < table_size; i++) {
            int currentLen = 0;
            Node* curr = table[i];
            while (curr != nullptr) {
                currentLen++;
                curr = curr->next;
            }
            if (currentLen > maxLen) {
                maxLen = currentLen;
            }
        }

        if (maxLen > 5) {
            cout << "[WARNING] System Overload! Longest chain is " << maxLen << " nodes." << endl;
        }
        return maxLen;
    }
};

int main() {
    HotTopicTracker tracker(5);
    tracker.insertTag("#AI");
    tracker.insertTag("#Tech");
    tracker.insertTag("#Coding");
    tracker.insertTag("#DataStructures");
    tracker.insertTag("#Hashing");
    tracker.insertTag("#CPlusPlus");
    tracker.insertTag("#Algorithms");
    tracker.insertTag("#AI");

    cout << "Count for #AI: " << tracker.searchTag("#AI") << endl;
    tracker.removeTag("#Tech");
    return 0;
}
