#include<iostream>
#include<string>
#include<vector>
#include<list>

using std::cout; using std::cin; using std::endl;
using std::vector;
using std::string;
using std::list;

template<typename T, unsigned N>
T* begin(const T (&container)[N])
{
    return container;
}

template<typename T, unsigned N>
T* end(const T (&container)[N])
{
    return container+N;
}

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    auto it = begin(v);
    cout<<*it<<endl;
    return 0;
}