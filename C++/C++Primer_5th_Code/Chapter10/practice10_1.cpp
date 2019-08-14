#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<numeric>

using namespace std;

int main()
{
    vector<string> v;
    string t;

    while (cin>>t)
    {
        v.push_back(t);
    }
    
    // cout<<count(v.cbegin(),v.cend(),2)<<endl;
    string s = accumulate(v.cbegin(),v.cend(),string(""));
    cout<<s<<endl;

    return 0;
}