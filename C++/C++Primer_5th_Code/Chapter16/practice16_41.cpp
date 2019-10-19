#include<iostream>
#include<string>
#include<vector>
#include<type_traits>

using namespace std;

template<typename T>
auto sum(T op1, T op2) -> decltype(op1+op2)
{
    return op1+op2;
}

int main()
{
    long a=10000000,b=20000000;
    auto s = sum(a,b);

    cout<<s<<endl;
    return 0;
}