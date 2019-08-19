#include<iostream>
#include<string>

using namespace std;

class X{
public:
    X(){cout<<"X()"<<endl;}
    X(const X&){cout<<"X(const X&)"<<endl;}
    ~X() {cout<<"~X()"<<endl;}
    X& operator=(const X&){cout<<"operator=(const X&)"<<endl;return *this;}

private:
    string name;
};

int main()
{
    X x1=*(new X());
    X x2=*(new X());

    x1 = x2;

    return 0;
}