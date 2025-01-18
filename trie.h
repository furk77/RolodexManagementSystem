#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    std::vector<size_t> entryIndices; // Store indices of entries in the Rolodex

    ~TrieNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() : root(new TrieNode()) {}

    ~Trie() {
        delete root;
    }

    void insert(const std::string& key, size_t index) {
        TrieNode* node = root;
        for (char ch : key) {
            if (!node->children.count(ch)) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->entryIndices.push_back(index);
    }

    std::vector<size_t> search(const std::string& key) const {
        TrieNode* node = root;
        for (char ch : key) {
            if (!node->children.count(ch)) {
                return {};
            }
            node = node->children[ch];
        }
        return node->entryIndices;
    }
};

#endif
