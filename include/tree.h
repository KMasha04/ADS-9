// Copyright 2022 NNTU-CS
#ifndef ALG_H
#define ALG_H

#include <vector>

class Node {
public:
    char value;
    std::vector<Node*> children;

    explicit Node(char val);
};

class PMTree {
public:
    PMTree(const std::vector<char>& items);
    ~PMTree();

    Node* getRoot();
    int getSize() const;
    void resetRoot();

private:
    Node* root;
    int totalPerms;

    void build(Node* node, std::vector<char> items);
    void clear(Node* node);
};


std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif // ALG_H
