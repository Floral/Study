#include<iostream>

using namespace std;

class A
{
public:
     void func()
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
    p.func();    

    return 0;
}
