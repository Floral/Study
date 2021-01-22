#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    map<int,priority_queue<int,vector<int>,greater<int> > >a;
    int n,i,j;
    scanf("%d",&n);
    getchar();
    char s[11000];
    for(i=0; i<n; i++)
    {
        int x=0,y=0;
        scanf("%s",s);
        for(j=4; s[j]!='('; j++)
            x=x*10+s[j]-'0';
        for(s[j]='('; s[j]!=')'; j++)
        {
            if(s[j]>='0'&&s[j]<='9')
            {
                y=y*10+s[j]-'0';
            }
            else
            {
                if(y!=0)a[x].push(y);
                y=0;
            }
        }
        if(y!=0)a[x].push(y);

    }
    printf("Task0");
    for(i=0; i<a.size(); i++)
    {
        while(!a[i].empty())
        {
            printf(" Task%d",a[i].top());
            a[i].pop();
        }
    }
    return 0;
}

