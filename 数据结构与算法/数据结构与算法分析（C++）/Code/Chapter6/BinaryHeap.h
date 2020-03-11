#ifndef MY_BINARY_HEAP
#define MY_BINARY_HEAP

#include<vector>
#include<iostream>
#include<exception>

template<typename T>
class BinaryHeap
{
private:
    /* data */
    int                 currentSize;
    std::vector<T>      array;

    void buildHeap();
    void percolateDown(int hole);

public:
    explicit BinaryHeap(int capacity = 100);
    explicit BinaryHeap(const std::vector<T>& items);
    ~BinaryHeap();

    bool isEmpty() const;
    const T& findMin() const;

    void insert(const T& x);
    void insert(T&& x);
    void deleteMin();
    void deleteMin(T& minItem);
    void makeEmpty();

};

template<typename T>
BinaryHeap<T>::BinaryHeap(int capacity):currentSize{0}
{    array.reserve(capacity);    }

template<typename T>
BinaryHeap<T>::BinaryHeap(const std::vector<T>& items):currentSize{items.size()}
{    
    array.reserve(items.size()*2);
    for(size_t i = 0; i < items.size(); ++i)
        array[i+1] = items[i];
    buildHeap();
}

template<typename T>
BinaryHeap<T>::~BinaryHeap()
{ makeEmpty(); }

template<typename T>
void BinaryHeap<T>::buildHeap()
{
    for (size_t i = currentSize / 2; i > 0 ; --i)
        percolateDown(i);
}

template<typename T>
void BinaryHeap<T>::percolateDown(int hole)
{
    int child;
    T tmp = std::move(array[hole]);

    for (; hole*2 <= currentSize; hole = child )
    {
        child = hole*2;
        if (child!=currentSize && array[child+1] < array[child])
            ++child;
        if (array[child] < tmp)
            array[hole] = std::move(array[child]);
        else
            break;
    }

    array[hole] = tmp;
}

template<typename T>
bool BinaryHeap<T>::isEmpty() const
{
    return currentSize == 0;
}

template<typename T>
void BinaryHeap<T>::insert(const T& x)
{
    if (currentSize+1 >= array.size())
        array.reserve(array.size()*2);

    //上滤 percolate up    
    int hole = ++currentSize;
    T copy = x;

    array[0] = std::move(copy); //是用来解决hole=1的情况的
    for (; copy < array[hole/2]; hole /= 2)
        array[hole] = std::move(array[hole/2]);

    array[hole] = std::move(copy);
}

template<typename T>
void BinaryHeap<T>::insert(T&& x)
{
    if (currentSize+1 >= array.size())
        array.reserve(array.size()*2);
    
    int hole = ++currentSize;

    array[0] = std::move(copy); //是用来解决hole=1的情况的
    for (; x < array[hole/2]; hole /= 2)
        array[hole] = std::move(array[hole/2]);

    array[hole] = std::move(x);
}

template<typename T>
void BinaryHeap<T>::deleteMin()
{
    if (isEmpty())
        return;     //这里还可以抛出异常
    
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

//删除最小项并将其放在minItem处
template<typename T>
void BinaryHeap<T>::deleteMin(T& minItem)
{
    if (isEmpty())
        return;

    minItem = std::move(array[1]);
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

template<typename T>
void BinaryHeap<T>::makeEmpty()
{
    array.clear();
    currentSize = 0;
}

#endif