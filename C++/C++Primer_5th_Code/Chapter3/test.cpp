#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cin; using std::cout; using std::endl;
using std::string;
int main()
{
    // vector<int> v(10,2);
    // v[2]=0;
    // for(auto t:v)
        // cout<<t<<endl;
    
    // int scores[10];
    // for (auto i : scores)
    // {
        // cout<<i<<" ";
    // }
    // cout<<endl;

    string s("Hello World!");

    const char *p = s.c_str();
    cout<<*p<<endl;

    typedef double wages[4];

    wages a = {0};
    for (auto &i : a)
    {
        cout<<i<<endl;   
    }
    
    return 0;
}