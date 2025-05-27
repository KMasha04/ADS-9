// Copyright 2022 NNTU-CS
#include <algorithm>
#include <vector>
#include "tree.h"
Node::Node(char val) : value(val) {}
PMTree::PMTree(const std::vector<char>& items) : root(nullptr), totalPerms(1) {
    for (size_t i = 2; i <= items.size(); ++i)
        totalPerms *= i;
    root = new Node(0);
    build(root, items);
}
PMTree::~PMTree() {
    clear(root);
}
void PMTree::clear(Node* node) {
    for (Node* child : node->children)
        clear(child);
    delete node;
}

void PMTree::build(Node* node, std::vector<char> items) {
    std::sort(items.begin(), items.end());
    for (size_t i = 0; i < items.size(); ++i) {
        Node* child = new Node(items[i]);
        node->children.push_back(child);
        std::vector<char> rest = items;
        rest.erase(rest.begin() + i);
        build(child, rest);
    }
}

Node* PMTree::getRoot() {
    return root;
}

int PMTree::getSize() const {
    return totalPerms;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collect(tree.getRoot(), path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(all.size()))
        return {};
    return all[num - 1];
}
static std::vector<char> findPerm(Node* node, int& count) {
    if (!node)
        return {};
    std::vector<char> path;
    if (node->value != 0)
        path.push_back(node->value);
    if (node->children.empty()) {
        if (--count == 0)
            return path;
        return {};
    }
    for (auto* child : node->children) {
        auto sub = findPerm(child, count);
        if (!sub.empty()) {
            path.insert(path.end(), sub.begin(), sub.end());
            return path;
        }
    }
    return {};
}
std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num < 1 || num > tree.getSize())
        return {};
    int counter = num;
    return findPerm(tree.getRoot(), counter);
}
