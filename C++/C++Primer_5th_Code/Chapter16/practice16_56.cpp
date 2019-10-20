#include<iostream>
#include<string>
#include<sstream>

using namespace std;

template<typename T>
string debug_rep(const T &t)
{
    ostringstream ret;
    ret<<t;
    return ret.str();
}

template<typename T>
ostream &print(ostream &os, const T &t)
{
    return os<<t;
}

template<typename T, typename ... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os<<t<<", ";
    return print(os, rest...);
}

template<typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
    return print(os, debug_rep(rest)...);
}

int main()
{
    int i=0;
    double d = 3.14;
    string s="Hello World!";

    errorMsg(cerr, i,42,d,s);
    return 0;
}