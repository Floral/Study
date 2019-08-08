#include<iostream>
#include<string>

using namespace std;


void myReplace(string &s,string &oldVal,string &newVal)
{
    int n = oldVal.size();
    for (size_t i = 0; i < s.size()-n; ++i)
    {
        string t = s.substr(i,n);
        if (t==oldVal)
        {
            // s.erase(i,n);
            // s.insert(i,newVal);
            s.replace(i,n,newVal);
            i=i+newVal.size()-1;
        }
        
    }    
}

int main()
{
    string s("just thotho for test tho.");

    string oldVal="tho",newVal = "though";
    cout<<"s: "<<s<<endl;
    myReplace(s,oldVal,newVal);

    cout<<"after: "<<s<<endl;

    return 0;
}