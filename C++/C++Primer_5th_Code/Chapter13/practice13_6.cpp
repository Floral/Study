#include<iostream>
#include<string>

class HasPtr{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)),i(0){}
    HasPtr(const HasPtr &orig):
        ps(new std::string(*orig.ps)),i(orig.i){}

    HasPtr& operator=(const HasPtr &rhs)
    {
        (*ps)=(*rhs.ps);
        i = rhs.i;
    }

private:
    std::string *ps;
    int i;
};

int main()
{
    
    return 0;
}