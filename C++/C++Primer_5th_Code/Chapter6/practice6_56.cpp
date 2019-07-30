#include<iostream>
#include<vector>

using std::cin; using std::cout;
using std::endl; using std::vector;


    int func(int,int);
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
    int divide(int a, int b) { return b != 0 ? a / b : 0; }
int main()
{
    vector<decltype(func)*> v;

    v.push_back(add);
    v.push_back(subtract);
    v.push_back(multiply);
    v.push_back(divide);

    int i=10,j=2;
    for (auto &x : v)
    {
        cout<<x(i,j)<<endl;
    }
    
    return 0;
}