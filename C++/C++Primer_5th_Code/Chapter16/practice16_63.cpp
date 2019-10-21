#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename T>
size_t count(std::vector<T> const &v, T target)
{
    size_t flag=0;
    for (auto &i : v)
    {
        if(i==target)
            ++flag;
    }
    
    return flag;
}

template<>
size_t count(std::vector<const char*> const &v, const char* target)
{
    size_t flag=0;
    for (auto &i : v)
    {
        if(i==target)
            ++flag;
    }
    
    return flag;
}

size_t count(std::vector<string> const &v, const char* target)
{
    size_t flag=0;
    for (auto &i : v)
    {
        if(i==target)
            ++flag;
    }
    
    return flag;
}

int main()
{
    vector<int> v1{1,2,3,4,5,6,7,6,6,8,9,0};
    vector<double> v2{1,2,3,4,5,3,4,3,2,5,6};
    vector<string> v3{"1","2","3","4","2","3","5"};

    cout<<count(v1,6)<<endl;
    cout<<count(v3,"dasda")<<endl;
    return 0;
}