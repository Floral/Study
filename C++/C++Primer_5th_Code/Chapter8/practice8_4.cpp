#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using std::fstream;
using std::ifstream;    using std::ofstream;
using std::string;  using std::vector;

int main(int argc,char *argv[])
{
/* 
    string s("Hello World!");
    int i=0;
    for (auto p = argv + 1; p != argv+argc; ++p,++i)
    {
        ofstream os(*p);
        if (os)
        {
            os<<s[i];
        }
        else
        {
            std::cerr<<"Could't open: "+string(*p);
        }
    }
 */
    
    vector<string> v;
    string s;
    ifstream is("chinese-3500.txt",fstream::in);

    while (is>>s)
    {
        /* code */
        v.push_back(s);
    }
    
    for (auto &i : v)
    {
        std::cout<<i<<std::endl;
    }
    
    return 0;
}