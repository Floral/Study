#include<iostream>
#include<string>
#include<cctype>

using std::cin; using std::cout;
using std::endl;using std::string;

int if_include_upper(const string &s)
{
    int ret=0;
    for (auto &c : s)
    {
        if (isupper(c))
        {
            ret=1;
            break;
        }
    }
    return ret;
}

int main()
{
    string s;
    cin>>s;
    cout<<if_include_upper(s)<<endl;
    return 0;
}