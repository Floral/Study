#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{

    int n,m,kcase=0;
    while(~scanf("%d%d",&n,&m)&&(n||m)){
        /* code */
        double sum=0;
        for(int i = n; i <= m; i++)
        {
            /* code */
            sum += 1/(double)i/i;
            // cout<<i<<endl;
        }
        printf("Case %d: %.5lf\n",++kcase,sum);        
    }
    
    return 0;
}