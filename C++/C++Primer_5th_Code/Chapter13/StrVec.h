#ifndef STRVEC
#define STRVEC

#include<iostream>
#include<memory>
#include<string>

class StrVec
{
private:
    static std::allocator<std::string> alloc;   //分配元素
    void chk_n_alloc()
    { if (size() == capacity()) reallocate();}

    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);

    void free();
    void reallocate();

    std::string *elements;
    std::string *first_free;
    std::string *cap;

public:
    StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){};
    StrVec(const StrVec&);  //拷贝构造函数;
    StrVec(StrVec&&) noexcept; //移动构造函数
    StrVec(const std::initializer_list<std::string>);
    StrVec& operator=(const StrVec&);
    StrVec& operator=(StrVec &&rhs) noexcept;
    ~StrVec();

    void push_back(const std::string&);
    size_t size() const {return first_free-elements;}
    size_t capacity() const {return cap-elements;}
    std::string *begin() const {return elements;}
    std::string *end() const {return first_free;}

};



#endif