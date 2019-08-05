#include<iostream>
#include"practice7_23.h"
#include<string>

using std::cin; using std::cout;
using std::endl;
using std::string;

int main()
{
    Screen myScreen(5,10,'X');
    Screen::pos t;
    myScreen.move(4,0).set('#').display(cout);
    cout<<"\n";
    myScreen.display(cout);
    cout<<"\n";
    return 0;
}