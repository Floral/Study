#include<iostream>
#include<vector>


class NoDefault{
public:
    NoDefault(int i){}
    static const int i=0;
    static constexpr double j = 6.5;

};

class C{
public:
    C():n(0){} 
private:
    NoDefault n;
};

int main()
{
    std::vector<C> vec(10);    
    return 0;
}