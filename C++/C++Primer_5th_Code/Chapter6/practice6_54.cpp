#include<iostream>
#include<vector>

using std::cin; using std::cout;
using std::endl; using std::vector;

int func(int a,int b);

using PF=int(*)(int,int);
int main()
{
    vector<decltype(func)*> v;
    return 0;
}