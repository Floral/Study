#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include<vector>
#include<list>

using std::vector;
using std::list;

template<typename T>
class HashTable
{
private:
    vector<list<T>> theLists;   // 链式hash表
    int currentSize;

    void rehash();
    size_t myhash(const T& x) const;

    
public:
    explicit HashTable(int size = 101):currentSize{size}{};
    ~HashTable()
    { makeEmpty(); }

    bool contains(const T& x) const;
    void makeEmpty();

    bool insert(const T& x);
    bool insert(T&& x);
    bool remove(const T& x);
};


#endif