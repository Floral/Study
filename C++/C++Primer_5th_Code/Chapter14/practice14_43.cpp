#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>

using namespace std;

int main()
{
    vector<int> v{2,3,4,5};
    int input;
    modulus<int> mod;

    cin>>input;
    auto predicator = [&](int i){return mod(input,i)!=0;};
    auto p = none_of(v.begin(),v.end(),predicator);
    cout<<(p?"Yes":"No")<<endl;
    return 0;
}