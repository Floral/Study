#include"vector.h"
#include<iostream>

using namespace std;

int main()
{
    Vector<int> v{3};
    cout<<"size:"<<v.size()<<",capacity:"<<v.capacity()<<endl;
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        cout<<"before:"<<*itr<<" ";
        *itr = 6;
        cout<<"after:"<<*itr<<endl;
    }
    v.push_back(12345);
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        cout<<*itr<<endl;
    }
    cout<<endl<<v.back();
    cout<<endl;
    v.pop_back();
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        cout<<*itr<<endl;
    }
    v.reserve(10);
    cout<<"capacity: "<<v.capacity()<<endl;

    return 0;
}