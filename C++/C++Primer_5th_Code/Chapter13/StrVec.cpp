#include<iostream>
#include<string>
#include<memory>
#include<map>
#include<utility>
#include"StrVec.h"

using namespace std;

allocator<string> StrVec::alloc;

void StrVec::push_back(const string& s)
{
    chk_n_alloc();  // make sure that there are enough space to insert new string
    alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if(elements)
    {
        // destroy old elements from end to begin
        for (auto p = first_free; p != elements; )
        {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap-elements);
    }
}

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(const initializer_list<string> il)
{
    auto newdata = alloc_n_copy(il.begin(),il.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec(){ free(); }

StrVec& StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    auto newcapacity = size()?2*size():1;
    auto newdata = alloc.allocate(newcapacity);

    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size() ; ++i)
    {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();

    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
    
}