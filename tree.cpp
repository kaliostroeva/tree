#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    vector<TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : children(26), isEndOfWord(false) {}
};

void insert(TrieNode* root, string word) {
    TrieNode* node = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (!node->children[index])
            node->children[index] = new TrieNode();
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

void search(TrieNode* node, string word, vector<string>& suggestions) {
    if (node->isEndOfWord)
        suggestions.push_back(word);
    for (int i = 0; i < 26; i++) {
        if (node->children[i])
            search(node->children[i], word + char(i + 'a'), suggestions);
    }
}

vector<string> autocomplete(TrieNode* root, string prefix) {
    vector<string> suggestions;
    TrieNode* node = root;
    for (char ch : prefix) {
        int index = ch - 'a';
        if (!node->children[index])
            return suggestions;
        node = node->children[index];
    }
    search(node, prefix, suggestions);
    return suggestions;
}

int main() {
    vector<string> dictionary = { "apple", "banana", "cherry", "grape", "lemon", "orange", "peach", "pear" };
    TrieNode* root = new TrieNode();
    for (string word : dictionary)
        insert(root, word);

    string input;
    while (true) {
        cout << "Enter a prefix: ";
        cin >> input;
        vector<string> suggestions = autocomplete(root, input);
        cout << "Suggestions: ";
        for (string suggestion : suggestions)
            cout << suggestion << " ";
        cout << endl;
    }

    return 0;
}
