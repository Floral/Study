#include<iostream>
#include<deque>
#include<string>

using namespace std;

int main()
{
    deque<string> q;
    string s;

    while (cin>>s)
    {
        /* code */
        q.push_back(s);
        // q.emplace_back(s);
        // q.insert(q.cend(),s);
    }
    
    for (auto &i : q)
    {
        cout<<i<<endl;
    }
    

    return 0;
}