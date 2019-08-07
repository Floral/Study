#include<iostream>
#include<vector>
#include<list>

using namespace std;
int main()
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};

    vector<int> v;
    list<int> l;

    for (auto &i : ia)
    {
        v.push_back(i);
        l.push_back(i);
    }
    
    auto vit(v.cbegin());
    auto lit(l.cbegin());
    
    for (; vit != v.cend() && lit != l.cend();)
    {
        if ((*vit)%2==0)
        {
            vit = v.erase(vit);
            ++lit;
        }
        else
        {
            lit = l.erase(lit);
            ++vit;
        }
    }
    
    for (size_t i = 0; i < v.size(); i++)
    {
        /* code */
        cout<<v[i]<<endl;
    }
    cout<<"list:\n"<<ends;
    for (auto &i : l)
    {
        cout<<i<<endl;
    }
    
    return 0;
}