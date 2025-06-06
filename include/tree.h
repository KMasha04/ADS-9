// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <iostream>
#include <algorithm>

struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char val) : value(val) {}
};

class PMTree {
 public:
    explicit PMTree(const std::vector<char>& items) {
        totalPerms = 0;
        root = new Node('\0');
        build(root, items);
    }

    ~PMTree() {
        clear(root);
    }

    Node* getRoot() {
        return root;
    }

    int getSize() const {
        return totalPerms;
    }

    void resetRoot() {
        clear(root);
        root = new Node('\0');
        totalPerms = 0;
    }

 private:
    Node* root;
    int totalPerms;

    void build(Node* node, std::vector<char> items) {
    std::sort(items.begin(), items.end());
    do {
        Node* current = node;
        for (char c : items) {
            Node* child = new Node(c);
            current->children.push_back(child);
            current = child;
        }
        ++totalPerms;
    } while (std::next_permutation(items.begin(), items.end()));
    }
    void clear(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            clear(child);
        }
        delete node;
    }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
auto all = getAllPerms(tree);
    if (num >= 0 && num < static_cast<int>(all.size())) {
        return all[num];
    }
    return {};
}
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
