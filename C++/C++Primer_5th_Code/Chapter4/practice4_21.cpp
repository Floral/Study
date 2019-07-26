#include<iostream>
#include<vector>

using std::vector;
using std::cin; using std::cout; using std::endl;

int main()
{
    vector<int> v;
    int t;
    while (cin>>t)
        v.push_back(t);
    
    for (auto &i : v)
    {
        (i%2==1) ? i=i*2 : i;
    }
    for (auto &i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    
    return 0;
}