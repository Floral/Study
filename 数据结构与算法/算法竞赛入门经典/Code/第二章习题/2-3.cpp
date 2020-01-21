#include<iostream>
#include<stdio.h>

using namespace std;

int main()
{
    int n;
    
    scanf("%d",&n);

    for(int i = 0; i < n; i++)
    {
        /* code */
        for(int j = 0; j < i; j++)
        {
            /* code */
            cout<<" ";
        }

        for(int k = 0; k < 2*(n-i)-1; k++)
        {
            /* code */
            cout<<"*";
        }
        cout<<endl;
    }
    
    return 0;
}