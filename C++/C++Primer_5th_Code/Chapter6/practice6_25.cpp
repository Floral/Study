#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cin; using std::cout;
using std::endl; using std::string;

void test(vector<string> v)
{
    for (auto &i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    string s("");
    s=s+argv[1]+argv[2];
    cout<<s<<endl;
    
    test({"just","for","test"});
    return 0;
}