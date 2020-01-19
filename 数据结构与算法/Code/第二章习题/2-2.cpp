#include<stdio.h>
#include<iostream>

using namespace std;

int main()
{
    int a,b,c,kcase=0;
    while(~scanf("%d%d%d",&a,&b,&c)){
        /* code */
        int i;
        for(i = 10; i < 100; i++)
        {
            /* code */
            if (i%3==a && i%5==b && i%7==c) {
                /* code */
               cout<<"case "<<++kcase<<": "<<i<<endl;
               break; 
            }
            
        }
        if (i==100) {
            /* code */
            cout<<"case "<<++kcase<<": No answer"<<endl;
        }
        
    }
    

    return 0;
}