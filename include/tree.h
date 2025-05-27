// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char val);
};

class PMTree {
 public:
    explicit PMTree(const std::vector<char>& items);
    ~PMTree();
    Node* getRoot();
    int getSize() const;

 private:
    Node* root;
    int totalPerms;
    void build(Node* node, std::vector<char> items);
    void clear(Node* node);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
