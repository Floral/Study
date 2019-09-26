#include<iostream>
#include<string>
#include<vector>
#include<list>

using std::cout; using std::cin; using std::endl;
using std::vector;
using std::string;
using std::list;

template<typename T, unsigned N>
unsigned size(T (&arr)[N])
{
    return N;
}


int main()
{
    int k[]={1,2,3,4,5,6,7,8,9,0};
    cout<<size(k)<<endl;
    return 0;
}