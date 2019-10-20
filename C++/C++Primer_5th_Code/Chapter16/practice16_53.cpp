#include<iostream>
#include<string>

using namespace std;

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

int main()
{
    int i=0;
    double d=3.14;
    string s="Hello World!";

    print(cout, i, d, s);
    return 0;
}