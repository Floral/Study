#include<iostream>
#include<string>
#include<set>
#include<sstream>
#include<algorithm>

using namespace std;

int main()
{
    string s;
    set<string> dict;

    while (cin>>s)
    {
        /* code */
        dict.insert(s);
    }
    for (auto &i : dict)
    {
        cout<<i<<endl;
    }
    
    return 0;
}