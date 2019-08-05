#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>

using std::string;  using std::vector;
using std::fstream;
using std::stringstream;

int main()
{
    vector<string> v;
    string s;
    fstream fs("chinese-3500.txt");

    while (getline(fs,s))
    {
        /* code */
        v.push_back(s);
    }
    
    stringstream ss;
    for (auto &i : v)
    {
        // stringstream ss(i);
        ss.str(i);
        string t;
        while (ss>>t)
        {
            std::cout<<t<<std::endl;
        }
        ss.clear();
    }
        
    return 0;
}