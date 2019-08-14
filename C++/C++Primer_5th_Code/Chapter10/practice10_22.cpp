#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;
using namespace std::placeholders;

bool ifLessThan(const string &word,string::size_type &sz)
{
    return word.size()<=sz;
}

void countLessThan6(const vector<string> &words,string::size_type sz)
{
    cout<<count_if(words.cbegin(),words.cend(),bind(ifLessThan,_1,sz))<<endl;
}

int main()
{
    vector<string> v;
    string i;
    string::size_type j=5;
    while(cin>>i)
        v.push_back(i);
    countLessThan6(v,j);
    return 0;
}