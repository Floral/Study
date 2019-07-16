#include<iostream>
#include<string>
#include<vector>
#include<cctype>

using std::cin; using std::cout; using std::endl;
using std::string; using std::vector;

int main()
{
    vector<string> v;
    string word;

    while (cin>>word)
    {
        v.push_back(word);
    }
    for (auto &t : v)
    {
        for (auto &i : t)
        {
            if (isalpha(i))
            {
                i=toupper(i);
            }
        }
    }
    for (auto &i : v)
    {
        cout<<i<<endl;
    }
    
    return 0;
}