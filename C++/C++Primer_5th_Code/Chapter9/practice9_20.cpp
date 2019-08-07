#include<iostream>
#include<list>
#include<deque>

using namespace std;

int main()
{
    list<int> l;
    int i;
    while (cin>>i)
    {
        l.push_back(i);
    }
    
    deque<int> odd,even;
    for (auto &i : l)
    {
        if (i%2==0)
        {
            even.push_back(i);
        }
        else
        {
            odd.push_back(i);
        }
    }

    cout<<"odd queue:"<<endl;

    for (auto &i : odd)
    {
        cout<<i<<endl;
    }
    cout<<"even queue:"<<endl;
    for (auto &i : even)
    {
        cout<<i<<endl;
    }
    deque<int> q2;
    cout<<q2.at(0);
    return 0;
}