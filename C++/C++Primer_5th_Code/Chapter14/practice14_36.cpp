#include<iostream>
#include<string>
#include<vector>

using namespace std;

class inputString{
public:
    inputString(istream& is=cin):is(is){};
    vector<string>& operator()();
private:
    istream& is;
    vector<string> v;
};

vector<string>& inputString::operator()()
{
    string s;
    while (getline(is,s))
    {
        v.push_back(s);
    }
    
    return v;
}

int main()
{
    inputString iS;

    iS();
    return 0;
}
