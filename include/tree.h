// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <iostream>

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
        root = nullptr;
        totalPerms = 0;
    }

 private:
    Node* root;
    int totalPerms;

    void build(Node* node, std::vector<char> items) {
        if (items.empty()) {
            ++totalPerms;
            return;
        }

        for (size_t i = 0; i < items.size(); ++i) {
            char c = items[i];
            Node* child = new Node(c);
            node->children.push_back(child);

            std::vector<char> remaining = items;
            remaining.erase(remaining.begin() + i);
            build(child, remaining);
        }
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
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
