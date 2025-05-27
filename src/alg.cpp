// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <vector>

static void collect(Node* node, std::vector<char>& path, 
                   std::vector<std::vector<char>>& out) {
    if (node->value != 0) 
        path.push_back(node->value);
    
    if (node->children.empty()) {
        if (!path.empty()) 
            out.push_back(path);
    } else {
        for (auto* child : node->children) 
            collect(child, path, out);
    }
    
    if (node->value != 0) 
        path.pop_back();
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
