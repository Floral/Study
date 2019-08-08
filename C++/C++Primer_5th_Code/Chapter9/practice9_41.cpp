#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main()
{
    vector<char> v{'H','e','l','l','o'};
    string s(v.cbegin(),v.cend());
    
    cout<<s<<endl;
    s.insert(s.end(),{'a','b','c'});
    cout<<s<<endl;
    
    return 0;
}