#include<iostream>
#include<string>

using namespace std;

class inputString{
public:
    inputString(istream& is=cin):is(is){};
    string operator()();
private:
    istream& is;
};

string inputString::operator()()
{
    string s;
    is >> s;
    
    return cin ? s:string();
}

int main()
{
    inputString iS;

    cout<<iS();
    return 0;
}