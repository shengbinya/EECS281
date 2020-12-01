//Assignment Identifier: EAA16B5C3724FBFD78F132136AABBBBA4952E261


// LAB 8: Ro-Tater Tots
// Tree Tester File

#include "avl_lab.h"

int main() {

    AVL increasing_tree;
    AVL decreasing_tree;
    AVL randomish_tree;
    for (int i = 0; i < 10; i++) {
        increasing_tree.insert(i);
        decreasing_tree.insert(10 - i);
    }
    //
    std::vector<int> example = { 1, 19, 2, 4, 7, 3, 28, 30, 18, 13, 10, 64, 65, 66, 67, 70, 68, 69, 50, 43, 60 };
    for (int v : example) {
        randomish_tree.insert(v);
        randomish_tree.print_diagram();
    }
    std::cout << "test tree (increasing_tree)" << std::endl;
    increasing_tree.print_diagram();
    // should look like:
    //test tree (increasing_tree) //
    //     - 3-----               //
    //    /        \              //
    //   1         - 7            //
    //  / \       /   \           //
    // 0   2     5     8          //
    //          / \     \         //
    //         4   6     9        //

    std::cout << std::endl;

    std::cout << "test tree (decreasing_tree)" << std::endl;
    decreasing_tree.print_diagram();
    // should look like:
    // test tree (decreasing_tree) //
    //       ----- 7-              //
    //      /        \             //
    //     3-          9           //
    //    /  \        / \          //
    //   2     5     8  10         //
    //  /     / \                  //
    // 1     4   6                 //

    std::cout << std::endl;

    std::cout << "test tree (randomish_tree)" << std::endl;
    randomish_tree.print_diagram();
    // should look like:
    // test tree (randomish_tree)                 //
    //               -----30-------               //
    //              /              \              //
    //         ---13-            ---65-           //
    //        /      \          /      \          //
    //     - 4        19      50-       67-       //
    //    /   \       / \     /  \      /  \      //
    //   2     7    18  28  43    64  66    69    //
    //  / \     \                 /         / \   //
    // 1   3    10              60        68  70  //
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "SUBMISSION RESULTS:" << std::endl;
    //
    // actual part you need to submit for:
    AVL bigtree;
    for (int i = 0; i < 2000; i++) {
        // producing magic numbers
        unsigned int x = (unsigned int)i;
        // borrowed from http://stackoverflow.com/a/12996028/409054
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        bigtree.insert(x % 2017);
    }

    // search string ends with 'X' if found, 'M' if missing

    std::cout << "search for 201:" << std::endl;
    bigtree.search(201, true); // should be LLLRLLRLRX
    std::cout << "search for 745:" << std::endl;
    bigtree.search(745, true); // should be LRLLLLRLLX
    std::cout << "search for 1983:" << std::endl;
    bigtree.search(1983, true); // should be RRRRRX
    std::cout << "search for 2017:" << std::endl;
    bigtree.search(2017, true); // should be RRRRRRRRRRRM

}