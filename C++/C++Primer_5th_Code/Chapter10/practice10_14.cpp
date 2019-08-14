#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    auto f=[](const int i,const int j){cout<<i<<" "<<j<<endl;return i+j;};
    auto d=[](const int i,const int j){cout<<i<<" "<<j<<endl;return i+j;};
    int i,j;
    cin>>i>>j;
    cout<<d(i,j)<<endl;
    return 0;
}