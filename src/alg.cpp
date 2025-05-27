// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <vector>

using namespace std;

void traverse(const PMTree::Node* node, vector<char>& current, vector<vector<char>>& result) {
    current.push_back(node->value);
    if (node->children.empty())
        result.push_back(current);
    else
        for (const PMTree::Node* child : node->children)
            traverse(child, current, result);
    current.pop_back();
}

vector<vector<char>> getAllPerms(const PMTree& tree) {
    vector<vector<char>> result;
    vector<char> current;
    for (const PMTree::Node* child : tree.getRoot()->children)
        traverse(child, current, result);
    return result;
}
vector<char> getPerm1(const PMTree& tree, int num) {
    vector<vector<char>> all = getAllPerms(tree);
    if (num < 1 || num > all.size()) return {};
    return all[num - 1];
}

long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

vector<char> getPerm2(const PMTree& tree, int num) {
    const PMTree::Node* root = tree.getRoot();
    int n = root->children.size();
    if (num < 1 || num > factorial(n)) return {};

    vector<long long> facts(n + 1, 1);
    for (int i = 2; i <= n; ++i)
        facts[i] = facts[i - 1] * i;

    long long current_num = num - 1;
    const PMTree::Node* current = root;
    vector<char> result;

    for (int step = 0; step < n; ++step) {
        int remaining = n - step - 1;
        long long fact = facts[remaining];
        const auto& children = current->children;
        long long index = current_num / fact;

        if (index >= children.size()) return {};
        result.push_back(children[index]->value);
        current_num %= fact;
        current = children[index];
    }

    return result;
}
