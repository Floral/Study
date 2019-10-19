#include<iostream>
#include<string>

using namespace std;

template<typename T>
int compare(T&& a, T&& b)
{
    ++a;
    if(a<b)
        return -1;
    if(b<a)
        return 1;
    return 0;
}

int main()
{
    
    // std::cout<<compare<std::string>("dasda","grgr")<<std::endl;
    // string s1("dasda"),s2;
    int i=1,j=2;
    cout<<i<<endl;
    // s2=std::move(s1);
    compare(i,j);
    cout<<i<<endl;
    // cout<<s1<<endl;
    return 0;
}