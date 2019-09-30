#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template<typename T>
void print(T &t)
{
    typename T::size_type i=0;
    for(;i!=t.size();++i)
    {
        cout<<t[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    vector<string> v{"1","2","3","4","5","6"};

    print(v);
    return 0;
}