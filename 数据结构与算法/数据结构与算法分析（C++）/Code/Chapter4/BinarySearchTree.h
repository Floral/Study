#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE


#include<iostream>
#include<utility>

using std::ostream;
using std::cout;

template<typename Comparable>
class BinarySearchTree
{
private:
    struct BinaryNode;

    BinaryNode* root;

    void insert(const Comparable& x, BinaryNode* &t);
    void insert(Comparable&& x, BinaryNode* &t);
    void remove(const Comparable& x, BinaryNode* &t);
    BinaryNode* findMin(BinaryNode* t) const;
    BinaryNode* findMax(BinaryNode* t) const;
    bool contains(const Comparable& x, BinaryNode* t) const;
    void makeEmpty(BinaryNode* &t);
    void printTree(BinaryNode *t, ostream &out) const;
    BinaryNode* clone(BinaryNode *t) const;     //clone（子）树，而不是单单一个节点

public:
    BinarySearchTree():root{nullptr} {};
    BinarySearchTree(const BinarySearchTree& rhs):root{nullptr} 
    { root = clone(rhs.root); }
    BinarySearchTree(BinarySearchTree&& rhs):root{std::move(rhs.root)} {};
    ~BinarySearchTree() { makeEmpty(); };

    const Comparable& findMin() const
    { findMin(root)->element; }

    const Comparable& findMax() const
    { findMax(root)->element; }

    bool contains(const Comparable& x) const
    { return contains(x, root); }

    bool isEmpty() const
    {
        if (root == nullptr)
            return true;
        else
            return false;
    }
    
    void printTree(ostream& out = cout) const
    {   printTree(root, out);   }

    void makeEmpty()
    {   makeEmpty(root);  }

    void insert(const Comparable& x)
    {   insert(x,root); }

    void insert(Comparable&& x)
    {   insert(std::move(x),root);  }

    void remove(const Comparable& x)
    {   remove(x, root);    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs);
    BinarySearchTree& operator=(BinarySearchTree&& rhs);
};


template<typename Comparable>
struct BinarySearchTree<Comparable>::BinaryNode
{
    Comparable element;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
    : element{theElement}, left{lt}, right{rt} {}

    BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt)
    : element{std::move(theElement)}, left{lt}, right{rt} {}
};

template<typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree& rhs)
{
    BinarySearchTree copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template<typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(BinarySearchTree&& rhs)
{
    std::swap(*this.root, rhs.root);
    return *this;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode* &t)
{
    if (t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;   //重复的元素，暂时什么也不做
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable&& x, BinaryNode* &t)
{
    if (t == nullptr)
        t = new BinaryNode(std::move(x), nullptr, nullptr);
    else if (x < t->element)
        insert(std::move(x), t->left);
    else if (t->element < x)
        insert(std::move(x), t->right);
    else
        ;   //同上
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode* &t)
{
    if (t == nullptr)
        return ;

    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x,t->right);
    else if (t->left != nullptr && t->right != nullptr) //要删除的节点有两个子节点
    {
        t->element = findMin(t->right)->element;    //用其右子树的最小值代替他的位置
        remove(t->element, t->right);   //递归删掉右子树的最小值
    }
    else
    {
        BinaryNode* old = t;
        t = (t->left != nullptr) ? t->left : t->right;      //若只有一个子节点，则直接用其代替
        delete old;
    }
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMin(BinaryNode* t) const
{
    if (t == nullptr)
        return  nullptr;
    if (t->left == nullptr)
        return t;
    else
        return findMin(t->left);

    //以下是非递归实现
    // if (t == nullptr)
    //     return nullptr;
    // else
    // {
    //     while (t->left != nullptr)
    //         t = t->left;
    //     return t;
    // }
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMax(BinaryNode* t) const
{
    if (t == nullptr)
        return  nullptr;
    if (t->right == nullptr)
        return t;
    else
        return findMax(t->right);

    //以下是非递归实现
    // if (t == nullptr)
    //     return nullptr;
    // else
    // {
    //     while (t->right != nullptr)
    //         t = t->right;
    //     return t;
    // }
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& x, BinaryNode* t) const
{
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element< x)
        return contains(x, t->right);
    else
        return true;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode* &t)
{
    if (t == nullptr)
        return ;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    t = nullptr;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode* t, ostream& out) const
{
    if (t == nullptr)
        return ;
}

template<typename Comparable>   //clone整个树t
typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::clone(BinaryNode* t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

#endif