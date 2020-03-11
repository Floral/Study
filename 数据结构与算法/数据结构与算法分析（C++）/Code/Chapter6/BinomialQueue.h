#ifndef BINOMIAL_QUEUE
#define BINOMIAL_QUEUE

#include<vector>
#include<algorithm>
#include<utility>

template<typename T>
class BinomialQueue
{
private:
    struct BinomialNode;
    const static int DEFAULT_TREES = 1;

    std::vector<BinomialNode*> theTrees;    //树根组成的数组
    int currentSize;

    int findMinIndex() const;
    int capacity() const;
    BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2); //合并两个树
    void makeEmpty(BinomialNode*& t);
    BinomialNode* clone(BinomialNode* t) const;
    
public:
    BinomialQueue();
    BinomialQueue(const T& item);
    BinomialQueue(const BinomialQueue& rhs);
    BinomialQueue(BinomialQueue&& rhs);
    ~BinomialQueue();

    BinomialQueue& operator=(const BinomialQueue& rhs);
    BinomialQueue& operator=(BinomialQueue&& rhs);

    bool isEmpty() const;
    const T& findMin() const;

    void insert(const T& x);
    void insert(T&& x);
    void deleteMin();
    void deleteMin(T& minItem);

    void makeEmpty();
    void merge(BinomialQueue& rhs);
};

template<typename T>
struct BinomialQueue<T>::BinomialNode
{
    T element;
    BinomialNode* leftChild;
    BinomialNode* nextSibling;

    BinomialNode(const T& e, BinomialNode* lt, BinomialNode* rt)
    :element{e}, leftChild{lt}, nextSibling{rt} {}

    BinomialNode(T&& e, BinomialNode* lt, BinomialNode* rt)
    :element{std::move(e)}, leftChild{lt}, nextSibling{rt} {}
};


template<typename T>
typename  BinomialQueue<T>::BinomialNode* BinomialQueue<T>::combineTrees(BinomialNode* t1, BinomialNode* t2)
{
    if (t1->element <= t2->element)
    {
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        return t1;
    }
    else
        return combineTrees(t2,t1);
}

template<typename T>
BinomialQueue<T>::BinomialQueue()
{
}

template<typename T>
BinomialQueue<T>::~BinomialQueue()
{
}



#endif