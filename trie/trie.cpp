#include <iostream>
#include <vector>
using namespace std;

class TrieNode {
public:
    vector<TrieNode*> children;
    bool is_end;

    TrieNode() : children(26, nullptr), is_end(false) {}

    bool contains_key(char ch) {
        return children[ch - 'a'] != nullptr;
    }

    TrieNode* get(char ch) {
        return children[ch - 'a'];
    }

    void put(char ch, TrieNode* node) {
        children[ch - 'a'] = node;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->contains_key(ch)) {
                node->put(ch, new TrieNode());
            }
            node = node->get(ch);
        }
        node->is_end = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->contains_key(ch)) {
                node = node->get(ch);
            } else {
                return false;
            }
        }
        return node != nullptr && node->is_end;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->contains_key(ch)) {
                node = node->get(ch);
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Trie trie;

    // Test case 1: Inserting words and searching for them
    vector<string> words_to_insert = {"apple", "banana", "car", "cat", "dog", "doggo"};
    for (string word : words_to_insert) {
        trie.insert(word);
    }

    // Search for inserted words
    assert(trie.search("apple") == true);
    assert(trie.search("banana") == true);
    assert(trie.search("car") == true);
    assert(trie.search("cat") == true);
    assert(trie.search("dog") == true);
    assert(trie.search("doggo") == true);

    // Test case 2: Searching for words that are not in the Trie
    assert(trie.search("applepie") == false);
    assert(trie.search("bananarama") == false);
    assert(trie.search("dogs") == false);
    assert(trie.search("dogg") == false);

    // Test case 3: Searching for words that are prefixes of inserted words
    assert(trie.startsWith("app") == true);
    assert(trie.startsWith("ban") == true);
    assert(trie.startsWith("do") == true);

    // Test case 4: Searching for prefixes that are not in the Trie
    assert(trie.startsWith("appr") == false);
    assert(trie.startsWith("bano") == false);
    assert(trie.startsWith("da") == false);

    cout << "All test cases passed!" << endl;

    return 0;
}
