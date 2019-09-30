#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template<typename T>
void print(T &t)
{
    
    for(auto b = t.begin();b!=t.end();++b)
    {
        cout<<(*b)<<" ";
    }
    cout<<endl;
}

int main()
{
    vector<string> v{"1","2","3","4","5","6"};

    print(v);
    return 0;
}