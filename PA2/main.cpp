#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "AVLTree.h"

int main() {
    int ascendingOrder[50], descendingOrder[50], randomOrder[50];
    int j =1;
    for(int i = 0; i < 50; i++){
        ascendingOrder[i] = j;
        randomOrder[i] = j;
        descendingOrder[49-i] = j;
        j+=2;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(randomOrder, randomOrder + 49, std::default_random_engine(seed));

    auto* AscendingTree = new AVLTree<int>;
    auto* DescendingTree = new AVLTree<int>;
    auto* RandomTree = new AVLTree<int>;

    for(int i = 0; i < 50; i++){
        AscendingTree->insert(ascendingOrder[i]);
        DescendingTree->insert(descendingOrder[i]);
        RandomTree->insert(randomOrder[i]);
    }
    std::cout << "Height of Trees\n";
    std::cout << "\tAscending Tree: " << AscendingTree->height() << std::endl;
    std::cout << "\tDescending Tree: " << DescendingTree->height() << std::endl;
    std::cout << "\tRandom Tree: " << RandomTree->height() << std::endl << std::endl;
    std::cout << "validate() results\n";
    std::cout << "\tAscending Tree: " << AscendingTree->validate() << std::endl;
    std::cout << "\tDescending Tree: " << DescendingTree->validate() << std::endl;
    std::cout << "\tRandom Tree: " << RandomTree->validate() << std::endl << std::endl;
    std::cout << "Ascending Tree:    Descending Tree:     Random Tree:" << std::endl;
    bool failed = false;
    for(int i = 1; i <= 100; i++){
        int a = AscendingTree->contains(i);
        int d = DescendingTree->contains(i);
        int r = RandomTree->contains(i);
        if (i % 2 != (a && d && r)) failed = true;
        std::cout << a << "                  " << d << "                    " << r << std::endl;
    }
    if (failed) std::cout << "My AVL tree implementation is wrong\n";

    return 0;
}
