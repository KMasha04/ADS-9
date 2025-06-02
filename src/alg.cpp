// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include  <vector>

void collect(Node* node, std::vector<char>&
 path, std::vector<std::vector<char>>& result) {
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
    if (num >= 0 && num < all.size()) {
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
