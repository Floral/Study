#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

struct Sales_data
{
    string isbn;
    double avenue=0.0;
};


bool compareIsbn(const Sales_data &s1,const Sales_data &s2)
{
    return s1.isbn<s2.isbn;
}

int main()
{
    Sales_data s1={"abcdefg"};
    Sales_data s2={"bcdefgh"};

    vector<Sales_data> v;
    v.push_back(s2);
    v.push_back(s1);
    for (auto &i : v)
    {
        cout<<i.isbn<<" ";
    }
    cout<<endl;

    stable_sort(v.begin(),v.end(),[](const Sales_data &s1,const Sales_data &s2){return s1.isbn<s2.isbn;});

    for (auto &i : v)
    {
        cout<<i.isbn<<" ";
    }
    cout<<endl;
    return 0;
}