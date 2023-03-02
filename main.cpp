#include <iostream>
#include "AVLTree.h"

int main()
{
    AVLTree<int> t;
    for (int i = 1; i < 6; ++i) t.insert(i);
    for (int i = 10; i > 4; --i) t.insert(i);

    t.inorder();
    cout << "t.root-val: " << t.root->val << "\n";
    cout << "Tree height: " << t.root->height << "\n";

    t.remove(1);
    t.inorder();
    cout << "t.root-val: " << t.root->val << "\n";
    cout << "Tree height: " << t.root->height << "\n";

    t.remove(5);
    cout << "t.root-val: " << t.root->val << "\n";
    cout << "Tree height: " << t.root->height << "\n"; 

    t.remove(3);
    cout << "t.root-val: " << t.root->val << "\n";
    cout << "Tree height: " << t.root->height << "\n";       
    return 0;
}