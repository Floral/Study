#include<stdio.h>
#define maxn 1010
int bulb[maxn];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(size_t i = 0; i < n; i++)
    {
        /* code */
        bulb[i]=1;
    }
    for(size_t i = 2; i <= k; i++)
    {
        /* code */
        for(size_t j = 1; j*i < n; j++)
        {
            /* code */
            // printf("j:%d",j);
            bulb[i*j-1]=(-1)*bulb[i*j-1];
        }
        
    }
    
    for(size_t i = 0; i < n; i++)
    {
        /* code */
        if (bulb[i]==1) {
            /* code */
            printf("%d ",i+1);
        }
    }
    printf("\n");

    return 0;
}