#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>
#include<list>

using namespace std;

int main()
{
    vector<int> v1={0,1,2,3,4,5,6,7,8,9};
    vector<int> v2;
    // back_insert_iterator bt = back_inserter(v2);
    unique_copy(v1.cbegin(),v1.cend(),back_inserter(v2));

    for (auto &i : v2)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}