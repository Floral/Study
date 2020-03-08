#ifndef LEFT_IST_HEAP
#define LEFT_IST_HEAP

#include<iostream>
#include<utility>
#include<exception>

template<typename T>
class LeftistHeap
{
private:
    /* data */
    struct LeftistNode;
    
    LeftistNode* root;
    LeftistNode* merge(LeftistNode* h1, LeftistNode* h2);
    LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2);

    void swapChildren(LeftistNode* t);
    void reclaimMemory(LeftistNode* t);
    LeftistNode* clone(LeftistNode* t) const;


public:
    LeftistHeap();
    LeftistHeap(const LeftistHeap& rhs);
    LeftistHeap(LeftistHeap&& rhs);

    ~LeftistHeap();

    LeftistNode& operator=(const  LeftistNode& rhs);
    LeftistNode& operator=(LeftistNode&& rhs);

    bool isEmpty() const;
    const T& findMin() const;
    void insert(const T& x);
    void insert(T&& x);
    void deleteMin();
    void deleteMin(T& minItem);
    void makeEmpty();
    void merge(LeftistHeap& rhs);

};

template<typename T>
struct LeftistHeap<T>::LeftistNode
{
    T element;
    LeftistNode* left;
    LeftistNode* right;
    int  npl;

    LeftistNode(const T& e, LeftistHeap* lt = nullptr, LeftistNode* rt = nullptr, int np = 0)
    :element{e}, left{lt}, right{rt}, npl{np} {}

    LeftistNode(T&& e, LeftistHeap* lt = nullptr, LeftistNode* rt = nullptr, int np = 0)
    :element{std::move(e)}, left{lt}, right{rt}, npl{np} {}
};


template<typename T>
LeftistHeap<T>::LeftistHeap():root{nullptr}
{}
template<typename T>
LeftistHeap<T>::LeftistHeap(const LeftistHeap& rhs):root{nullptr}
{
    LeftistNode* copy = rhs.root;
    std::swap(root, copy);
}

template<typename T>
LeftistHeap<T>::LeftistHeap(LeftistHeap&& rhs):root{std::move(rhs.root)}
{}

template<typename T>
LeftistHeap<T>::~LeftistHeap()
{
}

template<typename T>
void LeftistHeap<T>::merge(LeftistHeap& rhs)
{
    if (this == &rhs)
        return ;    //重名
    
    root = merge(root, rhs.root);
    rhs.root = nullptr;
}


template<typename T>
typename LeftistHeap<T>::LeftistNode* LeftistHeap<T>::merge(LeftistNode* h1, LeftistNode* h2)
{
    if (h1==nullptr)
        return h2;
    if (h2==nullptr)
        return h1;

    if (h1->element < h2->element)
        return merge1(h1, h2);      //这是间接递归
    else
        return merge1(h2, h1);
}

template<typename T>
typename LeftistHeap<T>::LeftistNode* LeftistHeap<T>::merge1(LeftistNode* h1, LeftistNode* h2)
{
    if (h1->left == nullptr)
        h1->left = h2;
    else
    {
        h1->right = merge(h1->right, h2);
        if (h1->left->npl < h2->right->npl)
            swapChildren(h1);
        h1->npl = h1->right->npl+1;
    }
    return h1;
}

template<typename T>
void LeftistHeap<T>::insert(const T& x)
{
    root = merge(new LeftistNode{x}, root);
}

template<typename T>
void LeftistHeap<T>::deleteMin()
{
    if (isEmpty())
        throw ;

    LeftistNode* oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;
}

template<typename T>
void LeftistHeap<T>::deleteMin(T& minItem)
{
    minItem = findMin();
    deleteMin();
}


#endif