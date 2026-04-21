#include <iostream>
#include <string>

using namespace std;


class Trie {
    class TrieNode {
    public:
        TrieNode* children[26];
        bool isEnd;
        TrieNode() : isEnd(false) {
            for(int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* cur = root;
        for(char c : word) {
            TrieNode* node = cur->children[c - 'a'];
            if(node != nullptr) {
                cur = node;
            } else {
                cur->children[c - 'a'] = new TrieNode();
                cur = cur->children[c - 'a'];
            }
        }
        cur->isEnd = true;
    }

    TrieNode* walkPath(string& path) {
        TrieNode* cur = root;
        for(char c : path) {
            if((cur = cur->children[c - 'a']) == nullptr)
                return nullptr;
        }
        return cur;
    }

    bool search(string word) {
        TrieNode* node = walkPath(word);
        return node == nullptr ? false : node->isEnd; 
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = walkPath(prefix);
        return node != nullptr;
    }
};


