#include<iostream>
#include<string>

using std::string;
using std::cin; using std::cout; using std::endl;

int main()
{
    int grade;
    cin>>grade;

    cout<<((grade<60)?"fail":(grade<75)?"low pass":(grade<90)?"pass":"high pass")<<endl;

    
    if (grade<60)
    {
        cout<<"fail"<<endl;
    }
    else if (grade<75)
    {
        cout<<"low pass"<<endl;
    }
    else if (grade<90)
    {
        cout<<"pass"<<endl;
    }
    else
    {
        cout<<"high pass"<<endl;
    }
    return 0;
}