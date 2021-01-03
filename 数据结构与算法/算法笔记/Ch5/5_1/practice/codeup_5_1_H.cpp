#include<cstdio>
#include<cstdlib>

int main()
{
    int m,n;

    scanf("%d", &m);
    while (m--)
    {
        int ans = 0;
        scanf("%d", &n);
        
        for (int i = abs(n); i <= 2*abs(n); i++)
            ans+=i;
        if (n>=0)
            printf("%d\n", ans);
        else
            printf("%d\n", -ans);
    }
    
    return 0;
}