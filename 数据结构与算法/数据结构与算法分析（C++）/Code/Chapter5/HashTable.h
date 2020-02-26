#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include<vector>
#include<list>
#include<functional>
#include<algorithm>

using std::vector;
using std::list;
using std::hash;
using std::find;

template<typename T>
class HashTable
{
private:
    vector<list<T>> theLists;   // 链式hash表
    int currentSize;

    void rehash();
    size_t myhash(const T& x) const;

    
public:
    explicit HashTable(int size = 101):currentSize{0}
    { theLists.reserve(size); }
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
    return hf(x) % theLists.size();
}

template<typename T>
void HashTable<T>::makeEmpty()
{
    for(auto& theList: theLists)
        theList.clear();
}

template<typename T>
bool HashTable<T>::contains(const T& x) const
{
    auto& theList = theLists[myhash(x)];
    return find(std::begin(theList), std::end(theList)) != theList.end();
}

template<typename T>
bool HashTable<T>::insert(const T& x)
{
    auto& whichList = theLists[myhash(x)];
    if (find(std::begin(whichList), std::end(whichList)) != std::end(whichList))
        return false;

    whichList.push_back(x);

    if (++currentSize > theLists.size())
        rehash();   //重散列

    return true;
}

template<typename T>
bool HashTable<T>::insert(T&& x)
{
    auto& whichList = theLists[myhash(x)];
    if (find(std::begin(whichList), std::end(whichList)) != std::end(whichList))
        return false;

    whichList.push_back(std::move(x));

    if (++currentSize > theLists.size())
        rehash();   //重散列

    return true;
}

template<typename T>
bool HashTable<T>::remove(const T& x)
{
    auto& theList = theLists[myhash(x)];
    auto& itr = find(std::begin(theList), std::end(theList));

    if(itr == std::end(theList))
        return false;

    theList.erase(itr);
    --currentSize;

    return true;
}

#endif