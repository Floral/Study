#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
void dispVector(const vector<string> &v)
{
    for (auto &i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}

bool isLongerThan4(const string &s)
{
    return s.size()>4;
}

int main()
{
    vector<string> v;
    string i;
    while (cin>>i)
    {
        v.push_back(i);
    }
    
    dispVector(v);

    auto distinct = partition(v.begin(),v.end(),isLongerThan4);

    for (auto it = v.begin(); it != distinct; ++it)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
    return 0;
}