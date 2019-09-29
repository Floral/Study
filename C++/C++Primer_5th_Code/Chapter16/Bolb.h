#ifndef BLOB
#define BLOB

#include<iostream>
#include<vector>
#include<memory>

template <typename T> class Blob{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    Blob();
    Blob(std::initializer_list<T> il);

    size_type size() const { return data->size();}
    bool empty() const { return data->empty(); }

    void push_back(const T &t) { data->push_back(t); }
    void push_back(const T &&t) { data->push_back(std::move(t)); }
    void pop_back();

    T& back();
    T& operator[](size_type i);

private:
    std::shared_ptr<std::vector<T>> data;

    void check(size_type i, const std::string &msg) const;

};

template<typename T> class BlobPtr{
public:
    BlobPtr():curr(0) {};
    BlobPtr(Blob<T> &a, size_t sz = 0): wptr(a.data),curr(sz) {}
    T& operator*() const
    {
        auto p = check(curr,"dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++();
    BlobPtr& operator--();

    BlobPtr operator++(int);
    BlobPtr operator--(int);
private:
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;

    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

#endif