#include<iostream>
#include<string>
#include<vector>
#include<list>

using std::cout; using std::cin; using std::endl;
using std::vector;
using std::string;
using std::list;

template<typename T, unsigned N>
void print(T (&arr)[N])
{
    for (auto &&i : arr)
    {
        cout<<i<<" ";
    }
}

int main()
{
    int v[10]={1,2,3,4,5,6,7,8,9,0};

    print(v);
    return 0;
}