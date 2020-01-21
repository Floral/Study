#include<stdio.h>
#include<string.h>

int main()
{
    int T,count[10];
    scanf("%d",&T);
    
    while(T--){
        int n;
        scanf("%d",&n);
        memset(count,0,sizeof(count));
        for (size_t i = 1; i <= n; i++)
        {
            int t=i;
            while (t>0)
            {
                count[t%10]++;
                t/=10;
            }
        }
        printf("%d",count[0]);
        for (size_t i = 1; i < 10; i++)
        {
            printf(" %d",count[i]);
        }
        printf("\n");
    }
    
    return 0;
}