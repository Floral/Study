#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

void dispVector(const vector<string>&);

void elimDups(vector<string> &words)
{
    sort(words.begin(),words.end());
    dispVector(words);
    auto end_unique = unique(words.begin(),words.end());
    words.push_back("test");
    cout<<"in:"<<words.size()<<endl;

    dispVector(words);
    words.erase(end_unique,words.end());
}

void dispVector(const vector<string> &v)
{
    for (auto &i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}

bool isShorter(const string &s1,const string &s2)
{
    return s1.size()<s2.size();
}


int main()
{
    vector<string> v;
    string i;
    while (cin>>i)
    {
        v.push_back(i);
    }
    cout<<"before:"<<endl;
    dispVector(v);
    elimDups(v);

    cout<<"after:"<<endl;
    dispVector(v);
    stable_sort(v.begin(),v.end(),isShorter);

    cout<<"stable_sort"<<endl;
    dispVector(v);
    return 0;
}