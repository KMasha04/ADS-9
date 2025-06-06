// Copyright 2022 NNTU-CS
#include "alg.h"        
#include <cstdlib>      
#include <iostream>     
#include <vector>
#include <string>       

Node::Node(char val) : value(val) {}

PMTree::PMTree(const std::vector<char>& items) {
    totalPerms = 0;
    root = new Node('\0');
    build(root, items);
}

PMTree::~PMTree() {
    clear(root);
}

Node* PMTree::getRoot() {
    return root;
}

int PMTree::getSize() const {
    return totalPerms;
}

void PMTree::resetRoot() {
    clear(root);
    root = nullptr;
    totalPerms = 0;
}

void PMTree::build(Node* node, std::vector<char> items) {
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

void PMTree::clear(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        clear(child);
    }
    delete node;
}

void collect(Node* node, std::vector<char>& path,
std::vector<std::vector<char>>& result) {
    if (node->value != '\0') {
        path.push_back(node->value);
    }

    if (node->children.empty()) {
        result.push_back(path);
    } else {
        for (Node* child : node->children) {
            collect(child, path, result);
        }
    }

    if (!path.empty()) {
        path.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collect(tree.getRoot(), path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    if (num >= 0 && num < static_cast<int>(all.size())) {
        return all[num];
    }
    return {};
}

bool getByIndex(Node* node, int& index, int target,
                std::vector<char>& path, std::vector<char>& result) {
    if (node->value != '\0') {
        path.push_back(node->value);
    }

    if (node->children.empty()) {
        if (index == target) {
            result = path;
            return true;
        }
        index++;
    } else {
        for (Node* child : node->children) {
            if (getByIndex(child, index, target, path, result)) {
                return true;
            }
        }
    }

    if (!path.empty()) {
        path.pop_back();
    }
    return false;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result, path;
    int index = 0;
    getByIndex(tree.getRoot(), index, num, path, result);
    return result;
}
