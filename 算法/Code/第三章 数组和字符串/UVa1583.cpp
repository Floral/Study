#include<stdio.h>
#include<string.h>
#define maxn 100005
int ans[maxn];
/*
/*我的垃圾做法
int main()
{
    int n,i;

    scanf("%d",&n);
    for( i = 1; i < n; i++)
    {
        int t=i;
        for(size_t j = i; j>0 ;)
        {
            
            t=t+j%10;
            j=j/10;
        }
        if (t==n) {
            printf("%d\n",i);
            break;
        }
    }
    if (i==n) {
        printf("0\n");
    }
    return 0;
}
*/

//书上的答案
int main()
{
    int T,n;
    memset(ans,0,sizeof(ans));
    for(size_t i = 0; i < maxn; i++)
    {
        int x=i,y=i;
        while(x>0){
            y+=x%10;
            x/=10;
        }
        if (y<maxn && ans[y]==0) {
            ans[y]=i;
        }
        
    }

    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("%d\n",ans[n]);
    }
    return 0;
}