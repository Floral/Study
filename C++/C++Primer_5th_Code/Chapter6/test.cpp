#include<iostream>
#include<string>

using std::cin; using std::cout;
using std::endl;using std::string;

string::size_type find_char(const string &s,char c,string::size_type &occurs)
{
    auto ret = s.size();
    int i=0;
    occurs = 0;
    for (const auto &cc : s)
    {
        ++i;
        if (cc==c)
        {
            if(ret==s.size())
                ret=i;
            ++occurs;
        }
    }
    return ret;
}

void print(const int ia[10])
{
    for (size_t i = 0; i != 10; ++i)
    {
        cout<<ia[i]<<endl;
    }
}

int main()
{
    string s;
    string::size_type occurs=0;

    cout<<"please input a string:";
    cin>>s;
    cout<<"The char 'a' appear at number "<<find_char(s,'a',occurs)<<" the first time."<<endl;
    cout<<"There are "<<occurs<<" 'a' in your input string"<<endl;
    
    int i=42;
    const int j=42;
    const int *cp=&i;   //这里的const是指cp所指的对象不能被更改
    const int * p=cp;
    // int * const c = &j; //这里的const是指c指针本身不能被修改，但是它指向的对象可以被修改，而j本身是不能被修改的，所以这里报错了。

    int ia[10]{0,1,2,3,4,5,6,7,8,9};
    print(ia);
    return 0;
}