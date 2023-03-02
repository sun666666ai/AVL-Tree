#ifndef AVLTREE
#define AVLTREE
#include <iostream>
using std::cout;

template<typename T>
class AVLTree
{
public:
    struct AVLNode
    {
        int height;
        AVLNode *left, *right;
        T val;
        AVLNode() {}
        AVLNode(T v): height(1), left(nullptr), right(nullptr), val(v) {} 
    };

    AVLNode *root = nullptr;
    AVLTree(AVLNode *u = nullptr): root(u) {}

    AVLNode* search(T v) { return _search(root, v); }
    void insert(T v) { root = _insert(root, v); }
    void remove(T v) { root = _remove(root, v); }
    void inorder() 
    { 
        _inorder(root);
        cout << '\n';
    }

private:
    AVLNode* _search(AVLNode *n, T v)
    {
        if (n == nullptr || n->val == v) return n;
        else if (v < n->val) return _search(n->left, v);
        else return _search(n->right, v);
    }
    
    AVLNode* leftRotate(AVLNode* n)
    {
        AVLNode* nr = n->right;
        n->right = nr->left;
        nr->left = n;

        if (n->left == nullptr && n->right == nullptr) n->height = 1;
        else if (n->left == nullptr) n->height = n->right->height + 1;
        else if (n->right == nullptr) n->height = n->left->height + 1;
        else n->height = std::max(n->left->height, n->right->height) + 1;

        if (nr->right == nullptr) nr->height = n->height + 1;
        else nr->height = std::max(n->height, nr->right->height) + 1;

        return nr;
    }

    AVLNode* rightRotate(AVLNode* n)
    {
        AVLNode* nr = n->left;
        n->left = nr->right;
        nr->right = n;

        if (n->left == nullptr && n->right == nullptr) n->height = 1;
        else if (n->left == nullptr) n->height = n->right->height + 1;
        else if (n->right == nullptr) n->height = n->left->height + 1;
        else n->height = std::max(n->left->height, n->right->height) + 1;

        if (nr->left == nullptr) nr->height = n->height + 1;
        else nr->height = std::max(n->height, nr->left->height) + 1;

        return nr;
    }

    AVLNode* _insert(AVLNode* n, T v)
    {
        if (n == nullptr)
        {
            n = new AVLNode(v);
            return n;
        }
        if (v > n->val) n->right = _insert(n->right, v);
        if (v < n->val) n->left = _insert(n->left, v);

        int lh = n->left ? n->left->height : 0;
        int rh = n->right ? n->right->height : 0;
        n->height = std::max(lh, rh) + 1;
        if (lh > rh + 1)
        {
            if (v > n->left->val) n->left = leftRotate(n->left);
            n = rightRotate(n);
        }
        if (rh > lh + 1)
        {
            if (v < n->right->val) n->right = rightRotate(n->right);
            n = leftRotate(n);
        }

        return n;
    }

    AVLNode* _remove(AVLNode *n, T v)
    {
        if (n == nullptr) return n;
        if (v < n->val) n->left = _remove(n->left, v);
        else if (v > n->val) n->right = _remove(n->right, v);
        else
        {
            if (n->right == nullptr) 
            {
                AVLNode* t = n;
                n = n->left;
                delete t;
                return n;
            }
            else if (n->left == nullptr) 
            {
                AVLNode* t = n;
                n = n->right;
                delete t;
                return n;
            }
            else
            {
                AVLNode *t = n->right;
                while (t->left) t = t->left;
                n->val = t->val;
                n->right = _remove(n->right, t->val);
            }
        }
        
        int lh = n->left ? n->left->height : 0;
        int rh = n->right ? n->right->height : 0;
        n->height = std::max(lh, rh) + 1;
        if (lh > rh + 1)
        {
            int llh = n->left->left ? n->left->left->height : 0;
            int lrh = n->left->right ? n->left->right->height : 0;
            if (lrh > llh) n->left = leftRotate(n->left);
            n = rightRotate(n);
        }
        if (rh > lh + 1)
        {
            int rlh = n->right->left ? n->right->left->height : 0;
            int rrh = n->right->right ? n->right->right->height : 0;
            if (rlh > rrh) n->right = rightRotate(n->right);
            n = leftRotate(n);
        }

        return n;
    }

    void _inorder(AVLNode *n)
    {
        if (n == nullptr) return;
        _inorder(n->left);
        cout << n->val << " ";
        _inorder(n->right);
    }

};
#endif