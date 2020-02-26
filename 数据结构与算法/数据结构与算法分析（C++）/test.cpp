#include<iostream>
#include<string>

using namespace std;

class A
{
public:
    virtual void func()
    {
        cout<<"I'm A!";
    }
};

class B:public A
{
public:
    void func()
    {
        cout<<"I'm B!";
    }
};

int main(int argc, char const *argv[])
{
    A a;
    B b;
    A& p = b;
    // a.func();    

    const string str = "string";
    for(auto & x: str)
        cout<<x<<" ";

    cout<<str[0]<<endl;

    return 0;
}
