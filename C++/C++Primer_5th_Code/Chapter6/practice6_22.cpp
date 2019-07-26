#include<iostream>

using std::cin;
using std::cout;
using std::endl;

void change_pointer(int *&p1,int *&p2)
{
    int *t;
    t=p1;
    p1=p2;
    p2=t;
}

int main()
{
    int i=1,j=2;
    int *p1=&i,*p2=&j;
    cout<<"before change:"<<endl;
    cout<<*p1<<" "<<*p2<<endl;
    change_pointer(p1,p2);
    cout<<"after change:"<<endl;
    cout<<*p1<<" "<<*p2<<endl;
    return 0;
}