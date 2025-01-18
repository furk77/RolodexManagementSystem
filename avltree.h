#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include <algorithm>

struct AVLNode {
    std::string key;
    size_t index;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const std::string& k, size_t i)
        : key(k), index(i), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* balance(AVLNode* node) {
        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balance < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, const std::string& key, size_t index) {
        if (!node) return new AVLNode(key, index);

        if (key < node->key) {
            node->left = insert(node->left, key, index);
        } else if (key > node->key) {
            node->right = insert(node->right, key, index);
        } else {
            return node; // Duplicate keys are not allowed
        }

        return balance(node);
    }

    void inorder(AVLNode* node, std::vector<size_t>& indices) const {
        if (node) {
            inorder(node->left, indices);
            indices.push_back(node->index);
            inorder(node->right, indices);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const std::string& key, size_t index) {
        root = insert(root, key, index);
    }

    std::vector<size_t> getSortedIndices() const {
        std::vector<size_t> indices;
        inorder(root, indices);
        return indices;
    }
};

#endif
