#ifndef MY_CUCKOO_HASH_TABLE
#define MY_CUCKOO_HASH_TABLE

#include<vector>
#include<functional>

template<typename T>
class CuckooHashFamily
{
public:
    size_t hash(const T& x, int which) const;
    int getNumOfFunctions() const;
    void generateNewFunctions();
};

template<typename T>
class StringHashFamily: public CuckooHashFamily<T>
{
    //I'm lazy....

};

class UniformRandom
{
public:
    int nextInt(int);
};


template<typename T, typename HashFamily>
class CuckooHashTable
{
private:
    struct HashEntry
    {
        T element;
        bool isActive;

        HashEntry(const T& e = T{}, bool a = false)
        :element{e}, isActive{a} {}
        HashEntry(T&& e, bool a = false)
        :element{std::move(e)}, isActive{a} {}
    };

    static constexpr double MAX_LOAD = 0.40;
    static const int ALLOWED_REHASHES = 5;

    std::vector<HashEntry> array;
    int currentSize;
    int numHashFunctions;
    int rehashes;
    UniformRandom r;
    HashFamily hashFunctions;
    
public:
    explicit CuckooHashTable(int size = 101);
    ~CuckooHashTable();
    
    void makeEmpty();
    bool contains(const T& x) const;
    bool remove(const T& x);
    bool insert(const T& x);
    bool insert(T&& x);

private:

    bool insertHelper1(const T& xx);
    bool insertHelper1(T&& xx);
    bool isActive(int currentPos) const;

    size_t myhash(const T& x, int which) const;
    int findPos(const T& x) const;
    void expand();
    void rehash();
    void rehash(int newSize);

};

int nextPrime(int size);

template<typename T, typename HashFamily>
CuckooHashTable<T, HashFamily>::CuckooHashTable(int size)
:array( nextPrime(size) ), rehashes{0}
{
    numHashFunctions = hashFunctions.getNumOfFunctions();
    makeEmpty();
}

template<typename T, typename HashFamily>
CuckooHashTable<T, HashFamily>::~CuckooHashTable()
{   makeEmpty(); }

template<typename T, typename HashFamily>
void CuckooHashTable<T, HashFamily>::makeEmpty()
{
    currentSize = 0;
    for (auto &i : array)
        i.isActive = false;   
}


template<typename T, typename HashFamily>
bool CuckooHashTable<T, HashFamily>::contains(const T& x) const
{
    return findPos(x) != -1;
}

template<typename T, typename HashFamily>
bool CuckooHashTable<T, HashFamily>::remove(const T& x)
{
    int pos = findPos(x);
    if (pos == -1)
        return false;

    array[pos].isActive = false;
    --currentSize;
    return true;
}

template<typename T, typename HashFamily>
bool CuckooHashTable<T, HashFamily>::insert(const T& x)
{
    if (contains(x))
        return false;

    if (currentSize >= array.size()*MAX_LOAD)
        expand();

    return insertHelper1(x);
}

template<typename T, typename HashFamily>
bool CuckooHashTable<T, HashFamily>::insert(T&& x)
{
    if (contains(x))
        return false;

    if (currentSize >= array.size()*MAX_LOAD)
        expand();

    return insertHelper1(std::move(x));
}


/*********************** Private Functions ***************************/

template<typename T, typename HashFamily>
bool CuckooHashTable<T, HashFamily>::insertHelper1(const T& xx)
{
    const int COUNT_LIMIT = 100;
    T x = xx;

    while (true)
    {
        int lastPos = -1;
        int pos;
        for (size_t count = 0; count < COUNT_LIMIT; ++count)
        {
            for (size_t i = 0; i < numHashFunctions; ++i)
            {
                pos = myhash(x, i);
                if (!array[pos].isActive)   //如果有空位
                {
                    array[pos] = std::move(HashEntry{std::move(x), true});
                    ++currentSize;
                    return true;
                }
            }

            //没有空位了，替换掉一个随机的位置
            int i = 0;
            do
            {
                pos = myhash(x, r.nextInt(numHashFunctions));
            } while (pos == lastPos && i++<5);

            lastPos = pos;
            std::swap(x, array[pos].element);   //这是因为要递归替换了
        }

        //若没有在前一个 for循环中return true出去，说明该散列表有点拥挤了
        if (++currentSize > ALLOWED_REHASHES)
        {
            expand();
            rehashes = 0;   
        }
        else
            rehash();   //表大小相同，但是散列函数是新的了
    }
}

template<typename T, typename HashFamily>
bool CuckooHashTable<T, HashFamily>::isActive(int currentPos) const
{    
    return currentPos == -1 ? false : array[currentPos].isActive;
}

template<typename T, typename HashFamily>
size_t CuckooHashTable<T, HashFamily>::myhash(const T& x, int which) const
{
    return hashFunctions.hash(x, which) % array.size();
}


template<typename T, typename HashFamily>
int CuckooHashTable<T, HashFamily>::findPos(const T& x) const
{
    for(size_t i = 0; i<numHashFunctions ; ++i)
    {
        int currentPos = myhash(x, i);

        if (array[currentPos].isActive &&
            array[currentPos].element == x)
            return currentPos;
        
    }
    return -1;
}


template<typename T, typename HashFamily>
void CuckooHashTable<T, HashFamily>::expand()
{   rehash(static_cast<int> (currentSize / MAX_LOAD) ); }

template<typename T, typename HashFamily>
void CuckooHashTable<T, HashFamily>::rehash()
{
    hashFunctions.generateNewFunctions();
    rehash(array.size());
}

template<typename T, typename HashFamily>
void CuckooHashTable<T, HashFamily>::rehash(int newSize)
{
    std::vector<HashEntry> oldArray = array;

    array.resize(nextPrime(newSize));
    for (auto& i : array)
        i.isActive = false;

    for (auto& i : oldArray)
        if (i.isActive)
            insert(std::move(i.element));
}

#endif