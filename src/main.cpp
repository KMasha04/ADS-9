// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int main() {
    vector<int> sizes = {3, 4, 5, 6, 7, 8};
    for (int n : sizes) {
        vector<char> elements(n);
        for (int i = 0; i < n; ++i)
            elements[i] = '1' + i;

        PMTree tree(elements);
        auto start = chrono::high_resolution_clock::now();
        auto perms = getAllPerms(tree);
        auto end = chrono::high_resolution_clock::now();
        auto duration_all = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        mt19937 rng(random_device{}());
        uniform_int_distribution<int> dist(1, factorial(n));

        start = chrono::high_resolution_clock::now();
        getPerm1(tree, dist(rng));
        end = chrono::high_resolution_clock::now();
        auto duration_perm1 = chrono::duration_cast<chrono::microseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        getPerm2(tree, dist(rng));
        end = chrono::high_resolution_clock::now();
        auto duration_perm2 = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << "n=" << n << " getAllPerms: " << duration_all << "ms, "
             << "getPerm1: " << duration_perm1 << "us, "
             << "getPerm2: " << duration_perm2 << "us" << endl;
    }
    return 0;
}
