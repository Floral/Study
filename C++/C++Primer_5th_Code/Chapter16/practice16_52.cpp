#include<iostream>
#include<string>

using namespace std;

template<typename T, typename... Args>
void foo(const T &t, const Args& ... rest)
{
    cout<< sizeof...(Args)<<endl;
    cout<< sizeof...(rest)<<endl;
    cout<< rest...<<endl;
}

int main()
{
    int i=0;
    double d = 0;
    string s = "How are you!";
    foo(i,s,42,d);

    return 0;
}