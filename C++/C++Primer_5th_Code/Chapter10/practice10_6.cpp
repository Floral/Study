#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    cout<<"before:";
    for (auto &i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    fill_n(v.begin(),v.size(),0);
    
    cout<<"after:";
    for (auto &i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    
    return 0;
}