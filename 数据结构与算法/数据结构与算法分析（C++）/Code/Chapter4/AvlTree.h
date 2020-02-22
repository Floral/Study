#ifndef AVL_TREE
#define AVL_TREE

#include<utility>

template<typename T>
class AvlTree
{
private:
    struct AvlNode;
    AvlNode* root;

    static const int ALLOWED_IMBALANCE = 1;

    int height(AvlNode* t) const;   //返回节点的高度
    void insert(const T& x, AvlNode*& t);
    void insert(T&& x, AvlNode*& t);
    void remove(const T& x, AvlNode*& t);
    AvlNode* findMin(AvlNode* t) const;
    AvlNode* findMax(AvlNode* t) const;

    void balance(AvlNode*& t);
    void rotateWithLeftChild(AvlNode*& t);
    void doubleWithLeftChild(AvlNode*& t);
    void rotateWithRightChild(AvlNode*& t);
    void doubleWithRightChild(AvlNode*& t);

    AvlNode* clone(AvlNode* t) const;
    void makeEmpty(AvlNode*& root);
public:
    AvlTree():root{nullptr} {};
    AvlTree(const AvlTree& rhs):root{} { root = clone(rhs.root); }
    AvlTree(AvlTree&& rhs):root{std::move(rhs.root)} {}
    ~AvlTree() { makeEmpty(root); }
    
    void insert(const T& x)
    { insert(x, root); }
    
    void insert(T&& x)
    { insert(std::move(x), root); }

    void remove(const T& x)
    { remove(x, root); }

    AvlNode* findMin() const
    { findMin(root); }

    AvlNode* findMax() const
    { findMax(root); }

};

template<typename T>
struct AvlTree<T>::AvlNode
{
    T element;
    AvlNode* left;
    AvlNode* right;
    int height;

    AvlNode(const T& ele, AvlNode* lt, AvlNode* rt, int h = 0)
    :element{ele}, left{lt}, right{rt}, height{h} {}

    AvlNode(T&& ele, AvlNode* lt, AvlNode* rt, int h = 0)
    :element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
};

template<typename T>
int AvlTree<T>::height(AvlNode* t) const
{
    return t == nullptr ? -1 : t->height;
}

template<typename T>
void AvlTree<T>::insert(const T& x, AvlNode*& t)
{
    if (t == nullptr)
        t = new AvlNode(x, nullptr, nullptr);
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);

    balance(t);
}

template<typename T>
void AvlTree<T>::insert(T&& x, AvlNode*& t)
{
    if (t == nullptr)
        t = new AvlNode(std::move(x), nullptr, nullptr);
    else if (x < t->element)
        insert(std::move(x), t->left);
    else if (t->element < x)
        insert(std::move(x), t->right);

    balance(t);
}

template<typename T>
void AvlTree<T>::balance(AvlNode*& t)
{
    if (t == nullptr)
        return;
    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE )
    {
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }
    else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
    {
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else 
            doubleWithRightChild(t);
    }
    
    t->height = max(height(t->left), height(t->right)) + 1;
}
        /*
                k2                  k1
              /  \                /  \
            k1   Z     --->      X   k2
          /  \                     /  \
        X    Y                   Y    Z
        */

template<typename T>    //单旋转
void AvlTree<T>::rotateWithLeftChild(AvlNode*& k2)
{
    AvlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template<typename T>        //双旋转
void AvlTree<T>::doubleWithLeftChild(AvlNode*& k3)
{
    //以下是一种直接看图的出来的方法
    AvlNode* k1 = k3->left;
    AvlNode* k2 = k1->right;
    k1->right = k2->left;
    k3->left = k2->right;
    k2->left = k1;
    k2->right = k3;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k3->height = max(height(k3->left), height(k3->right)) + 1;
    k2->height = max(k1->height, k2->height) + 1;
    k3 = k2;

    //以下是更清晰的一种方法
    // rotateWithRightChild(k3->left);
    // rotateWithLeftChild(k3);
}

        /*
               k1                 k2
              / \                /  \
             X  k2     --->    k1   Z
               /  \          /  \
              Y   Z         X   Y 
        */

template<typename T>
void AvlTree<T>::rotateWithRightChild(AvlNode*& k1)
{
    AvlNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

template<typename T>
void AvlTree<T>::doubleWithRightChild(AvlNode*& k1)
{
    //以下是一种直接看图的出来的方法
    AvlNode* k3 = k1->right;
    AvlNode* k2 = k3->left;
    k3->left = k2->right;
    k1->right = k2->left;
    k2->left = k1;
    k2->right = k3;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k3->height = max(height(k3->left), height(k3->right)) + 1;
    k2->height = max(k1->height, k2->height) + 1;
    k3 = k2;

    //以下是更清晰的一种方法
    // rotateWithLeftChild(k1->left);
    // rotateWithRightChild(k1);
}

template<typename T>
void AvlTree<T>::remove(const T& x, AvlNode* &t)
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
        AvlNode* old = t;
        t = (t->left != nullptr) ? t->left : t->right;      //若只有一个子节点，则直接用其代替,没有子节点逻辑也是ok的
        delete old;
    }

    balance(t);
}

#endif