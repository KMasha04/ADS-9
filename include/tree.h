// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

class PMTree {
 public:
    struct Node {
        char value;
        std::vector<Node*> children;
        Node(char v) : value(v) {}
        ~Node() {
            for (Node* child : children)
                delete child;
        }
    };

    PMTree(const std::vector<char>& elements) {
        root = new Node('\0');
        buildTree(root, elements);
    }
    ~PMTree() { delete root; }
    const Node* getRoot() const { return root; }

 private:
    Node* root;

    void buildTree(Node* node, std::vector<char> elements) {
        if (elements.empty()) return;
        std::sort(elements.begin(), elements.end());
        for (char c : elements) {
            Node* child = new Node(c);
            node->children.push_back(child);
            std::vector<char> remaining;
            for (char ch : elements)
                if (ch != c) remaining.push_back(ch);
            buildTree(child, remaining);
        }
    }
};
#endif  // INCLUDE_TREE_H_
