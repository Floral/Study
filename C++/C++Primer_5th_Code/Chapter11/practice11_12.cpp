#include<iostream>
#include<utility>
#include<vector>
#include<string>

using namespace std;

int main()
{
    vector<pair<string,int>> v;
    string s;
    int i;
    while (cin>>s>>i)
    {
        v.push_back({s,i});
    }
    
    for (auto &i : v)
    {
        cout<<i.first<<" "<<i.second<<endl;
    }
    
    return 0;
}