#ifndef STRBLOBPTR
#define STRBLOBPTR

#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include"StrBlob.h"

// using namespace std;
class StrBlob;

class StrBlobPtr
{
public:
    StrBlobPtr():curr(0){};
    StrBlobPtr(StrBlob &a, size_t sz = 0):
                wptr(a.data),curr(sz){};
    // ~StrBlobPtr();

    std::string& deref() const;
    StrBlobPtr& incr();

private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;    //the position in vector currently;

};

std::shared_ptr<std::vector<std::string>> 
StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
    {
        throw std::runtime_error("unbound StrBlobPtr");
    }
    if (i>=ret->size())
    {
        throw std::out_of_range(msg);
    }
    return ret;
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

#endif