#include<iostream>

using namespace std;

int main()
{
    int i;

    cin>>i;
    auto f=[i](int j){cout<<i<<" "<<j<<endl; return i+j;};

    cout<<f(3)<<endl;
    return 0;
}