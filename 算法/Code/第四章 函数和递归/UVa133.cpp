#include<stdio.h>
#define maxn 25
int a[maxn];
int begin,end;


void count()
{
    
}

int main()
{
    int n,k,m;
    while (scanf("%d%d%d",&n,&k,&m)==3)
    {
        for (size_t i = 1; i <= n; i++) a[i]=i;
        
        while (1)
        {
            int flag=1;
            count();
            for (size_t i = 0; i < n; i++)
            {
                if (a[i]==0)
                {
                    flag=0;
                }
            }
            if (flag)
            {
                break;
            }
        }
        
    }
    
    return 0;
}