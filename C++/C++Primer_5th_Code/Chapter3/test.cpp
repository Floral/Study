#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cin; using std::cout; using std::endl;
using std::string;
int main()
{
    vector<int> v(10,2);
    v[2]=0;
    for(auto t:v)
        cout<<t<<endl;
    return 0;
}