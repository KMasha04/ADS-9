// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "tree.h"

static int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<char> sample = {'1', '2', '3'};
    PMTree tree(sample);
    std::cout << "All permutations:\n";
    auto perms = getAllPerms(tree);
    for (const auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << "\n";
    }
    for (int n = 3; n <= 8; ++n) {
        std::vector<char> alphabet(n);
        for (int i = 0; i < n; ++i)
            alphabet[i] = '1' + i;
        PMTree tree(alphabet);
        int total = factorial(n);
        int num = rand() % total + 1; // NOLINT
        auto start = std::chrono::high_resolution_clock::now();
        auto all = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double t1 = std::chrono::duration<double>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        getPerm1(tree, num);
        end = std::chrono::high_resolution_clock::now();
        double t2 = std::chrono::duration<double>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        getPerm2(tree, num);
        end = std::chrono::high_resolution_clock::now();
        double t3 = std::chrono::duration<double>(end - start).count();
        std::cout << "n=" << n << " getAllPerms: " << t1 << "s "
                  << "getPerm1: " << t2 << "s "
                  << "getPerm2: " << t3 << "s\n";
    }
    return 0;
}
