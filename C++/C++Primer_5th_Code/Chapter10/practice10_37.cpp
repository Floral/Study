#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    list<int> l(v.crbegin()+3,v.crend()-2);
    
    for (auto &i : l)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    

    return 0;
}