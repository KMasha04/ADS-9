// Copyright 2022 NNTU-CS
#include <iostream>
#include "tree.h"
#include  <vector>

int main() {
    std::vector<char> items = {'a', 'b', 'c'};
    PMTree tree(items);

    std::cout << "Total permutations: " << tree.getSize() << "\n\n";

    std::cout << "All permutations:\n";
    auto all = getAllPerms(tree);
    for (const auto& perm : all) {
        for (char c : perm) std::cout << c;
        std::cout << '\n';
    }

    std::cout << "\nPerm1 (index 2): ";
    for (char c : getPerm1(tree, 2)) std::cout << c;
    std::cout << '\n';

    std::cout << "Perm2 (index 4): ";
    for (char c : getPerm2(tree, 4)) std::cout << c;
    std::cout << '\n';

    return 0;
}
