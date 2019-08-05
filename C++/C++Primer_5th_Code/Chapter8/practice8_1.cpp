#include<iostream>
#include<string>
#include<sstream>

using std::istream;
using std::cout;

istream& print(istream& is)
{
    auto old_state = is.rdstate();
    std::string s;

    while (is>>s)
    {
        cout<<s<<std::endl;
    }
    is.setstate(old_state);
    return is;
}

int main()
{
    std::istringstream iss("Hello World!");
    print(iss);
    return 0;
}