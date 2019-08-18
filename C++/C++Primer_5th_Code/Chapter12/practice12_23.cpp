#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int main()
{
    const char *s1 = "Hello ";
    const char *s2 = "World!";
    size_t len = strlen(s1)+strlen(s2)+1;
    char *s = new char[len]();
    strcpy(s,s1);
    strcat(s,s2);

    cout<<s<<endl;

    string str1 = "Hello ";
    string str2 = "World!!!";
    strcpy(s,(str1+str2).c_str());

    cout<<s<<endl;
    return 0;
}