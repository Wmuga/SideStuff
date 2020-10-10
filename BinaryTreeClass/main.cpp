#include <iostream>
#include "binary_tree.h"

void show(binary_tree<int>& tree,binary_tree<int>::leaf _leaf)
{
    if (tree.goto_left(_leaf).second) show(tree,tree.goto_left(_leaf).first);
    std::cout << tree.get_value(_leaf) << " ";
    if (tree.goto_right(_leaf).second) show(tree,tree.goto_right(_leaf).first);
}

int main() {
    binary_tree<int> test;
    binary_tree<int>::leaf _leaf = test.goto_head();
    test.insert_c(_leaf,5);
    test.insert_l(_leaf,1);
    test.insert_r(_leaf,9);
    show(test,test.goto_head());
    return 0;
}
