// #define NDEBUG
#include<iostream>
#include<vector>
#include<cassert>
#include<string>

using std::cin; using std::cout;
using std::endl; using std::vector;
using std::string;
using Iter = vector<string>::iterator;

void func(Iter begin,Iter end)
{
    #ifndef NDEBUG
        cout<<"The vector remains "<<end-begin<<" string."<<endl;
    #endif
    if (begin!=end)
    {
        cout<<*begin<<endl;
        func(++begin,end);
    }else
    {
        cout<<"over!"<<endl;
    }
    
}

int main()
{
    vector<string> v{"1","2","3","4","5"};
    func(v.begin(),v.end());
    return 0;
}