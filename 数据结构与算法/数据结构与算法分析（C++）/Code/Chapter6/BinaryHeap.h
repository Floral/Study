#ifndef MY_BINARY_HEAP
#define MY_BINARY_HEAP

#include<vector>
#include<iostream>

template<typename T>
class BinaryHeap
{
private:
    /* data */
    int                 currentSize;
    std::vector<T>      array;

    void buildHeap();
    void percolateDown();

public:
    explicit BinaryHeap(int capacity = 100);
    explicit BinaryHeap(const vector<T>& items);
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
BinaryHeap<T>::~BinaryHeap()
{
}

#endif