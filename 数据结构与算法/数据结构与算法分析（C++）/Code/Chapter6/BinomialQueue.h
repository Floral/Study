#ifndef BINOMIAL_QUEUE
#define BINOMIAL_QUEUE

#include<vector>
#include<algorithm>
#include<utility>
#include<exception>

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

template<typename T>
void BinomialQueue<T>::makeEmpty(BinomialNode*& t)
{
    if (t == nullptr)
        return;
    
    makeEmpty(t->leftChild);
    makeEmpty(t->nextSibling);

    delete t;
    t = nullptr;
}

template<typename T>
void BinomialQueue<T>::merge(BinomialQueue& rhs)
{
    if (this == &rhs)
        return ;        //避免别名问题

    currentSize+=rhs.currentSize;

    if (currentSize > capacity())
    {
        int oldNumTrees = theTrees.size();
        int newNumTrees = std::max(theTrees.size(), rhs.theTrees.size()) + 1;
        theTrees.resize(newNumTrees);
        for (size_t i = oldNumTrees; i < count; i++)
            theTrees[i] = nullptr;      //新增的根指针初始化为nullptr
    }

    BinomialNode* carry = nullptr;  //carry是进位的意思
    for (size_t i = 0, j = 1; j <= currentSize; ++i, j*=2)
    {
        BinomialNode* t1 = theTrees[i];
        BinomialNode* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;
        
        int whichCase = (t1 == nullptr ? 0:1);
        whichCase += (t2 == nullptr ? 0:2);
        whichCase += (carry == nullptr ? 0:4);

        switch (whichCase)
        {
        case 0: //没有高度为i的树的情况
        case 1: //只有this有高度为i的树的情况
            break;
        case 2: //只有rhs有高度为i的树
            theTrees[i] = t2;
            rhs.theTrees[i] = nullptr;
            break;
        case 4: //只有carry的情况
            theTrees[i] = carry;
            carry = nullptr;
            break;
        case 3: //this和rhs都有高度为i的树
            carry = combineTrees(t1,t2);    //合并后的树在下一个高度被存储，即i+1
            theTrees[i] = rhs.theTrees[i] = nullptr;
            break;
        case 5: //this 和carry的情况
            carry = combineTrees(t1, carry);
            theTrees[i] = nullptr;
            break;
        case 6: //rhs 和carry的情况
            carry = combineTrees(t2, carry);
            rhs.theTrees[i] = nullptr;
            break;
        case 7: //this rhs and carry
            theTrees[i] = carry;
            carry = combineTrees(t1, t2);
            rhs.theTrees[i] = nullptr;
            break;
        }
    }
    
    for (auto& root : rhs.theTrees)
        root = nullptr;
    rhs.currentSize = 0;
}

template<typename T>
int BinomialQueue<T>::findMinIndex() const
{
    int i;
    int minIndex;

    for (i = 0; theTrees[i] == nullptr ; ++i)
        ;
    
    for (minIndex = i; i < theTrees.size(); ++i)
        if (theTrees[i]!=nullptr &&
            theTrees[i]->element < theTrees[minIndex]->element)
            minIndex = i;

    return minIndex;
}

template<typename T>
int BinomialQueue<T>::capacity() const
{
    return theTrees.capacity();
}

template<typename T>
void BinomialQueue<T>::deleteMin(T& minItem)
{
    if (isEmpty())
        throw std::exception();
    
    int minIndex = findMinIndex();
    minItem = theTrees[minIndex]->element;

    BinomialNode* oldRoot = theTrees[minIndex];
    BinomialNode* deletedTree = oldRoot->leftChild;
    delete oldRoot;

    //构建H''
    BinomialQueue deletedQueue;
    deletedQueue.theTrees.resize(minIndex+1);
    deletedQueue.currentSize = (1<<minIndex) - 1;
    for (size_t i = minIndex-1; i >= 0; --i)    //删掉根节点后拆分成多个子树
    {
        deletedQueue.theTrees[i] = deletedTree;
        deletedTree = deletedTree->nextSibling;
        deletedQueue.theTrees[i]->nextSibling = nullptr;
    }

    //构建H'
    theTrees[minIndex] = nullptr;
    currentSize -= deletedQueue.currentSize+1;  //因为merge里面会加上currentSize的，但是减去了一个最小的
    merge(deletedQueue);
}

#endif