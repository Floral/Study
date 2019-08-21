#include<iostream>
#include<string>

class HasPtr{
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)),i(0){}
    HasPtr(const HasPtr &orig):
        ps(new std::string(*orig.ps)),i(orig.i){}

    HasPtr& operator=(const HasPtr &rhs)
    {
        (*ps)=(*rhs.ps);
        i = rhs.i;
        return *this;
    }
    std::string* getContent()
    {
        return ps;
    }

private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{

}

using namespace std;
int main()
{
    
    HasPtr hp("test"),hp2("hhhh");
    cout<< *(hp.getContent())  <<endl;
    
    // hp2=hp;
    cout<<*(hp2.getContent()) <<endl;
    return 0;
}