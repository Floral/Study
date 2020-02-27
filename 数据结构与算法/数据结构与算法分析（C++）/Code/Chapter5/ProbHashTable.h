#ifndef MY_PROBING_HASH_TABLE
#define MY_PROBING_HASH_TABLE

#include<vector>
#include<algorithm>
#include<functional>


int nextPrime(int x)
{
    //todo
}

template<typename T>
class HashTable
{
public:
    enum EntryType{ ACTIVE, EMPTY, DELETED};

private:
    struct HashEntry
    {
        T element;
        EntryType info;

        HashEntry(const T& e = T{}, EntryType i = EMPTY)
        :element{e}, info{i} {}

        HashEntry(T&& e, EntryType i = EMPTY)
        :element{std::move(e)}, info{i} {}
    };

    std::vector<HashEntry> array;   // 链式hash表
    int currentSize;

    bool isActive(int currentPos) const;
    int findPos(const T& x) const;
    void rehash();
    size_t myhash(const T& x) const;

    
public:
    explicit HashTable(int size = 101):currentSize{0}
    { array.reserve(size); }
    ~HashTable()
    { makeEmpty(); }

    bool contains(const T& x) const;
    void makeEmpty();

    bool insert(const T& x);
    bool insert(T&& x);
    bool remove(const T& x);
};


template<typename T>
size_t HashTable<T>::myhash(const T& x) const
{
    static hash<T> hf;
    return hf(x) % array.size();
}

template<typename T>
void HashTable<T>::makeEmpty()
{
    currentSize = 0;
    for(auto& entry: array)
        entry.info = EMPTY;
}

template<typename T>
bool HashTable<T>::contains(const T& x) const
{
    return isActive(findPos(x));
}

template<typename T>
int HashTable<T>::findPos(const T& x) const //该函数的任务是找到与x相等的元素，即使为deleted也要返回其位置
{
    size_t currentPos = myhash(x);
    int offset = 1;

    while (array[currentPos].info != EMPTY &&
           array[currentPos].element != x)
    {
        currentPos += offset;       //平方消解函数
        offset += 2;

        if (currentPos>=currentSize)
            currentPos -= currentSize;
    }
    
    return currentPos;
}

template<typename T>
bool HashTable<T>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template<typename T>
bool HashTable<T>::insert(const T& x)
{
    int currentPos = findPos(x);

    if (isActive(currentPos))
        return false;

    array[currentPos].info = ACTIVE;
    array[currentPos].element = x;

    if (++currentSize > array.size()/2)
        rehash();
    
    return true;
}

template<typename T>
bool HashTable<T>::insert(T&& x)
{
    int currentPos = findPos(x);

    if (isActive(currentPos))
        return false;

    array[currentPos].info = ACTIVE;
    array[currentPos].element = std::move(x);

    if (++currentSize > array.size()/2)
        rehash();
    
    return true;
}

template<typename T>
bool HashTable<T>::remove(const T& x)   //值得注意的是，这里的remove并不减小currentSize的值
{
    int currentPos = findPos(x);

    if (!isActive(currentPos))
        return false;

    array[currentPos].info = DELETED;

    return true;
}

template<typename T>
void HashTable<T>::rehash()
{
    std::vector<HashEntry> oldArray = array;

    //创建两倍大的空表
    array.resize(nextPrime(2*oldArray.size())); 
    for (auto& entry : array)
        entry.info = EMPTY;

    //复制整个表
    for (auto& entry : oldArray)
    {
        if (entry.info = ACTIVE)
        {
            insert(std::move(entry.element));
        }
    }
}

#endif