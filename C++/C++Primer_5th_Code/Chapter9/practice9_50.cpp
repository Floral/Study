#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main()
{
    vector<string> v;
    string s;
    while (cin>>s)
    {
        v.push_back(s);
    }
    
    int sum=0;
    for (auto &i : v)
    {
        sum+=stoi(i);
    }
    
    cout<<sum<<endl;
    return 0;
}