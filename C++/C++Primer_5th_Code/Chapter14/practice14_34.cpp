#include<iostream>
#include<string>

using namespace std;

class ITE{
public:
    int operator()(const int x1, const int x2, const int x3)
    {
        return x1 ? x2:x3;
    }
private:

};

int main()
{
    ITE t;
    cout<<t(0,2,3)<<endl;

    return 0;
}